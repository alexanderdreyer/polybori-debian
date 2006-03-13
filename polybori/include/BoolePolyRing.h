/// -*- c++ -*-
//*****************************************************************************
/** @file 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file the class BoolePolyRing, where carries the definition of a
 * polynomial ring over Booleans.
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
 * Revision 1.5  2006/03/13 12:27:24  dreyer
 * CHANGE: consistent function names
 *
 * Revision 1.4  2006/03/11 08:41:07  bricken
 * *bricken: standard/copy constructor
 *
 * Revision 1.3  2006/03/10 15:13:06  dreyer
 * ADD: Added static access to current ring
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

// load PolyBoRi settings
# include "pbori_defs.h"


#ifndef BoolePolyRing_h_
#define BoolePolyRing_h_

BEGIN_NAMESPACE_PBORI

/** @class BoolePolyRing
 * @brief This class is just a wrapper for using @c cudd's decicion diagram
 * manager as Boolean polynomial rings.
 *
 * The purpose of this wrapper is just to provide a fixed interface to the ring
 * structure, even if switched to a different type of binary decision diagram.
 *
 **/
class BoolePolyRing {

 public:
  //-------------------------------------------------------------------------
  // types definitions
  //-------------------------------------------------------------------------

  /// generic access to current type
  typedef BoolePolyRing self;

  /// @name adopt global type definitions
  //@{
  typedef CTypes::manager_type manager_type;
  typedef CTypes::dd_type dd_type;
  typedef CTypes::bool_type bool_type;
  typedef CTypes::size_type size_type;
  typedef CTypes::idx_type idx_type;
  //@}

  //-------------------------------------------------------------------------
  // constructors and destructor
  //-------------------------------------------------------------------------
  /// constructor for @em nvars variables
  BoolePolyRing(size_type nvars=100, bool_type make_active = true);
  BoolePolyRing(const BoolePolyRing &);
  
  /// destructor
  ~BoolePolyRing();

  //-------------------------------------------------------------------------
  // member operators
  //-------------------------------------------------------------------------
  /// cast to base operator
  operator manager_type&();

  //-------------------------------------------------------------------------
  // other member functions
  //-------------------------------------------------------------------------
  /// access to base
  manager_type& manager();

  /// constant access to base
  const manager_type& manager() const;

  /// access nvar-th ring variable
  dd_type variable(idx_type nvar) const;

  /// get number of ring variables
  size_type nVariables() const;


  /// access current global ring setting
  static self& ring();

  /// make this global ring
  void activate();

protected:

  /// pointer to current global ring setting
  static self* current_ring;

  /// interprete @c mgr as structure of Boolean polynomial ring
  mutable manager_type mgr;

  /// store number of ring variables
  size_type nvars;
};

END_NAMESPACE_PBORI

#endif // of #ifndef BoolePolyRing_h_
