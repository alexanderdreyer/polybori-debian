/*
 *  literal_factorization.h
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 29.05.06.
 *  Copyright 2006 The PolyBoRi Team. See LICENSE file.
 *
 */

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <utility>
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
  deg_type lmDeg;
  bool occursAsLeadOfFactor(idx_type v) const;
  bool trivial() const;
  bool is11Factorization();
  bool is00Factorization();
  //Theorem: f BoolePolynomial with factor (x+b), b in 0, 1 (considered in the usual Polynomial Ring)
  //then f/(x+b) does not involve the variable x
  //typedef std::pair<idx_type,idx_type> var_pair_type;
  //typedef std::set<var_pair_type> two_var_factors;
  typedef std::map<idx_type, idx_type> var2var_map_type;
  var2var_map_type var2var_map;
  
  protected:
    
    
    
};
deg_type common_literal_factors_deg(const LiteralFactorization& a, const LiteralFactorization& b);
END_NAMESPACE_PBORIGB
#endif
