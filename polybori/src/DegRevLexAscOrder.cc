// -*- c++ -*-
//*****************************************************************************
/** @file DegRevLexAscOrder.cc
 *
 * @author Alexander Dreyer
 * @date 2006-05-18
 *
 * Defining Degree-reverse lexicographical ordering.
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
 * Revision 1.9  2006/11/30 19:42:47  dreyer
 * CHANGE: lead(bound) now uses cached and recursive variant
 *
 * Revision 1.8  2006/11/29 13:40:03  dreyer
 * CHANGE: leadexp() made recursive and cached
 *
 * Revision 1.7  2006/11/28 09:32:58  dreyer
 * CHANGE: lead() (for dlex, dp_asc) is recursive and cached now
 *
 * Revision 1.6  2006/10/05 12:51:32  dreyer
 * CHANGE: Made lex-based comparisions more generic.
 *
 * Revision 1.5  2006/10/03 18:17:21  bricken
 * + removed minus sign again
 *
 * Revision 1.4  2006/10/03 11:36:36  bricken
 * + a minus sign
 *
 * Revision 1.3  2006/10/03 09:55:26  dreyer
 * FIX: monomial comparison broken on dp_asc
 *
 * Revision 1.2  2006/09/13 15:07:05  dreyer
 * ADD: lead(sugar) and infrastructure
 *
 * Revision 1.1  2006/09/13 09:05:44  dreyer
 * ADD: dp_asc/DegRevLexAscOrder
 * ADD: BoolePolynomial::endOfNavigation()
 * CHANGE: BoolePolynomial: removed biDegBegin(), biDegEnd(), which can be
 *   generated more generically using navigation() and endOfNavigation().
 *
 * @endverbatim
**/
//*****************************************************************************

// include  definitions
#include "DegRevLexAscOrder.h"

#include "pbori_algo.h"
#include "PBoRiOutIter.h"
#include "CIdxPath.h"


#include "CDelayedTermIter.h"

// get internal routines
#include "pbori_routines.h"

#include "CDegLexIter.h"

#include "CDegreeCache.h"

BEGIN_NAMESPACE_PBORI



// Comparison of monomials
DegRevLexAscOrder::comp_type
DegRevLexAscOrder::compare(const monom_type& lhs, const monom_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "DegRevLexAscOrder::compare(const monom_type&, const monom_type&) const)" );

  return deg_lex_compare(lhs, rhs, idx_comparer_type());
}

// Comparison of monomials
DegRevLexAscOrder::comp_type
DegRevLexAscOrder::compare(const exp_type& lhs, const exp_type& rhs) const {
  
  PBORI_TRACE_FUNC( 
    "DegRevLexAscOrder::compare(const exp_type&, const exp_type&) const)" );

  return deg_lex_compare(lhs, rhs, idx_comparer_type());

}

// Comparison of monomials
DegRevLexAscOrder::comp_type
DegRevLexAscOrder::compare(idx_type lhs, idx_type rhs) const {
  
  PBORI_TRACE_FUNC( 
    "DegRevLexAscOrder::compare(monom_type, monom_type) const)" );

  return generic_compare_3way(lhs, rhs, idx_comparer_type());
}

// Extraction of leading term
DegRevLexAscOrder::monom_type 
DegRevLexAscOrder::lead(const poly_type& poly) const {


  CDDOperations<BooleSet, monom_type> op;
  CCacheManagement<CCacheTypes::dp_asc_lead> 
    cache_mgr(poly.diagram().manager());
  CDegreeCache<> deg_mgr(poly.diagram().manager());

  return  op.getMonomial( dd_recursive_degree_lead(cache_mgr, deg_mgr,
                                               poly.navigation(), 
                                               BooleSet(),
                                               std::less_equal<size_type>()) );  
}

// maybe common template here
// Extraction of leading exponent
DegRevLexAscOrder::exp_type 
DegRevLexAscOrder::leadExp(const poly_type& poly) const {

  exp_type result;
  result.reserve(poly.deg());

  CCacheManagement<CCacheTypes::dp_asc_lead> 
    cache_mgr(poly.diagram().manager());
  CDegreeCache<> deg_mgr(poly.diagram().manager());

  return dd_recursive_degree_leadexp (cache_mgr, deg_mgr,
                                      poly.navigation(), result,
                                      std::less_equal<size_type>());
}

// Extraction of leading exponent
DegRevLexAscOrder::exp_type 
DegRevLexAscOrder::leadExp(const poly_type& poly, size_type bound) const {

  exp_type result;
  result.reserve(poly.deg());

  CCacheManagement<CCacheTypes::dp_asc_lead> 
    cache_mgr(poly.diagram().manager());
  CDegreeCache<> deg_mgr(poly.diagram().manager());

  return dd_recursive_degree_leadexp (cache_mgr, deg_mgr,
                                      poly.navigation(), result, bound,
                                      std::less_equal<size_type>());


}

// Extraction of leading term
DegRevLexAscOrder::monom_type 
DegRevLexAscOrder::lead(const poly_type& poly, size_type bound) const {

  CDDOperations<BooleSet, monom_type> op;
  CCacheManagement<CCacheTypes::dp_asc_lead> 
    cache_mgr(poly.diagram().manager());
  CDegreeCache<> deg_mgr(poly.diagram().manager());

  return  op.getMonomial( dd_recursive_degree_lead(cache_mgr, deg_mgr,
                                                poly.navigation(), 
                                                BooleSet(), bound,
                                                std::less_equal<size_type>()) );
}


// Initialize iterator corresponding to leading term
DegRevLexAscOrder::iterator
DegRevLexAscOrder::leadIterator(const poly_type& poly) const {

  PBORI_TRACE_FUNC( "DegRevLexAscOrder::leadIterator(const poly_type&) const" );

  return generic_iteration<self, iterator>().leadIterator(poly);
}

// Find next term (after iter) in polynomial according to current order
DegRevLexAscOrder::iterator
DegRevLexAscOrder::incrementIterator(iterator iter,
                                     const poly_type& poly) const {

  PBORI_TRACE_FUNC(
    "DegRevLexAscOrder::incrementIterator(iterator, const poly_type&) const" );

  return generic_iteration<self, iterator>().incrementIterator(iter, poly);
}

END_NAMESPACE_PBORI
