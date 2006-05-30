/*
 *  literal_factorization.h
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 29.05.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <algorithm>
#include <vector>
#include <map>
#include "groebner_defs.h"
#ifndef PBORI_GB_LF_H
#define PBORI_GB_LF_H
BEGIN_NAMESPACE_PBORIGB
class LiteralFactorization{
public:
  LiteralFactorization(const Polynomial&);
  typedef std::map<idx_type, int> map_type;
  map_type factors;
  Polynomial rest;
  bool occursAsLeadOfFactor(idx_type v);
  //Theorem: f BoolePolynomial with factor (x+b), b in 0, 1 (considered in the usual Polynomial Ring)
  //then f/(x+b) does not involve the variable x
};
deg_type common_literal_factors_deg(const LiteralFactorization& a, const LiteralFactorization& b);
END_NAMESPACE_PBORIGB
#endif