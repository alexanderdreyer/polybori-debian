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

// include basic definitions for orderings
#include "order_tags.h"

// include polynomial definitions
#include "BoolePolynomial.h"

// include monomial definitions
#include "BooleMonomial.h"

// include exponent vector definitions
#include "BooleExponent.h"

#ifndef DegLexOrder_h_
#define DegLexOrder_h_

BEGIN_NAMESPACE_PBORI

/** @class DegLexOrder
 * @brief This class defines ordering related functions.
 *
 *
 **/
class DegLexOrder {

 public:
  //-------------------------------------------------------------------------
  // types definitions
  //-------------------------------------------------------------------------

  /// generic access to current type
  typedef DegLexOrder self;

  /// Type of Boolean polynomials
  typedef BoolePolynomial poly_type;

  /// Type of Boolean monomials
  typedef BooleMonomial monom_type;

  /// Type of Boolean monomials
  typedef BooleExponent exp_type;

  /// @name adopt global type definitions
  //@{
  typedef CTypes::bool_type bool_type;
  typedef CTypes::dd_type dd_type;
  typedef CTypes::size_type size_type;
  typedef CTypes::idx_type idx_type;
  typedef CTypes::comp_type comp_type;
  //@}

  /// @name define generic property markers
  //@{
  typedef invalid_tag lex_property; 
  typedef invalid_tag ordered_property;
  typedef valid_tag symmetry_property;
  typedef valid_tag degorder_property;
  typedef valid_tag totaldegorder_property;
  //@}

  /// Default Constructor
  DegLexOrder() {};

  /// Copy Constructor
  DegLexOrder(const self&) {};

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

  /// Get leading exponent
  exp_type leadExp(const poly_type&) const;
};


END_NAMESPACE_PBORI

#endif // DegLexOrder_h_
