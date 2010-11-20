// -*- c++ -*-
//*****************************************************************************
/** @file BoolePolyRing.cc
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file implements the class BoolePolyRing, where carries the definition of
 * a polynomial ring over Booleans. 
 *
 * @par Copyright:
 *   (c) 2006-2010 by The PolyBoRi Team
 *
**/
//*****************************************************************************


// load header file
# include "BoolePolyRing.h"
#include "BooleEnv.h"


// get error types
# include "PBoRiError.h"

#include "pbori_order.h"

#include "BooleExponent.h"
#include "BooleMonomial.h"

#include "cuddInt.h"

BEGIN_NAMESPACE_PBORI


/// Constructor for @em nvars variables
  //BooleRing::BooleRing(size_type nvars):
  // p_core(new core_type(nvars, get_ordering(lp)) ) {   }



/// Active Ring
BoolePolyRing::BoolePolyRing() : 
  p_core(BooleEnv::ring().core()) {
  PBORI_TRACE_FUNC( "BoolePolyRing()" );
}

// interface with cudd's variable management
BoolePolyRing::BoolePolyRing(size_type nvars, ordercode_type order,
                             bool_type make_active) : 
  p_core(new core_type(nvars, get_ordering(order))) {
  PBORI_TRACE_FUNC( "BoolePolyRing(size_type)" );

  if(make_active)
    activate();
}

void
BoolePolyRing::changeOrdering(ordercode_type order) {

  PBORI_TRACE_FUNC( "changeOrdering(ordercode_type)" );
  p_core->change_ordering(get_ordering(order)); 
}


//  make this global ring
void
BoolePolyRing::activate() {

  PBORI_TRACE_FUNC( "BoolePolyRing::activate()" );
  BooleEnv::set(*this);
}

/// Map polynomial to this ring, if possible
BoolePolyRing::poly_type BoolePolyRing::coerce(const poly_type& rhs) const {
  if (getManager() ==
      rhs.ring().getManager()) 
    return poly_type(rhs.navigation(), *this);
  
  throw PBoRiError(CTypes::invalid);
}

/// Map monomial to this ring, if possible
BoolePolyRing::monom_type BoolePolyRing::coerce(const monom_type& rhs) const {
  return CDDOperations<BooleSet, monom_type>().getMonomial(coerce(poly_type(rhs)).set());
}

/// Map variable to this ring
BoolePolyRing::var_type BoolePolyRing::coerce(const var_type& rhs) const {
  return var_type(rhs.index(), *this);
}


END_NAMESPACE_PBORI
