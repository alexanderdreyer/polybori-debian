// -*- c++ -*-
//*****************************************************************************
/** @file CCuddNavigator.h
 *
 * @author Alexander Dreyer
 * @date 2006-03-26
 *
 * This file defines an iterator for navigating through then and else branches
 * of Cudd decision diagrams.
 *
 * @note: Tested for Cudd's ZDDs only.
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.23  2008/09/21 22:21:02  dreyer
 * Change: deg_type replaces size_type for deg(), etc.
 *
 * Revision 1.22  2008/07/13 22:49:35  dreyer
 * Fix: Doxygen clean-up
 *
 * Revision 1.21  2007/11/06 15:03:33  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.20  2007/10/25 14:38:00  dreyer
 * ADD: use of CCuddNavigator more secure
 *
 * Revision 1.19  2007/07/30 15:19:39  dreyer
 * CHANGE: CCuddNavigator does not convert to DdNode* impicitely any more
 *
 * Revision 1.18  2007/07/06 14:04:21  dreyer
 * ADD: newly written C++_interface for Cudd
 *
 * Revision 1.17  2007/05/25 11:37:15  dreyer
 * CHANGE: typo
 *
 * Revision 1.16  2007/05/25 08:25:08  dreyer
 * Fix: workaround to break unwanted cast sequence navigator -> .. -> bool
 *
 * Revision 1.15  2007/02/20 09:41:06  dreyer
 * CHANGE: now running prototype for dlex-block iteration
 *
 * Revision 1.14  2007/02/09 17:08:21  dreyer
 * ADD: assertion
 *
 * Revision 1.13  2006/12/13 18:07:04  dreyer
 * ADD: poly /= exp
 *
 * Revision 1.12  2006/11/27 16:25:13  dreyer
 * CHANGE: CDegreeCache, now inherited from standard cache; dlex-lead cached
 *
 * Revision 1.11  2006/11/21 10:33:22  dreyer
 * CHANGE: added inlinable member functions
 *
 * Revision 1.10  2006/09/21 16:09:59  dreyer
 * ADD: caching mechanism for BoolePolynomial::deg()
 *
 * Revision 1.9  2006/09/19 09:46:05  dreyer
 * CHANGE: binary_compose to binary_composition
 * CHANGE: BooleMonomial::idx_map_type
 * ADD: symmetric_composition<>, navigates<>
 *
 * Revision 1.8  2006/08/18 19:47:15  dreyer
 * change finished low-level variant of minimal_elements also for lnegth()==2
 *
 * Revision 1.7  2006/08/09 12:52:31  dreyer
 * CHANGE/ADD: added lowlevel implementation of BooleSet::divisorsOf()
 *
 * Revision 1.6  2006/04/24 10:23:22  dreyer
 * ADD BoolePolynomial::begin() and end()
 * FIX type reference in CCuddNavigator
 *
 * Revision 1.5  2006/04/21 13:13:29  dreyer
 * ADD PBoRiOutITer for more generic manipulations
 *
 * Revision 1.4  2006/04/13 08:41:34  dreyer
 * CHANGE change() used by BoolePolynomial backward (for efficiency)
 *
 * Revision 1.3  2006/04/06 14:10:58  dreyer
 * ADD hash_type and CCuddNavigator::hash()
 *
 * Revision 1.2  2006/04/06 13:05:54  dreyer
 * CHANGE more suitable names for CCuddNavigator functions
 *
 * Revision 1.1  2006/04/04 15:31:06  dreyer
 * ADD: BoolePolynomial::navigator() and corresp. class CCuddNavigator
 *
 * @endverbatim
**/
//*****************************************************************************

#include <iterator>

// include basic definitions
#include "pbori_defs.h"
#include "pbori_tags.h"

#include "CCuddInterface.h"

#ifndef CCuddNavigator_h_
#define CCuddNavigator_h_

BEGIN_NAMESPACE_PBORI

/** @class CCuddNavigator
 * @brief This class defines an iterator for navigating through then and else branches
 * of ZDDs.
 *
 **/

class CCuddNavigator {

public:
  /// Cudd's node pointer
  typedef DdNode* pointer_type;

  /// Cudd's node pointer
  typedef CTypes::dd_base dd_base;

  /// Type for constantly accessing node pointer
  typedef const pointer_type const_access_type;

  /// Type for indices
  typedef CTypes::idx_type idx_type;

  /// Type for indices
  typedef CTypes::size_type size_type;

  /// Type for degrees
  typedef CTypes::deg_type deg_type;

  /// Type for hashing
  typedef CTypes::hash_type hash_type;

  /// Type for boolean results
  typedef CTypes::bool_type bool_type;

  /// Return type of dereferencing operator
  typedef idx_type value_type;

  /// Get type of *this
  typedef CCuddNavigator self;

  /// @name Interface types for standard iterator access
  //@{
  typedef navigator_tag iterator_category;
  typedef std::iterator_traits<pointer_type>::difference_type difference_type;
  typedef void pointer;
  typedef value_type reference;
  //@}

  /// Default constructor
  CCuddNavigator(): pNode(NULL) {}

  /// Construct from node pointer
  explicit CCuddNavigator(pointer_type ptr): pNode(ptr) {
    assert(isValid());
  }

  /// Construct from decision diagram
                         //  explicit CCuddNavigator(const dd_base& rhs): pNode(rhs.getNode()) {}

  /// Copy Constructor
  CCuddNavigator(const self& rhs): pNode(rhs.pNode) {}

  /// Destructor
  ~CCuddNavigator() {}

  /// Increment in @c then direction
  self& incrementThen();        // inlined below

  /// Increment in @c then direction
  self thenBranch() const { return self(*this).incrementThen(); }

  /// Increment in @c else direction
  self& incrementElse();        // inlined below

  /// Increment in @c else direction
  self elseBranch() const { return self(*this).incrementElse(); }

  /// Constant dereference operator
  reference operator*() const;  // inlined below

  /// Constant pointer access operator
  const_access_type operator->() const { return pNode; }

  /// Constant pointer access operator
  const_access_type getNode() const { return pNode; }

  /// Constant pointer access operator
  hash_type hash() const { return reinterpret_cast<long>(pNode); }

  /// Equality test
  bool_type operator==(const self& rhs) const { return (pNode == rhs.pNode); }

  /// Nonequality test
  bool_type operator!=(const self& rhs) const { return (pNode != rhs.pNode); }

  /// Check whether constant node was reached
  bool_type isConstant() const; // inlined below

  /// Check whether terminal node marks end of path
  bool_type terminalValue() const; // inlined below

  /// Check whether *this is not the default iterator self() (NULL pointer)
  bool_type isValid() const { return (pNode != NULL); }

  /// Check whether end of path was reached
  bool_type isTerminated() const { return isConstant() && terminalValue(); }

  /// Check whether dead end was reached
  bool_type isEmpty() const { return isConstant() && !terminalValue(); }

  /// @name Pointer-like comparision operations
  //@{
  bool_type operator<(const self& rhs) const { return (pNode < rhs.pNode); }
  bool_type operator<=(const self& rhs) const { return (pNode <= rhs.pNode); }
  bool_type operator>(const self& rhs) const { return (pNode > rhs.pNode); }
  bool_type operator>=(const self& rhs) const { return (pNode >= rhs.pNode); }
  //@}

  /// Force incrementation of reference count
  void incRef() const {  assert(isValid()); Cudd_Ref(pNode); }

  /// Force decrementation of reference count
  void decRef() const {  assert(isValid()); Cudd_Deref(pNode); }

  /// Force recursive decrementation of reference count
  template <class MgrType>
  void recursiveDecRef(const MgrType& mgr) const {
    assert(isValid());
    Cudd_RecursiveDerefZdd(mgr, pNode); 
  }

private: 
  /// Store node pointer
  pointer_type pNode;
};

// Inlined member functions

// constant pointer access operator
inline CCuddNavigator::value_type
CCuddNavigator::operator*() const {

  PBORI_TRACE_FUNC( "CCuddNavigator::operator*() const" );
  assert(isValid());
  return Cudd_Regular(pNode)->index;
}

// whether constant node was reached
inline CCuddNavigator::bool_type 
CCuddNavigator::isConstant() const {

  PBORI_TRACE_FUNC( "CCuddNavigator::isConstant() const" );
  assert(isValid());
  return Cudd_IsConstant(pNode);
}

// constant node value
inline CCuddNavigator::bool_type 
CCuddNavigator::terminalValue() const {

  PBORI_TRACE_FUNC( "CCuddNavigator::terminalValue() const" );
  assert(isConstant());
  return Cudd_V(pNode);
}


// increment in then direction
inline CCuddNavigator&
CCuddNavigator::incrementThen() {

  PBORI_TRACE_FUNC( "CCuddNavigator::incrementThen()" );

  assert(isValid());
  pNode = Cudd_T(pNode);

  return *this;
}

// increment in else direction
inline CCuddNavigator&
CCuddNavigator::incrementElse() {

  PBORI_TRACE_FUNC( "CCuddNavigator::incrementElse()" );

  assert(isValid());
  pNode = Cudd_E(pNode);

  return *this;
}

inline CCuddNavigator
explicit_navigator_cast(CCuddNavigator::pointer_type ptr) {

#ifndef NDEBUG
  if (ptr == NULL)
    return CCuddNavigator();
  else
#endif
    return CCuddNavigator(ptr);
}


END_NAMESPACE_PBORI

#endif
