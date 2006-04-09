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

// include basic definitions
#include "pbori_defs.h"

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

  /// Type for indices
  typedef int idx_type;

  /// Type for hashing
  typedef int hash_type;

  /// Type for boolean results
  typedef bool bool_type;

  /// Return type of dereferencing operator
  typedef idx_type value_type;

  /// Get type of *this
  typedef CCuddNavigator self;
  
  /// Default constructor and construct from node pointer
  CCuddNavigator(pointer_type ptr = NULL);

  /// Copy Constructor
  CCuddNavigator(const self&);

  /// Destructor
  ~CCuddNavigator();

  /// Increment in @i then direction
  self& incrementThen();

  /// Increment in @i then direction
  self thenBranch() const;

  /// Increment in @i else direction
  self& incrementElse();

  /// Increment in @i else direction
  self elseBranch() const;

  /// Constant dereference operator
  value_type operator*() const;

  /// Constant pointer access operator
  const pointer_type operator->() const;

  /// Constant pointer access operator
  hash_type hash() const;

  /// Equality test
  bool_type operator==(const self&) const;

  /// Nonequality test
  bool_type operator!=(const self&) const;

  /// Check whether constant node was reached
  bool_type isConstant() const;

  /// Check whether terminal node marks end of path
  bool_type terminalValue() const;

  /// Check whether *this is not the default iterator self() (NULL pointer)
  bool_type isValid() const;

private:
  pointer_type pNode;
};


END_NAMESPACE_PBORI

#endif