// -*- c++ -*-
//*****************************************************************************
/** @file 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file implements the class BoolePolymials, where carries the definition
 * of polynomials over Booleans.
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
 * Revision 1.3  2006/03/20 12:11:57  dreyer
 * CHANGE: Revised *deg*() functions.
 *
 * Revision 1.2  2006/03/17 16:53:37  dreyer
 * ADD added nNodes(), operator*= to BoolePolynomial
 *
 * Revision 1.1  2006/03/16 17:09:13  dreyer
 * ADD BoolePolynial functionality started
 *
 * @endverbatim
**/
//*****************************************************************************


// load header file
# include "BoolePolynomial.h"

// get polynomial riung definition
# include "BoolePolyRing.h"

// get error types
# include "PBoRiError.h"

BEGIN_NAMESPACE_PBORI

//-------------------------------------------------------------------------
// Constructors and destructor
//------------------------------------------------------------------------

// Default constructor
BoolePolynomial::BoolePolynomial():
  m_dd()  {

  PBORI_TRACE_FUNC( "BoolePolynomial()" );
}

// Constructor polynomial from existing decision diagram
BoolePolynomial::BoolePolynomial(const dd_type& rhs):
  m_dd(rhs)  {

  PBORI_TRACE_FUNC( "BoolePolynomial(const dd_type&)" );
}

// Copy constructor
BoolePolynomial::BoolePolynomial(const self& rhs) :
  m_dd(rhs.m_dd) {
  
  PBORI_TRACE_FUNC( "BoolePolynomial(const self&)" );
}

// Destructor
BoolePolynomial::~BoolePolynomial() {

  PBORI_TRACE_FUNC( "~BoolePolynomial()" );

}

//-------------------------------------------------------------------------
// operators and member functions
//------------------------------------------------------------------------


// Addition
BoolePolynomial&
BoolePolynomial::operator+=(const self& rhs) {

  PBORI_TRACE_FUNC( "BoolePolynomial::operator+=(const self&)" );

  m_dd = m_dd.Union( rhs.m_dd ).Diff( m_dd.Intersect(rhs.m_dd) );

  return *this;
}

// Multiplication
BoolePolynomial&
BoolePolynomial::operator*=(const monom_type& rhs) {

  PBORI_TRACE_FUNC( "BoolePolynomial::operator*=(const monom_type&)" );

  m_dd = m_dd.UnateProduct(rhs.m_dd);

  return *this;
}

// Leading term
BoolePolynomial::monom_type
BoolePolynomial::lead() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::lead() const" );

  PBORI_NOT_IMPLEMENTED;

  return monom_type();
}

// Maximal degree of the polynomial
BoolePolynomial::size_type
BoolePolynomial::deg() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::deg() const" );

  PBORI_NOT_IMPLEMENTED;

  return 0;
}


// Degree of the leading term
BoolePolynomial::size_type
BoolePolynomial::lmDeg() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::deg() const" );

  PBORI_NOT_IMPLEMENTED;

  return 0;
}


// Total (weighted) maximal degree of the polynomial
BoolePolynomial::size_type
BoolePolynomial::totalDeg() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::totalDeg() const" );

  // No weighted degrees yet, so map to non-weighted variant
  return deg();
}

// Total (weighted) degree of the leading term
BoolePolynomial::size_type
BoolePolynomial::lmTotalDeg() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::lmTotalDeg() const" );

  // No weighted degrees yet, so map to non-weighted variant
  return lmDeg();
}

// Number of nodes in the decision diagram
BoolePolynomial::size_type
BoolePolynomial::nNodes() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::nNodes() const" );

  return Cudd_zddDagSize(m_dd.getNode());
}

// Number of variables of the polynomial
BoolePolynomial::size_type
BoolePolynomial::nUsedVariables() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::nUsedVariables() const" );

  PBORI_NOT_IMPLEMENTED;

  return 0;
}

// Set of variables of the polynomial
BoolePolynomial::ddvector_type
BoolePolynomial::usedVariables() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::usedVariables() const" );

  PBORI_NOT_IMPLEMENTED;

  return ddvector_type(0, NULL, NULL);
}

// Access to internal decision diagramm structure
BoolePolynomial::dd_type&
BoolePolynomial::diagram() {

  PBORI_TRACE_FUNC( "BoolePolynomial::diagram()" );

  return m_dd;
}

// Access to internal decision diagramm structure
const BoolePolynomial::dd_type&
BoolePolynomial::diagram() const {

  PBORI_TRACE_FUNC( "BoolePolynomial::diagram() const" );

  return m_dd;
}

// Print current polynomial to cout
BoolePolynomial::ostream_type&
BoolePolynomial::print(ostream_type& os) const {

  PBORI_TRACE_FUNC( "BoolePolynomial::print() const" );

  ///  @todo: add std::cout capability for cudd's ZDD type

  os << "-> ";
  m_dd.print(BoolePolyRing::nRingVars());
  m_dd.PrintMinterm();

  return os;
}

// Stream output for Boolean polynomials
BoolePolynomial::ostream_type&
operator<<(BoolePolynomial::ostream_type& os, const BoolePolynomial& source) {

  return source.print(os);
}

END_NAMESPACE_PBORI
