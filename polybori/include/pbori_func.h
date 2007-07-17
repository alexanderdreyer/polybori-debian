// -*- c++ -*-
//*****************************************************************************
/** @file pbori_func.h
 *
 * @author Alexander Dreyer
 * @date 2006-04-07
 *
 * This file includes some functional templates templates. 
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
 * Revision 1.37  2007/07/17 15:57:00  dreyer
 * ADD: header file for CCuddZDD; clean-up
 *
 * Revision 1.36  2007/05/03 16:04:46  dreyer
 * CHANGE: new-style CTermIter integrated
 *
 * Revision 1.35  2006/10/27 16:24:54  dreyer
 * ADD: some maybe useful stuff
 *
 * Revision 1.34  2006/10/27 15:31:11  dreyer
 * ADD: some maybe useful stuff
 *
 * Revision 1.33  2006/10/26 12:58:25  dreyer
 * ADD: lowlevel routine for union-xor (easy cudd-style variant)
 *
 * Revision 1.32  2006/10/24 14:21:56  dreyer
 * ADD: variable_name functional
 *
 * Revision 1.31  2006/10/06 12:52:01  dreyer
 * ADD easy_equility_property and used in lex_compare
 *
 * Revision 1.30  2006/10/05 12:51:32  dreyer
 * CHANGE: Made lex-based comparisions more generic.
 *
 * Revision 1.29  2006/10/04 13:09:56  dreyer
 * ADD: added compile-time optimied iterators and genericBegin/genericEnd
 *
 * Revision 1.28  2006/09/19 09:46:05  dreyer
 * CHANGE: binary_compose to binary_composition
 * CHANGE: BooleMonomial::idx_map_type
 * ADD: symmetric_composition<>, navigates<>
 *
 * Revision 1.27  2006/09/13 15:07:04  dreyer
 * ADD: lead(sugar) and infrastructure
 *
 * Revision 1.26  2006/09/13 09:05:44  dreyer
 * ADD: dp_asc/DegRevLexAscOrder
 * ADD: BoolePolynomial::endOfNavigation()
 * CHANGE: BoolePolynomial: removed biDegBegin(), biDegEnd(), which can be
 *   generated more generically using navigation() and endOfNavigation().
 *
 * Revision 1.25  2006/09/12 15:44:42  dreyer
 * FIX: accidently untested project<0> caused error.
 *
 * Revision 1.24  2006/09/12 15:33:16  dreyer
 * CHANGE: project_ith<0> corresponds to do-nothing (void return_type)
 *
 * Revision 1.23  2006/09/04 15:58:43  dreyer
 * ADD: DegLexOrder and preparations
 *
 * Revision 1.22  2006/08/28 15:08:19  bricken
 * + define HAVE_HASH_MAP
 *
 * Revision 1.21  2006/08/28 09:21:12  bricken
 * + extra xor for addition
 *
 * Revision 1.20  2006/08/28 07:25:08  dreyer
 * CHANGE: BooleExponent nomenclatur
 *
 * Revision 1.19  2006/08/24 14:47:50  dreyer
 * ADD: BooleExponent integrated, FIX: multiples (for indices < first)
 *
 * Revision 1.18  2006/08/23 14:24:53  dreyer
 * ADD: BooleSet::usedVariables and infrastructure
 *
 * Revision 1.17  2006/08/22 16:06:22  dreyer
 * + Added highlevel division
 *
 * Revision 1.16  2006/08/09 12:52:31  dreyer
 * CHANGE/ADD: added lowlevel implementation of BooleSet::divisorsOf()
 *
 * Revision 1.15  2006/07/20 10:13:59  dreyer
 * CHANGE: Made COrderProperties more generic
 *
 * Revision 1.14  2006/07/06 16:01:29  dreyer
 * CHANGE: Functionals ins pbori_func.h made more consistent
 *
 * Revision 1.13  2006/07/04 14:11:03  dreyer
 * ADD: Generic and handy treatment of string literals
 *
 * Revision 1.12  2006/06/07 11:54:26  dreyer
 * ADD variantes for usedVariables
 *
 * Revision 1.11  2006/06/06 10:56:59  dreyer
 * CHANGE usedVariables() more efficient now.
 *
 * Revision 1.10  2006/05/05 09:03:44  dreyer
 * ADD different implementation of the addition
 *
 * Revision 1.9  2006/04/25 10:17:39  dreyer
 * FIX recovered template<> preceeding explicit template specialization
 *
 * Revision 1.8  2006/04/25 09:30:42  dreyer
 * FIX end of CTermIterm for constants, CHANGE consistent functional names
 *
 * Revision 1.7  2006/04/24 14:45:35  dreyer
 * FIX CTermIter; ADD BoolePolynomial uses CTermIter
 *
 * Revision 1.6  2006/04/24 10:23:22  dreyer
 * ADD BoolePolynomial::begin() and end()
 * FIX type reference in CCuddNavigator
 *
 * Revision 1.5  2006/04/21 13:13:30  dreyer
 * ADD PBoRiOutITer for more generic manipulations
 *
 * Revision 1.4  2006/04/19 15:55:53  dreyer
 * ADD BooleMonomial, BoolePolynomial::fetchTerms() and ::terms()
 *
 * Revision 1.3  2006/04/13 07:53:19  dreyer
 * CHANGE BoolePolynomial::print() and deg() produces more useful results
 *
 * Revision 1.2  2006/04/12 16:23:54  dreyer
 * ADD template class CIDXPath<>
 *
 * Revision 1.1  2006/04/10 07:36:27  dreyer
 * ADD pbori_func.h to carry PolyBoRi related functionals
 *
 * @endverbatim
**/
//*****************************************************************************

// get polybori definitions
#include "pbori_defs.h"

// get polybori properties
#include "pbori_traits.h"

// get standard string and string stream functionality
#include <string>
#include <sstream>


// get map/hash_map functionality from stl/stl-ext
#define HAVE_HASH_MAP 1
#ifdef HAVE_HASH_MAP
#  include <ext/hash_map>
#else
#  include <map>
#endif

#ifndef pbori_func_h_
#define pbori_func_h_

BEGIN_NAMESPACE_PBORI

/// @class push_back 
/// @brief Accessing .push_back()
template <class ListType, class ValueType = typename ListType::value_type >
class push_back {
public:

  ListType
  operator()(ListType theList, const ValueType& elt) const {
    theList.push_back(elt);
    return theList;
  }
};

/// @class change
/// @brief Accessing .change()
template <class RhsType, class LhsType = typename RhsType::idx_type >
class change_idx {
public:

  RhsType operator() (const RhsType& rhs, const LhsType& lhs) const {
    return (rhs.change(lhs));
  } 

};

/// @class change_assign
/// @brief Accessing .changeAssign()
template <class RhsType = void,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class change_assign;

/// @class change_assign
/// @brief Accessing .changeAssign()
template <class RhsType, class LhsType>
class change_assign {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    return (rhs.changeAssign(lhs));
  } 

};

/// @class changeAssign
/// @brief Accessing .change(); variante using member templates
template<>
class change_assign<void, pbori_traits<void>::idx_type> {
public:

  template <class RhsType, class LhsType>
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    return (rhs.changeAssign(lhs));
  } 

};

/// @class subset1_assign
/// @brief Accessing .subset1Assign()
template <class RhsType, class LhsType = typename RhsType::idx_type>
class subset1_assign {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    (rhs.subset1Assign(lhs));
    return rhs;
  } 
};

/// @class subset1_assign
/// @brief Accessing .subset1Assign()
template <class RhsType, class LhsType>
class subset0_assign {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    return (rhs.subset0Assign(lhs));
  } 
};
/// @class unite_assign
/// @brief Accessing .uniteAssign()
template <class RhsType,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class unite_assign:
  public std::binary_function<RhsType&, const LhsType&, RhsType&> {

public:
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    return (rhs.uniteAssign(lhs));
  } 
};


// @class project_ith
/// @brief Accessing ith of n arguments 
/// (ITH = 0 returns default value of first type)
///
/// @note The argument NLEN is not necessary, but is may be used to indicate the
/// argument length for documentation reasons.

template <unsigned int ITH, unsigned int NLEN = ITH>
class project_ith;

/// @class project_ith<0, NLEN>
/// @brief Virtually does nothing with the given arguments
template <unsigned int NLEN>
class project_ith<0, NLEN> {

public:
  /// Functional operator
  template <class ValueType>
  void operator() (const ValueType&, ...) const { } 
};

/// @class project_ith<1, NLEN>
/// @brief Is the identity functional or projection to first argument
template <unsigned int NLEN>
class project_ith<1, NLEN> {

public:
  /// Constant functional operator template
  template <class ValueType>
  const ValueType& operator() (const ValueType& value, ...) const {
    return value;
  } 

  /// Functional operator template
  template <class ValueType>
  ValueType& operator() (ValueType& value, ...) const {
    return value;
  } 
};


/// @class project_ith<2, NLEN>
/// @brief Project to the second of all given arguments
template <unsigned int NLEN>
class project_ith<2, NLEN> {

public:
  /// Constant functional operator template
  template <class FirstType, class ValueType>
  const ValueType& 
  operator() (const FirstType&, const ValueType& value, ...) const {
    return value;
  } 

  /// Functional operator template
  template <class FirstType, class ValueType>
  ValueType& operator() (const FirstType&, ValueType& value, ...) const {
    return value;
  } 
};


/// @class project_ith<3, NLEN>
/// @brief Project to the third of all given arguments
template <unsigned int NLEN>
class project_ith<3, NLEN> {

public:
  /// Functional operator template
  template <class FirstType, class SecondType, class ValueType>
  const ValueType& 
  operator() (const FirstType&, const SecondType&, 
              const ValueType& value, ...) const {
    return value;
  } 

  /// Constant functional operator template
  template <class FirstType, class SecondType, class ValueType>
  ValueType& operator() (const FirstType&, const SecondType&, 
                         ValueType& value, ...) const {
    return value;
  } 
};

/*
class print_all {
public:

  print_all(std::ostream& os_):os(os_){}

  template<class Type>
  Type& operator()(Type& val){
    std::copy(val.begin(), val.end(), 
         std::ostream_iterator<typename  Type::value_type>(os, ", "));
    return val;
  }
  std::ostream& os;
};
*/

/// @class dummy_iterator
/// @brief An iterator which virtually does nothing.
class dummy_iterator {
public:

  /// Type of *this
  typedef dummy_iterator self;

  template <class Type>
  const self& operator=(const Type&) const { return *this;}

  const self& operator*() const { return *this;}
  const self& operator++() const { return *this;}
  const self& operator++(int) const { return *this;}
};

template <>
class pbori_traits<dummy_iterator>:
  public CTypes {
};

/// @class integral_constant
/// @brief integral_constant<int_type, NUM>()() returns NUM of int_type, instead
/// of possibly arguments.
/// integral_constant<int_type, NUM, other_type>()() returns conversion of
/// NUM of int_type to other_type.
template <class IntType, IntType INTCONST, class ResultType = IntType>
struct integral_constant {

  typedef ResultType result_type;
  result_type operator()(...) const { return INTCONST; }
};

/// @class binary_composition
/// @brief Compose a binary function with two default constructable unary
/// functions.
template <class BinaryOp, class FirstOp, class SecondOp>
class binary_composition:
  public BinaryOp {

public:

  /// Define types corresponding to template arguments
  //@{
  typedef BinaryOp base;
  typedef FirstOp first_op_type;
  typedef SecondOp second_op_type;
  //@}

  // Constructor
  binary_composition(const base& binop = base(),
                     const first_op_type& unop1 = first_op_type(),
                     const second_op_type& unop2 = second_op_type() ): 
    base(binop), first_op(unop1), second_op(unop2) {}

  /// Getting inherited types
  typedef typename base::result_type result_type;

  /// The composed operation for constant arguments
  template <class FirstType, class SecondType>
  result_type operator()(const FirstType& first, 
                         const SecondType& second) const {
    return base::operator()(first_op(first), second_op(second));
  }

  /// The composed operation for constant second argument
  template <class FirstType, class SecondType>
  result_type operator()(FirstType& first, 
                         const SecondType& second) const {
    return base::operator()(first_op(first), second_op(second));
  }

  /// The composed operation for constant first argument
  template <class FirstType, class SecondType>
  result_type operator()(const FirstType& first, 
                         SecondType& second) const {
    return base::operator()(first_op(first), second_op(second));
  }

protected:
  first_op_type first_op;
  second_op_type second_op;
};

/// @class symmetric_composition
/// @brief Compose a binary function with a default constructable unary
/// function for both arguments.
template <class BinaryOp, class UnaryOperation>
class symmetric_composition:
  public binary_composition<BinaryOp, UnaryOperation, UnaryOperation>  {

public:

  /// Define types corresponding to template arguments
  //@{
  typedef BinaryOp binary_op_type;
  typedef UnaryOperation unary_op_type;
  typedef binary_composition<binary_op_type, unary_op_type, unary_op_type>
  base;
  //@}

  // Constructor
  symmetric_composition(const binary_op_type& binop = binary_op_type(),
                     const unary_op_type& unop = unary_op_type() ): 
    base(binop, unop, unop) {}
};

/// @class maximum_iteration
/// @brief Returns maximun of given argument and previous calls
template<class ValueType>
class maximum_iteration {
public:
  maximum_iteration(ValueType & init) : max(init){}

  ValueType& operator()(const ValueType& val) const {
    return max = std::max(max, val);
  }

private:
  ValueType & max;
};

/// @class dd_add_assign
/// @brief Defines addition operation with assignment for decision diagrams.
template <class DDType>
class dd_add_assign {
public:

  DDType& operator()(DDType& lhs, const DDType& rhs) const {
    // several possible implementations
    return 
#ifdef PBORI_ADD_BY_ITE
      lhs.iteAssign(lhs.diff(rhs), rhs);

# elif defined(PBORI_ADD_BY_OR)
      (lhs = (lhs.diff(rhs)).unite(rhs.diff(lhs)));

# elif defined(PBORI_ADD_BY_UNION)
      (lhs = lhs.unite(rhs).diff( lhs.intersect(rhs) ) );
# elif defined(PBORI_ADD_BY_EXTRA_XOR) || defined(PBORI_ADD_BY_XOR)
      (lhs = lhs.Xor(rhs));
#endif
  }
};

/// @class times_indexed_var
/// @brief Defines multiplication operation with the idx-th variable
template <class DDType, class IdxType = typename DDType::idx_type>
class times_indexed_var {
public:

  DDType& operator()(DDType& lhs, IdxType idx) const {

  // get all terms not containing the variable with index idx
    DDType tmp( lhs.subset0(idx) );

    // get the complementary terms
    lhs.diffAssign(tmp);

    // construct polynomial terms
    dd_add_assign<DDType>()(lhs, tmp.change(idx));

    return lhs;
  }

};

/// @class append_indexed_divisor
/// @brief Defines multiplication (with assignment) with the idx-th variable
template <class DDType, class IdxType = typename DDType::idx_type>
class append_indexed_divisor {
public:

  DDType& operator()(DDType& lhs, IdxType idx) const {

    lhs.uniteAssign( lhs.change(idx) );
    return lhs;
  }

};

/// @class inserts
/// @brief Accessing .insert()
// template <class RhsType = void,
//           class LhsType = typename RhsType::value_type >
// class inserts:
//   public std::binary_function<RhsType&, const LhsType&, RhsType&> {
// public:

//   RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
//     rhs.insert(lhs);
//     return rhs;
//   } 

// };


/// @class insert
/// @brief Accessing .insert()
template <class RhsType = void,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class inserts;

template <class RhsType, class LhsType>
class inserts:
  public std::binary_function<RhsType&, const LhsType&, RhsType&> {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.insert(lhs);
    return rhs;
  } 
};

template <>
class inserts<void,  pbori_traits<void>::idx_type> {
public:
template <class RhsType, class LhsType>
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.insert(lhs);
    return rhs;
  } 
};


/// @class insert_assign
/// @brief Accessing .insertAssign()
template <class RhsType = void,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class insert_assign;

template <class RhsType, class LhsType>
class insert_assign:
  public std::binary_function<RhsType&, const LhsType&, RhsType&> {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.insertAssign(lhs);
    return rhs;
  } 
};

template <>
class insert_assign<void,  pbori_traits<void>::idx_type> {
public:
template <class RhsType, class LhsType>
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.insertAssign(lhs);
    return rhs;
  } 
};



/// @class removes
/// @brief Accessing .remove()
template <class RhsType = void,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class removes;


template <class RhsType, class LhsType>
class removes:
  public std::binary_function<RhsType&, const LhsType&, RhsType&> {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.remove(lhs);
    return rhs;
  } 
};


template <>
class removes<void,  pbori_traits<void>::idx_type> {
public:

  template <class RhsType, class LhsType>
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.remove(lhs);
    return rhs;
  } 
};

/// @class remove_assign
/// @brief Accessing .removeAssign()
template <class RhsType = void,
          class LhsType = typename pbori_traits<RhsType>::idx_type >
class remove_assign;


template <class RhsType, class LhsType>
class remove_assign:
  public std::binary_function<RhsType&, const LhsType&, RhsType&> {
public:

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.removeAssign(lhs);
    return rhs;
  } 
};


template <>
class remove_assign<void,  pbori_traits<void>::idx_type> {
public:

  template <class RhsType, class LhsType>
  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    rhs.removeAssign(lhs);
    return rhs;
  } 
};

/// @class insert_second_to_list
/// @brief Insert second argument to a given list
template <class ListType, class RhsType, class LhsType>
class insert_second_to_list {
public:

  insert_second_to_list(ListType& theList__):
    theList(theList__) {};

  RhsType& operator() (RhsType& rhs, const LhsType& lhs) const {
    theList.insert(lhs);
    return rhs;
  } 

private:
  ListType& theList;
};


/** @class is_same_type
 * @brief This class tests whether two types equal
 **/
template <class Type1, class Type2>
class is_same_type;

template <class Type>
class is_same_type<Type, Type>:
  public integral_constant<CTypes::bool_type, true> {}; 

template <class Type1, class Type2>
class is_same_type:
  public integral_constant<CTypes::bool_type, false> {};


/** @class on_same_type
 * @brief This class switches betweem two types, depending on equality of types
 **/
template <class Type1, class Type2, class ThenType, class ElseType>
class on_same_type;

template <class Type, class ThenType, class ElseType>
class on_same_type<Type, Type, ThenType, ElseType> {
public:
  typedef ThenType type;
};

template <class Type1, class Type2, class ThenType, class ElseType>
class on_same_type {
public:
  typedef ElseType type;
};


/** @class internal_tag
 * @brief This class marks an internal part of a procedure
 **/
struct internal_tag {};

/** @class type_tag
 * @brief This class marks a given type
 **/
template<class Type>
struct type_tag {};

template <class Type>
class hashes {
public:

  typedef typename Type::hash_type hash_type;

  hash_type operator() (const Type& rhs) const{
    return rhs.hash();
  }
};

template <class Type>
class lm_hashes {
public:

  typedef typename Type::hash_type hash_type;

  hash_type operator() (const Type& rhs) const{
    return rhs.lmHash();
  }
};

template <class Type>
class generate_index_map {

  typedef typename Type::idx_type idx_type;
public:
  /// Type for index maps
#ifdef HAVE_HASH_MAP
  typedef __gnu_cxx::hash_map<Type, idx_type, hashes<Type> > type;
#else
  typedef std::map<Type, idx_type> type;
#endif
};

/** @class sizes_less
 * @brief A functional for size comparisons.
 **/
template <class ListType>
class sizes_less:
  public std::binary_function<const ListType&, const ListType&, bool> {

public:
  bool operator()(const ListType& lhs, const ListType& rhs) const {
    return (lhs.size() < rhs.size());
  }    
};

/** @class reversed_iteration
 * @brief Interchanges operator++ and operator-- of a given iterator.
 **/
template <class BiIterator>
class reversed_iteration_adaptor {
public:

  /// The iterator type to be reversed
  typedef BiIterator iterator;

  /// Generic access to type of *this
  typedef reversed_iteration_adaptor<iterator> self;
  /// @name Interface types for standard iterator access
  //@{
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef typename std::iterator_traits<iterator>::difference_type 
  difference_type;
  typedef typename std::iterator_traits<iterator>::pointer  pointer;
  typedef typename std::iterator_traits<iterator>::reference  reference;
  typedef typename std::iterator_traits<iterator>::value_type value_type;
  //@}

  /// Constructor
  reversed_iteration_adaptor(const iterator& iter):
    m_iter(iter) {}

  /// Dereferecing operation

  reference operator*() const {
    return *m_iter;
  }

  /// Prefix increment operator  
  self& operator++() {
    --m_iter;
    return *this;
  }

  /// Prefix decrement operator  
  self& operator--() {
    ++m_iter;
    return *this;
  }

  bool operator==(const self& rhs) const {
    return m_iter == rhs.m_iter;
  }

  bool operator!=(const self& rhs) const {
    return m_iter != rhs.m_iter;
  }
  iterator get() const {
    return m_iter;
  }

protected:
  iterator m_iter;
};


template <class DDType>
class navigates:
  public std::unary_function<DDType, typename DDType::navigator> {
public:
  /// Type of decision diagram
  typedef DDType dd_type;

  /// Type for navigation through diagram
  typedef typename DDType::navigator navigator;

  /// Generic access to base type
  typedef std::unary_function<dd_type, navigator> base;

  /// The actual operation
  typename base::result_type operator()(const dd_type& rhs) const{
    return rhs.navigation();
  }

};


template <class ValueType>
class default_value {
public:
  typedef ValueType value_type;

  value_type operator()(...) const{
    return value_type();
  }

};

template <template<class> class BindType, class BinaryFunction, 
          class ValueType, class ConstantOp>
class constant_binder_base :
  public BindType<BinaryFunction>{
public:
  typedef BinaryFunction bin_op; 
  typedef ConstantOp const_type;
  typedef BindType<bin_op> base;

  typedef ValueType value_type;

  constant_binder_base(const bin_op& op = bin_op()): base(op, const_type()()) {}
};

template <class BinaryFunction, class ConstantOp>
class constant_binder2nd :
  public constant_binder_base<std::binder2nd, BinaryFunction,
                              typename BinaryFunction::second_argument_type,
                              ConstantOp> {
};


template <class BinaryFunction, class ConstantOp>
class constant_binder1st :
  public constant_binder_base<std::binder1st, BinaryFunction,
                              typename BinaryFunction::first_argument_type,
                              ConstantOp> {
};

template <template<class> class BindType,
          class BinaryFunction, class ValueType>
class default_binder_base :
  public BindType<BinaryFunction>{
public:
  typedef BinaryFunction bin_op; 
  typedef BindType<bin_op> base;

  typedef ValueType value_type;

  default_binder_base(const value_type&  val): base(bin_op(), val) {}
};

template <class BinaryFunction>
class default_binder2nd :
  public default_binder_base<std::binder2nd, BinaryFunction,
                              typename BinaryFunction::second_argument_type> {
public:
  typedef default_binder_base<std::binder2nd, BinaryFunction,
                              typename BinaryFunction::second_argument_type>
  base;

  default_binder2nd(const typename base::value_type&  val): base(val) {}
};


template <class BinaryFunction>
class default_binder1st :
  public default_binder_base<std::binder1st, BinaryFunction,
                              typename BinaryFunction::first_argument_type> {
};

// /** @class property_owner
//  *  @brief defines generic base for properties
//  **/
// template <class ValidityTag>
// class property_owner {
// public:

//   /// Set marker for validity
//   typedef typename 
//   on_same_type<ValidityTag, valid_tag, valid_tag, invalid_tag>::type property;

//   /// Generate Boolean member function
//   is_same_type<property, valid_tag> hasProperty;
// };

/** @class variable_name
 *  @brief Defines generic access to variable names
 **/
template <class ManagerType, 
          class IdxType = typename ManagerType::idx_type,
          class VarNameType = typename ManagerType::const_varname_reference>
class variable_name {
public:
  typedef ManagerType manager_type;
  typedef IdxType idx_type;
  typedef VarNameType varname_type;

  /// Constructor
  variable_name(const manager_type& mgr): m_mgr(mgr) {}

  /// Funtional operator
  varname_type operator()(idx_type idx) const{
    return m_mgr.getVariableName(idx);
  }

protected:
  /// Store reference to manager
  const manager_type& m_mgr;
};

template <class MapType, class VariableType, class TermType, class NodeType>
class mapped_new_node {
public:
  typedef MapType map_type;
  typedef NodeType node_type;

  typedef typename node_type::idx_type idx_type;

  mapped_new_node(const map_type& the_map): m_map(the_map) {}

  NodeType operator()(idx_type idx,
                      const node_type& first, const node_type&  second) const{
    return ((TermType)VariableType(m_map[idx]))*first +  second;
  }



private:
  const map_type& m_map;
};


/** @class get_base
 *  @brief Declaration, which can be used to define base classes for
 *  inheritance of classes in advance.
 **/
template <class NewType>
struct pbori_base;



template <class DDType>
class get_node {

public:
  typename DDType::node_type operator()(const DDType& rhs) const {
    return rhs.getNode();
  }
};

END_NAMESPACE_PBORI

#endif
