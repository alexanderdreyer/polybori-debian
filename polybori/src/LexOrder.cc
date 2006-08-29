// -*- c++ -*-
//*****************************************************************************
/** @file LexOrder.cc
 *
 * @author Alexander Dreyer
 * @date 2006-05-18
 *
 * Defining lexicographical ordering.
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
 * Revision 1.5  2006/08/29 09:02:36  dreyer
 * ADD: leadExp()
 *
 * Revision 1.4  2006/08/24 14:47:50  dreyer
 * ADD: BooleExponent integrated, FIX: multiples (for indices < first)
 *
 * Revision 1.3  2006/07/14 09:02:49  dreyer
 * ADD: greater_variable()
 *
 * Revision 1.2  2006/05/23 15:26:25  dreyer
 * CHANGE BoolePolyRing  can handle different orderings (only lex yet)
 *
 * Revision 1.1  2006/05/23 11:40:59  dreyer
 * + Initial Version
 *
 * @endverbatim
**/
//*****************************************************************************

// include  definitions
#include "LexOrder.h"

#include "pbori_algo.h"
# include "PBoRiOutIter.h"
#include "CIdxPath.h"

BEGIN_NAMESPACE_PBORI

// todo: move to some header
template<class Order, class FirstIterator, class SecondIterator>
typename Order::comp_type
lex_compare(FirstIterator start, FirstIterator finish, 
            SecondIterator rhs_start, SecondIterator rhs_finish,
            Order order) {

  while ( (start != finish) && (rhs_start != rhs_finish) && 
          (*start == *rhs_start) ) {
    ++start; ++rhs_start;
  }

  if (start == finish)
    return CTypes::less_than;

  if (rhs_start == rhs_finish)
    return CTypes::greater_than;

  return order.compare(*start, *rhs_start);
}

// todo: move to some header
template<class Order, class LhsType, class RhsType>
typename Order::comp_type
lex_compare(const LhsType& lhs, const RhsType& rhs, Order order) {

  if (lhs == rhs)
    return CTypes::equality;

  return lex_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), order);
}

// Comparison of monomials
LexOrder::comp_type
LexOrder::compare(const monom_type& lhs, const monom_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "LexOrder::compare(const monom_type&, const monom_type&) const)" );

  return lex_compare(lhs, rhs, *this);
}

// Comparison of monomials
LexOrder::comp_type
LexOrder::compare(const exp_type& lhs, const exp_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "LexOrder::compare(const exp_type&, const exp_type&) const)" );

  return lex_compare(lhs, rhs, *this);

}

// Comparison of monomials
LexOrder::comp_type
LexOrder::compare(idx_type lhs, idx_type rhs) const {
  
  PBORI_TRACE_FUNC( 
    "LexOrder::compare(monom_type, monom_type) const)" );

  if (lhs == rhs)
    return CTypes::equality;

  return (lhs < rhs?  CTypes::greater_than : CTypes::less_than);
}

// Extraction of leading term
LexOrder::monom_type 
LexOrder::lead(const poly_type& poly) const {

  monom_type leadterm;
   
  if (poly.isZero())
    leadterm = 0;
  else {

    // store indices in list
    CIdxPath<idx_type> indices(poly.lmDeg());

    // iterator, which uses changeAssign to insert variable
    // wrt. given indices to a monomial
    PBoRiOutIter<monom_type, idx_type, change_assign<monom_type> >  
      outiter(leadterm) ;
    
    // insert backward (for efficiency reasons)
    reversed_inter_copy(poly.firstBegin(), poly.firstEnd(), indices, outiter);
  } 
  return leadterm;
}

// maybe common template here
// Extraction of leading exponent
LexOrder::exp_type 
LexOrder::leadExp(const poly_type& poly) const {

  exp_type leadterm;
   
  if (!poly.isZero()) {

    leadterm.reserve(poly.lmDeg());
    // wrt. given indices to a monomial
    PBoRiOutIter<exp_type, idx_type, inserts<exp_type> >  
      outiter(leadterm) ;
    
    std::copy(poly.firstBegin(), poly.firstEnd(), outiter);
  } 
  return leadterm;
}

END_NAMESPACE_PBORI
