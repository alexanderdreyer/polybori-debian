// -*- c++ -*-
//*****************************************************************************
/** @file CDDOperations.h
 *
 * @author Alexander Dreyer
 * @date 2006-08-29
 *
 * This file implements an internal template class for geenric CDDOperations;
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"

// Get Cudd definitions
#include "cudd.h"
#include "extrafwd.h"

#include <routines/pbori_routines.h>
#include <cache/CCacheManagement.h>

#include "BoolePolyRing.h"

#ifndef CDDOperations_h_
#define CDDOperations_h_

BEGIN_NAMESPACE_PBORI

/// @class CDDOperation
/// @brief Generic class containing decision diagram operations
template <class DDType, class MonomType>
class CDDOperations {
public:

  // This is only a work-around, since a monomial should not be generated from
  // a dd.
  MonomType getMonomial(const DDType& dd) const {
    return MonomType(dd);
  }
  
  MonomType usedVariables(const DDType& dd){

  // get type definitions from DDType
  typedef typename DDType::idx_type idx_type;
  typedef typename DDType::navigator navigator;
  typedef MonomType monom_type;

  CCacheManagement<BoolePolyRing, CCacheTypes::used_variables> cache_mgr((BoolePolyRing)dd.ring());
  return cached_used_vars(cache_mgr, dd.navigation(),  
                          MonomType(cache_mgr.one()));
}

};



END_NAMESPACE_PBORI

#endif
