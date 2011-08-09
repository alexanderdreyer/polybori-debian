// -*- c++ -*-
//*****************************************************************************
/** @file DegLexOrder.h
 *
 * @author Alexander Dreyer
 * @date 2006-05-18
 *
 * Defining Degree-lexicographical ordering.
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id: DegLexOrder.h,v 1.9 2008/07/08 21:41:58 alexanderdreyer Exp $
 *
 * @par History:
 * @verbatim
 * $Log: DegLexOrder.h,v $
 * Revision 1.9  2008/07/08 21:41:58  alexanderdreyer
 * Merge: from developer's repository
 *
 * Revision 1.13  2007/11/06 15:03:35  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.12  2007/07/31 07:43:50  dreyer
 * ADD: getBaseOrderCode(), lieInSameBlock(...), isSingleton(), isPair()...
 *
 * Revision 1.11  2007/04/30 15:20:31  dreyer
 * CHANGE: Switching from CTermIter to iterators based on CTermStack
 *
 * Revision 1.10  2007/03/21 08:55:09  dreyer
 * ADD: first version of block_dlex running
 *
 * Revision 1.9  2007/03/19 16:49:39  dreyer
 * CHANGE: ordered iterators made more generic
 *
 * Revision 1.8  2006/10/06 12:52:01  dreyer
 * ADD easy_equility_property and used in lex_compare
 *
 * Revision 1.7  2006/10/05 12:51:31  dreyer
 * CHANGE: Made lex-based comparisions more generic.
 *
 * Revision 1.6  2006/10/04 12:22:32  dreyer
 * ADD: getOrderCode()
 *
 * Revision 1.5  2006/09/13 15:07:04  dreyer
 * ADD: lead(sugar) and infrastructure
 *
 * Revision 1.4  2006/09/08 14:31:39  dreyer
 * ADD: COrderedIter and infrastructure for order-dependent iterator
 *
 * Revision 1.3  2006/09/05 11:10:44  dreyer
 * ADD: BoolePolyRing::Compare(...), fixed assertion in groebner
 *
 * Revision 1.2  2006/09/05 08:48:32  dreyer
 * ADD: BoolePolyRing::is(Total)DegreeOrder()
 *
 * Revision 1.1  2006/09/04 15:58:43  dreyer
 * ADD: DegLexOrder and preparations
 *
 * @endverbatim
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"

// include base order definitions
#include "COrderBase.h"

#ifndef DegLexOrder_h_
#define DegLexOrder_h_

BEGIN_NAMESPACE_PBORI

/** @class DegLexOrder
 * @brief This class defines ordering related functions.
 *
 *
 **/
class DegLexOrder:
  public COrderBase {

 public:
  //-------------------------------------------------------------------------
  // types definitions
  //-------------------------------------------------------------------------

  /// generic access to current type
  typedef DegLexOrder self;

  /// @name define generic property markers
  //@{
  typedef valid_tag symmetry_property;
  typedef valid_tag degorder_property;
  typedef valid_tag totaldegorder_property;
  typedef valid_tag descending_property;
  typedef dlex_tag order_tag;
  //@}

  /// Define binary predicate for index comparision
  typedef std::less<idx_type> idx_comparer_type;

  /// Get order code
  enum { order_code = CTypes::dlex, baseorder_code = order_code };

  /// Default Constructor
  DegLexOrder(): base() {};

  /// Copy Constructor
  DegLexOrder(const self& rhs): base(rhs) {};

  /// Destructor
  ~DegLexOrder() {};

  /// Comparison of indices corresponding to variables
  comp_type compare(idx_type, idx_type) const;

  /// Comparison of monomials
  comp_type compare(const monom_type&, const monom_type&) const;

  /// Comparison of exponent vectors
  comp_type compare(const exp_type&, const exp_type&) const;

  /// Get leading term
  monom_type lead(const poly_type&) const;

  /// Get leading term (using upper bound)
  monom_type lead(const poly_type& poly, size_type) const;

  /// Get leading exponent
  exp_type leadExp(const poly_type&) const;

  /// Get leading exponent (using an upper bound)
  exp_type leadExp(const poly_type&, size_type) const;

  /// Initialize iterator corresponding to leading term
  indirect_iterator leadIteratorBegin(const poly_type&) const;
  indirect_iterator leadIteratorEnd() const;
  indirect_exp_iterator leadExpIteratorBegin(const poly_type&) const;
  indirect_exp_iterator leadExpIteratorEnd() const;
};


END_NAMESPACE_PBORI

#endif // DegLexOrder_h_
