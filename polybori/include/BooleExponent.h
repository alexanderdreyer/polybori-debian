// -*- c++ -*-
//*****************************************************************************
/** @file BooleExponent.h
 *
 * @author Alexander Dreyer
 * @date 2006-08-23
 *
 * This file carries the definition of class @c BooleExponent, which can be used
 * as interim storage for boolean monomials.
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
 * Revision 1.5  2006/08/28 14:03:05  dreyer
 * CHANGE operator* to + etc.
 *
 * Revision 1.4  2006/08/28 07:25:07  dreyer
 * CHANGE: BooleExponent nomenclatur
 *
 * Revision 1.3  2006/08/24 16:09:33  bricken
 * + removed typo
 *
 * Revision 1.2  2006/08/24 14:47:49  dreyer
 * ADD: BooleExponent integrated, FIX: multiples (for indices < first)
 *
 * Revision 1.1  2006/08/23 17:00:01  dreyer
 * ADD: initial version
 *
 * @endverbatim
**/
//*****************************************************************************

#ifndef BooleExponent_h_
#define BooleExponent_h_

// include basic definitions
#include "pbori_defs.h"

// get definition of BoolePolynomial, BooleMonomial, and BooleVariable
#include "BooleMonomial.h"
#include "BooleVariable.h"

BEGIN_NAMESPACE_PBORI

/** @class BooleExponent
 * @brief This class is just a wrapper for using variables for storing indices
 * as interim data structure for BooleMonomial
 *
 **/
class BooleExponent {

 public:

  //-------------------------------------------------------------------------
  // types definitions
  //-------------------------------------------------------------------------

  /// @name Adopt global type definitions
  //@{
  typedef CTypes::dd_type dd_type;
  typedef CTypes::size_type size_type;
  typedef CTypes::idx_type idx_type;
  typedef CTypes::hash_type hash_type;
  typedef CTypes::bool_type bool_type;
  typedef CTypes::comp_type comp_type;
  typedef CTypes::integer_type integer_type;
  typedef CTypes::ostream_type ostream_type;
  //@}

  /// Define the underlying data structure
  typedef std::vector<idx_type> data_type;

  /// Generic access to actual data
  typedef data_type::value_type value_type;

  /// @name Generic access to iterator types
  //@{
  typedef data_type::iterator iterator;
  typedef data_type::const_iterator const_iterator;
  typedef data_type::reverse_iterator reverse_iterator;
  typedef data_type::const_reverse_iterator const_reverse_iterator;
  //@}

  /// Generic access to current type
  typedef BooleExponent self;

  /// Type of Boolean polynomials
  typedef BoolePolynomial poly_type;

  /// Type of Boolean variables
  typedef BooleVariable var_type;

  /// Type of Boolean variables
  typedef BooleMonomial monom_type;

  /// Type of sets of Boolean variables
  typedef BooleSet set_type;

  /// Type for index maps
  typedef generate_index_map<self>::type idx_map_type;

  /// Default Constructor
  BooleExponent();

  /// Copy constructor
  BooleExponent(const self&);

  /// Construct from Boolean monomial
  self& get(const monom_type&);

//   /// Construct from Boolean constant
//   BooleExponent(bool_type);

  /// Destructor
  ~BooleExponent();

  /// Start iteration over indices (constant access)
  const_iterator begin() const { return m_data.begin(); }

  /// Finish iteration over indices (constant access)
  const_iterator end() const { return m_data.end(); }

   /// Start reverse iteration over indices (constant access)
  const_reverse_iterator rbegin() const { return m_data.rbegin(); }

  /// Finish reverse iteration over indices (constant access)
  const_reverse_iterator rend() const { return m_data.rend(); }

  /// Degree of the corresponding monomial
  size_type size() const { return m_data.size(); }


  /// Degree of the corresponding monomial
  size_type deg() const { return size(); }

  /// Divisors of the monomial
  set_type divisors() const;

  /// multiples of the monomial wrt. given monomial
  set_type multiples(const self&) const; 

  /// Hash value of the monomial
  hash_type hash() const;

  /// Substitute variable with index idx by its complement and assign
  self& changeAssign(idx_type);

  /// Substitute variable with index idx by its complement
  self change(idx_type) const;

  /// Insert variable with index idx in exponent vector
  self& insert(idx_type);

  /// Remove variable with index idx in exponent vector
  self& remove(idx_type);

  /// Insert variable with index idx in exponent vector
  self insertConst(idx_type) const;

  /// Remove variable with index idx in exponent vector
  self removeConst(idx_type) const;

  /// Corresponds to division of monomials
  self divide(const self&) const;
  self divide(const idx_type& rhs) const { 
    return (reducibleBy(rhs)? removeConst(rhs) : self() ); }

  self divide(const var_type& rhs) const { return divide(rhs.index()); }
  self divide(const monom_type&) const;

  /// Corresponds to multiplication of monomials
  self multiply(const self&) const;

  self multiply(const idx_type& rhs) const { return insertConst(rhs); }
  self multiply(const var_type& rhs) const { return multiply(rhs.index()); }
  self multiply(const monom_type&) const;

//   /// @name Arithmetical operations
//   //@{
//   self& operator*=(const self&);
//   self& operator/=(const self&);
//   self& operator*=(const var_type&);
//   self& operator/=(const var_type&);
//   //@}

  /// @name Logical operations
  //@{
  bool_type operator==(const self& rhs) const { return m_data == rhs.m_data; }
  bool_type operator!=(const self& rhs) const { return m_data != rhs.m_data; }
  //@}

  /// Assignment operation
  self& operator=(const self& rhs) { m_data = rhs.m_data; return *this; }
  self& operator=(const monom_type& rhs) {
    m_data.resize(rhs.size());
    std::copy(rhs.begin(), rhs.end(), internalBegin());
    return *this;
  }

  /// Test for reducibility
  bool_type reducibleBy(const self& rhs) const;
  bool_type reducibleBy(const monom_type& rhs) const;
  bool_type reducibleBy(const idx_type& rhs) const;
  bool_type reducibleBy(const var_type& rhs) const { 
    return reducibleBy(rhs.index()); }


//   /// Test for reducibility wrt. to a given variable
//   bool_type reducibleBy(const var_type& rhs) const;

  /// Compare with rhs monomial and return comparision code
  comp_type compare(const self&) const;

  /// Degree of the least common multiple
  size_type LCMDeg(const self&) const;

  /// Compute theleast common multiple and assign
  /// self& LCMAssign(const self&);

  /// Compute the greatest common divisor
  self LCM(const self&) const;

  /// Compute the greatest common divisor and assign
  //self& GCDAssign(const self&);

  /// Compute the greatest common divisor
  self GCD(const self&) const;

  /// Print current polynomial to output stream
  ostream_type& print(ostream_type&) const;
 
protected:
  /// Start iteration over indices (constant access)
  iterator internalBegin() { return m_data.begin(); }

  /// Finish iteration over indices (constant access)
  iterator internalEnd() { return m_data.end(); }

   /// Start reverse iteration over indices (constant access)
  reverse_iterator rInternalBegin() { return m_data.rbegin(); }

  /// Finish reverse iteration over indices (constant access)
  reverse_iterator rInternalEnd() { return m_data.rend(); }

  /// The actual exponent indices
  data_type m_data;
};


/// Multiplication of monomials
template <class RHSType>
inline BooleExponent
operator+(const BooleExponent& lhs, const RHSType& rhs) {
  return lhs.multiply(rhs);
}

/// Division of monomials
template <class RHSType>
inline BooleExponent
operator-(const BooleExponent& lhs, const RHSType& rhs) {
  return lhs.divide(rhs);
}


/// Less than comparision
inline BooleExponent::bool_type
operator<(const BooleExponent& lhs, const BooleExponent& rhs) {

  return (lhs.compare(rhs) == CTypes::less_than);
}

/// Greater than comparision
inline BooleExponent::bool_type
operator>(const BooleExponent& lhs, const BooleExponent& rhs) {

  return (lhs.compare(rhs) == CTypes::greater_than);
}

/// Less or equal than comparision
inline BooleExponent::bool_type
operator<=(const BooleExponent& lhs, const BooleExponent& rhs) {

  return (lhs.compare(rhs) <= CTypes::less_or_equal_max);
}

/// Greater or equal than comparision
inline BooleExponent::bool_type
operator>=(const BooleExponent& lhs, const BooleExponent& rhs) {

  return (lhs.compare(rhs) >= CTypes::greater_or_equal_min);
}


/// Compute the greatest common divisor of two monomials
inline BooleExponent
GCD(const BooleExponent& lhs, const BooleExponent& rhs ){

  return lhs.GCD(rhs);
}

/// Compute the greatest common divisor of two monomials
inline BooleExponent
LCM(const BooleExponent& lhs, const BooleExponent& rhs ){

  return lhs.LCM(rhs);
}


/// Stream output operator
inline BooleExponent::ostream_type& 
operator<<(BooleExponent::ostream_type& os, const BooleExponent& rhs) {
  return rhs.print(os);
}

END_NAMESPACE_PBORI

#endif // of BooleExponent_h_
