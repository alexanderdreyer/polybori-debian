// -*- c++ -*-
//*****************************************************************************
/** @file 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file defines some types, macros and other settings to be used with
 * the polybori library.
 *
 * @note Uses c++ namespace if @c PBORI_NO_NAMESPACES is undefined.
 *
 * @par Copyright:
 *   (c) 2006 by
 *   Dep. of Mathematics, Kaiserslautern University of Technology and @n
 *   Fraunhofer Institute for Industrial Mathematics (ITWM)
 *   D-67663 Kaiserslautern, Germany
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.19  2006/08/28 09:21:12  bricken
 * + extra xor for addition
 *
 * Revision 1.18  2006/06/07 11:54:26  dreyer
 * ADD variantes for usedVariables
 *
 * Revision 1.17  2006/05/23 15:26:25  dreyer
 * CHANGE BoolePolyRing  can handle different orderings (only lex yet)
 *
 * Revision 1.16  2006/05/05 09:03:44  dreyer
 * ADD different implementation of the addition
 *
 * Revision 1.15  2006/04/19 15:55:53  dreyer
 * ADD BooleMonomial, BoolePolynomial::fetchTerms() and ::terms()
 *
 * Revision 1.14  2006/04/06 14:10:58  dreyer
 * ADD hash_type and CCuddNavigator::hash()
 *
 * Revision 1.13  2006/04/05 14:56:38  dreyer
 * ADD prettyPrint functions for dot-output to stdout or file
 *
 * Revision 1.12  2006/03/24 15:02:44  dreyer
 * ADD: Reference to manager_type can also be used for CDDManager<> -nterface
 * ADD: lead(), (n)usedVariables(), lmDeg() implemented in BoolePolynomial
 *
 * Revision 1.11  2006/03/23 09:23:11  dreyer
 * ADD: pbori_shared_ptr_postclean, used by ~BoolePolyRing() to clean
 * current_mgr, if pbori_shared_ptr<> is used (not for boost::shared_ptr<>).
 *
 * Revision 1.10  2006/03/22 16:48:13  dreyer
 * ADD alternative to shared_ptr (if not available)
 *
 * Revision 1.9  2006/03/22 08:06:59  dreyer
 * ADD: Template specializations CDDInterface<ZDD>, CDDManager<Cudd>; 
 * ring uses shared_ptr now
 *
 * Revision 1.8  2006/03/20 14:51:00  dreyer
 * CHANGE: Use CDDInterface temple specializations instead of raw dd_type
 *
 * Revision 1.7  2006/03/16 17:09:13  dreyer
 * ADD BoolePolynial functionality started
 *
 * Revision 1.6  2006/03/16 13:37:41  dreyer
 * ADD: added error codes and PBORI_DEVELOPER marker
 *
 * Revision 1.5  2006/03/13 10:06:29  bricken
 * *bricken: undo last checkin
 *
 * Revision 1.3  2006/03/10 15:10:16  dreyer
 * ADD: Global bool_type added.
 *
 * Revision 1.2  2006/03/10 08:25:54  dreyer
 * + refined header style
 *
 * Revision 1.1.1.1  2006/03/09 14:34:31  dreyer
 * + Project started
 *
 * @endverbatim
**/
//*****************************************************************************

// load cudd's c++ interface
# include <cuddObj.hh>

#ifndef pbori_defs_h_
#define pbori_defs_h_

/// Name the project
#define PBORINAME polybori

/// Define deverloper's mode
#ifndef PBORI_NO_DEVELOPER
#  define PBORI_DEVELOPER
#endif

#ifndef PBORI_NO_NAMESPACES

/// Start project's namespace
#  define BEGIN_NAMESPACE_PBORI namespace PBORINAME {

/// Finish project's namespace
#  define END_NAMESPACE_PBORI } // end of namespace 

/// Use project's namespace
#  define USING_NAMESPACE_PBORI using namespace PBORINAME;

/// Access something in project's namespace using PBORI::
#  define PBORI PBORINAME

/// Using something from project's namespace
#  define USING_PBORI using PBORI

/// Start some namespace
#  define PBORI_BEGIN_NAMESPACE( sub_space ) namespace sub_space {

/// Finish some namespace
#  define PBORI_END_NAMESPACE }

#else 

#  define BEGIN_NAMESPACE_PBORI 
#  define END_NAMESPACE_PBORI 
#  define USING_NAMESPACE_PBORI 
#  define PBORI 
#  define USING_PBORI 
#  define PBORI_BEGIN_NAMESPACE( sub_space ) 
#  define PBORI_END_NAMESPACE 

#endif // PBORI_NO_NAMESPACES

/// Generate trace function if debugging
#ifdef PBORI_DEBUG_TRACE
# include <iostream>
# define PBORI_TRACE_FUNC(text) std::cerr << text << std::endl;
#else
# define PBORI_TRACE_FUNC(text) 
#endif

/// Get output stream type
#ifndef PBORI_NO_STDSTREAMS

# include <iostream>
# define PBORI_OSTREAM std::ostream

#else

BEGIN_NAMESPACE_PBORI

/// @struct Dummy structure if std::ostream is not available
struct PBORI_OSTREAM {};

template <class StreamedType>
PBORI_OSTREAM& 
operator<<(PBORI_OSTREAM& dummy, const StreamedType&) {
  return dummy;
};
END_NAMESPACE_PBORI

#endif // of #ifndef PBORI_NO_STDSTREAMS

/// Get shared pointer type
#ifndef PBORI_NO_BOOST_PTR

# include <boost/shared_ptr.hpp>
# define PBORI_SHARED_PTR(Type) boost::shared_ptr<Type>

BEGIN_NAMESPACE_PBORI

// Clean second pointer
template <class ValueType>
void
pbori_shared_ptr_postclean( const PBORI_SHARED_PTR(ValueType)&, 
                            const PBORI_SHARED_PTR(ValueType)& ){
  // nothing needed for boost::shared_ptr
}
END_NAMESPACE_PBORI

#else

BEGIN_NAMESPACE_PBORI
/** @internal @class pbori_shared_ptr
 * @brief This is a class template replacement for shared_ptr<>, if the latter
 * is not available.
 *
 * @warning Copy constructor and operator= do only reference copies, the
 * allocated memory is destroyed, when the initial instance is destroyed.
 * 
 **/
template <class ValueType>
class pbori_shared_ptr {
public:

  /// The type this class is referencing
  typedef ValueType value_type;

  /// Type of *this
  typedef pbori_shared_ptr<value_type> self;

  /// Construct initial instance 
  /// @note This class instance is assumed to manage *pRhs exclusively
  pbori_shared_ptr(value_type* pRhs = NULL): 
    pVal(pRhs), is_shared(pRhs == NULL) {}

  /// Shallow copy constructor
  pbori_shared_ptr(const self& rhs):
    pVal(rhs.pVal), is_shared(true) {}

  /// Destructor
  ~pbori_shared_ptr(){ if (!is_shared) delete pVal; }

  /// Reference assignment
  self& operator=(const self& rhs) {
    pVal = rhs.pVal; is_shared = true; 
    return *this;
  } 

  /// @name Operators for mimicing pointer behavior
  //@{
  value_type* operator->(){ return pVal; }
  const value_type* operator->() const { return pVal; }
  value_type& operator*(){ return *pVal; }
  const value_type& operator*() const { return *pVal; }
  bool operator==(const self& rhs) const { return (pVal==rhs.pVal); }
  operator bool() const { return pVal != NULL; }
  //@}

  /// Check whether pVal was instantiated by *this
  bool unique() const { return !is_shared; }

protected:
  /// The actual pointer
  value_type* pVal;

  /// Flag for determining whether the pointer is shared.
  bool is_shared;
};
END_NAMESPACE_PBORI

# define PBORI_SHARED_PTR(Type) PBORI::pbori_shared_ptr<Type>

BEGIN_NAMESPACE_PBORI
// Clean second pointer
template <class ValueType>
void
pbori_shared_ptr_postclean( const PBORI_SHARED_PTR(ValueType)& lhs, 
                            PBORI_SHARED_PTR(ValueType)& rhs ){
  if( lhs.unique() && (lhs == rhs) )
    rhs = PBORI_SHARED_PTR(ValueType)();
}
END_NAMESPACE_PBORI


#endif // of #ifndef PBORI_NO_BOOST_PTR


BEGIN_NAMESPACE_PBORI

/// Forward declaration of decision diagram interface
template <class DDType>
class CDDInterface;

/// Forward declaration of decision diagram manager interface
template <class ManType>
class CDDManager;

template <class ManType>
class OrderedManagerBase;


/** @class CTypes
 * @brief This struct contains type definitions to be used in library classes
 *
 * It mainly consists of definitions for
 * - the type of decicion diagrams (chosen from the @c cudd library),
 * - built-in types to be used consistently all over the library
 * 
 **/
struct CTypes {
  //-------------------------------------------------------------------------
  // types for treatment of decision diagrams
  //-------------------------------------------------------------------------

  /// Type of underlying binary decicion diagrams 
  typedef ZDD dd_base;

  /// Type of interface to binary decicion diagrams 
  typedef CDDInterface<dd_base> dd_type;

  /// Vector of dd_type
  typedef ZDDvector ddvector_type;

  /// Variables manager base type
  typedef Cudd manager_base;

  /// Manage variables to be used by polynomials over Boolean ring
  //  typedef CDDManager<Cudd>  manager_type;
   typedef OrderedManagerBase<manager_base> manager_type;

  /// Reference to decision diagramm manager
   typedef CDDManager<manager_base&>  manager_reference;
  //typedef OrderedManagerBase<manager_base&> manager_reference;

  /// Define shared pointer to decision diagram manager
  typedef PBORI_SHARED_PTR(manager_type) manager_ptr;

  //-------------------------------------------------------------------------
  // types for several purposes
  //-------------------------------------------------------------------------

  /// Type for standard true/false statements
  typedef bool bool_type;

  /// Type for lengths, dimensions, etc.
  typedef unsigned int size_type;

  /// Type for integer numbers
  typedef int integer_type;

  /// Type for indices
  typedef int idx_type;

  /// Type for comparisons
  typedef int comp_type;

  /// Type for hashing
  typedef int hash_type;

  /// Error codes enumeration
  enum errorcodes {
    alright = 0,
    failed,
    no_ring,
    invalid,
    out_of_bounds,
    io_error,
#ifdef PBORI_DEVELOPER
   not_implemented,
#endif
    last_error
  };

  /// Comparision codes enumeration
  enum comparecodes {
    less_than = -1,
    equality = 0,
    greater_than = +1,
    less_or_equal_max = 0,
    greater_or_equal_min = 0
  };

  /// Codes For orderings
  enum ordercodes {
    lp,
    dp
  };

  /// Type for ordering codes
  typedef int ordercode_type;

  /// Type used to store error codes
  typedef unsigned int errornum_type;

  /// Type used to verbose error information
  typedef const char* errortext_type;

  /// Type for out-stream
  typedef PBORI_OSTREAM ostream_type;
};

END_NAMESPACE_PBORI

#ifdef PBORI_DEVELOPER
# define PBORI_NOT_IMPLEMENTED \
  throw PBORI::PBoRiError(PBORI::CTypes::not_implemented);
#else
# define PBORI_NOT_IMPLEMENTED 
#endif

// Set default addition method
#if defined(PBORI_ADD_BY_ITE) || defined(PBORI_ADD_BY_OR) \
    || defined(PBORI_ADD_BY_UNION)
#else
# define PBORI_ADD_BY_EXTRA_XOR
#endif 


// Set default method for getting all used variables
#if defined(PBORI_USEDVARS_BY_IDX) || defined(PBORI_USEDVARS_BY_TRANSFORM) \
  || defined(PBORI_USEDVARS_HIGHLEVEL)|| defined(PBORI_USEDVARS_BY_SUPPORT)
#else
# define PBORI_USEDVARS_BY_IDX
#endif 

#endif // of #ifndef pbori_defs_h_
