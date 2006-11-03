// -*- c++ -*-
//*****************************************************************************
/** @file pbori_routines_order.h
 *
 * @author Alexander Dreyer
 * @date 2006-08-23
 *
 * This file includes files, which defines ordering-related function templates.
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
 * Revision 1.7  2006/11/03 10:22:59  dreyer
 * FIX: bug at comparison between monomials, extended workaround
 *
 * Revision 1.6  2006/11/03 08:54:38  bricken
 * + same proc to compare lex. for monom/exponent, ignores easy equality
 *
 * Revision 1.5  2006/10/06 12:52:01  dreyer
 * ADD easy_equility_property and used in lex_compare
 *
 * Revision 1.4  2006/10/05 12:51:32  dreyer
 * CHANGE: Made lex-based comparisions more generic.
 *
 * Revision 1.3  2006/10/05 07:33:58  dreyer
 * ADD: BoolePolynomial::genericExpBegin()/End()
 *
 * Revision 1.2  2006/10/03 09:55:26  dreyer
 * FIX: monomial comparison broken on dp_asc
 *
 * Revision 1.1  2006/09/04 15:58:43  dreyer
 * ADD: DegLexOrder and preparations
 *
 * @endverbatim
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"
#include "pbori_order.h"
#include "pbori_algo.h"
#include "pbori_traits.h"

#include "CRestrictedIter.h"

BEGIN_NAMESPACE_PBORI




template <class FirstIterator, class SecondIterator, class BinaryPredicate>
CTypes::comp_type
lex_compare_3way(FirstIterator start, FirstIterator finish, 
              SecondIterator rhs_start, SecondIterator rhs_finish, 
              BinaryPredicate idx_comp) {

   while ( (start != finish) && (rhs_start != rhs_finish) &&
           (*start == *rhs_start) ) {
     ++start; ++rhs_start;
   }

   if (start == finish) {
     if (rhs_start == rhs_finish)
       return CTypes::equality;

     return CTypes::less_than;
   }
   
   if (rhs_start == rhs_finish)
     return CTypes::greater_than;

   return (idx_comp(*start, *rhs_start)? 
           CTypes::greater_than: CTypes::less_than);
}


/// @func lex_compare
/// @brief defines lexicographic comparison
template <class LhsType, class RhsType, class BinaryPredicate>
CTypes::comp_type
lex_compare(const LhsType& lhs, const RhsType& rhs, 
            BinaryPredicate idx_comp, valid_tag has_easy_equality_test) {

  if (lhs == rhs)
    return CTypes::equality;

  return lex_compare_3way(lhs.begin(), lhs.end(), 
                                      rhs.begin(), rhs.end(), idx_comp);
  //typedef lex_compare_predicate<LhsType, RhsType, BinaryPredicate> comp_type;
  //return generic_compare_3way(lhs, rhs, comp_type(idx_comp));
}


/// @func lex_compare
/// @brief defines lexicographic comparison
template <class LhsType, class RhsType, class BinaryPredicate>
CTypes::comp_type
lex_compare(const LhsType& lhs, const RhsType& rhs, 
            BinaryPredicate idx_comp, invalid_tag has_no_easy_equality_test) {

  return lex_compare_3way(lhs.begin(), lhs.end(), 
                          rhs.begin(), rhs.end(), idx_comp);
}

/// @func lex_compare
/// @brief defines lexicographic comparison
template <class LhsType, class RhsType, class BinaryPredicate>
CTypes::comp_type
lex_compare(const LhsType& lhs, const RhsType& rhs, BinaryPredicate idx_comp) {

  typedef typename pbori_binary_traits<LhsType, RhsType>::easy_equality_property
    equality_property;

  return lex_compare(lhs, rhs, idx_comp, equality_property());
}

/// @func deg_lex_compare
/// @brief defines degree-lexicographic comparison
template<class LhsType, class RhsType, class BinaryPredicate>
CTypes::comp_type
deg_lex_compare(const LhsType& lhs, const RhsType& rhs, 
                BinaryPredicate idx_comp) {

  typedef typename LhsType::size_type size_type;
  CTypes::comp_type result = generic_compare_3way( lhs.size(), rhs.size(), 
                                                   std::greater<size_type>() );

  return (result == CTypes::equality? lex_compare(lhs, rhs, idx_comp): result);
}


template <class OrderType, class Iterator>
class generic_iteration;

template<class DummyType>
class dummy_data_type {
public:
  dummy_data_type(const DummyType&) {}
  dummy_data_type(DummyType&) {}
  dummy_data_type() {}
};

// LexOrder
template <class Iterator>
class generic_iteration<LexOrder, Iterator> {
public:

  /// @name Get template parameters
  //@{
  typedef LexOrder order_type;
  typedef Iterator iterator;
  typedef typename order_type::poly_type poly_type;
  typedef dummy_data_type<poly_type> data_type;
  //@}

  /// Define initial iterator generation for this ordering
  iterator leadIterator(const poly_type& poly) const {
    return iterator(poly.navigation());
  }

  /// Define iterator incrementation for this ordering
  iterator incrementIterator(iterator& iter, const data_type&) const {
    return ++iter;
  }
};

// DegLexOrder
template <class Iterator>
class generic_iteration<DegLexOrder, Iterator> {
public:
  /// @name Get template parameters
  //@{
  typedef DegLexOrder order_type;
  typedef Iterator iterator;
  typedef typename order_type::poly_type poly_type;
  typedef poly_type data_type;
  typedef typename order_type::size_type size_type;
  //@}

  /// Define initial iterator generation for this ordering
  iterator leadIterator(const poly_type& poly) const {
    return std::max_element(iterator(poly.navigation()), 
                            iterator(poly.endOfNavigation()) );
  }

  /// Define iterator incrementation for this ordering
  iterator& incrementIterator(iterator& iter, const data_type& poly) const {
    typedef CRestrictedIter<iterator> bounded_iterator;
    
    iterator m_start(poly.navigation());
    iterator m_finish(poly.endOfNavigation());
    
    if (iter != m_finish) {
      size_type deg = *iter;
      ++iter;
      iter = std::find(iter, m_finish, deg);
      
      if(iter == m_finish) {
        iter = std::max_element( bounded_iterator(m_start, deg),
                                 bounded_iterator(m_finish, deg) );
        
      }
    }
    return iter;
  }
};


// DegRevLexAscOrder
template <class Iterator>
class generic_iteration<DegRevLexAscOrder, Iterator> {
public:
  /// @name Get template parameters
  //@{
  typedef DegRevLexAscOrder order_type;
  typedef Iterator iterator;
  typedef typename order_type::poly_type poly_type;
  typedef poly_type data_type;
  typedef typename order_type::size_type size_type;
  //@}

  /// Define initial iterator generation for this ordering
  iterator leadIterator(const poly_type& poly) const {
    return std::max_element(iterator(poly.navigation()), 
                            iterator(poly.endOfNavigation()),
                            std::less_equal<size_type>() );
  }

  /// Define iterator incrementation for this ordering
  iterator& incrementIterator(iterator& iter, const data_type& poly) const {

    typedef CRestrictedIter<iterator> bounded_iterator;
    
    iterator m_start(poly.navigation());
    iterator m_finish(poly.endOfNavigation());
    
    if (iter != m_finish) {
      
      size_type deg = *iter;
      --iter;
      iter = std::find(reversed_iteration_adaptor<iterator>(iter), 
                       reversed_iteration_adaptor<iterator>(m_finish), deg).get();
      
      if(iter == m_finish) {
        iter = std::max_element( bounded_iterator(m_start, deg),
                                 bounded_iterator(m_finish, deg), 
                                 std::less_equal<size_type>() );
        
      }
    }
    return iter;
  }
};


END_NAMESPACE_PBORI
