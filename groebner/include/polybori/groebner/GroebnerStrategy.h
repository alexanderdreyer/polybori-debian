// -*- c++ -*-
//*****************************************************************************
/** @file GroebnerStrategy.h 
 *
 * @author Michael Brickenstein 
 * @date 2011-06-29 
 *
 * This file includes the definition of the class @c GroebnerStrategy.
 *
 * @par Copyright:
 *   (c) 2006-2010 by The PolyBoRi Team
 *
**/
//*****************************************************************************

#ifndef polybori_groebner_GroebnerStrategy_h_
#define polybori_groebner_GroebnerStrategy_h_

// include basic definitions
#include "groebner_defs.h"
#include "pairs.h"
#include "cache_manager.h"

#include "PairManager.h"
#include "ReductionStrategy.h"

#include <vector>
#include <boost/shared_ptr.hpp>

BEGIN_NAMESPACE_PBORIGB

/** @class GroebnerStrategy
 * @brief This class defines GroebnerStrategy.
 *
 **/
class GroebnerStrategy{
public:
  /// copy constructor
  GroebnerStrategy(const GroebnerStrategy& orig);

  /// Construct from a ring
  GroebnerStrategy(const BoolePolyRing& input_ring):
    generators(input_ring), r(input_ring), pairs(*this, input_ring),
    optRedTailInLastBlock(input_ring.ordering().isBlockOrder()),
    optLazy(!input_ring.ordering().isDegreeOrder()),

    cache(new CacheManager()), matrixPrefix("mat"),
    chainCriterions(0), easyProductCriterions(0), extendedProductCriterions(0),

    optDrawMatrices(false), optModifiedLinearAlgebra(false),
    optDelayNonMinimals(true), enabledLog(false),
    variableChainCriterions(0),  optExchange(true), optHFE(false),
    optStepBounded(false), optAllowRecursion(true),
    optLinearAlgebraInLastBlock(true),
    reduceByTailReduced(false) {

    generators.llReductor = BooleSet(input_ring.one());
  }

  bool containsOne() const { return generators.leadingTerms.ownsOne(); }
  
  std::vector<Polynomial>  minimalizeAndTailReduce();
  std::vector<Polynomial>  minimalize();

  int addGenerator(const BoolePolynomial& p, 
                   bool is_impl=false, std::vector<int>* impl_v=NULL);
  void addGeneratorDelayed(const BoolePolynomial & p);
  void addAsYouWish(const Polynomial& p);  
  void addGeneratorTrySplit(const Polynomial& p, bool is_minimal);

  bool variableHasValue(idx_type i);
  void llReduceAll();
  void treat_m_p_1_case(const PolyEntry& e);

  Polynomial nextSpoly(){ return pairs.nextSpoly(generators);  }
  void addNonTrivialImplicationsDelayed(const PolyEntry& p);
  void propagate(const PolyEntry& e); 
  void propagate_step(const PolyEntry& e, std::set<int> others);

  void log(const char* c){ if (enabledLog) std::cout<<c<<std::endl; }

  Polynomial redTail(const Polynomial& p);
  std::vector<Polynomial> noroStep(const std::vector<Polynomial>&);
  std::vector<Polynomial> faugereStepDense(const std::vector<Polynomial>&);

  Polynomial nf(Polynomial p) const;
  void symmGB_F2();
  int suggestPluginVariable();
  std::vector<Polynomial> allGenerators();

protected:
  std::vector<Polynomial> treatVariablePairs(int s);
  void treatNormalPairs(int s,MonomialSet intersecting_terms,
                        MonomialSet other_terms, MonomialSet ext_prod_terms);
  void addVariablePairs(int s);
  std::vector<Polynomial>
  add4ImplDelayed(const Polynomial& p, const Exponent& lm_exp,
                  const Exponent& used_variables, int s, bool include_orig);
  std::vector<Polynomial>
  addHigherImplDelayedUsing4(int s,const LiteralFactorization& literal_factors,
                             bool include_orig);
      
public:

  /// @name public available parameters
  PairManager pairs;
  bool reduceByTailReduced;
  ReductionStrategy generators;
  bool optDrawMatrices;
  std::string matrixPrefix;
  //const char* matrixPrefix;
  boost::shared_ptr<CacheManager> cache;
  BoolePolyRing r;
  bool enabledLog;
   unsigned int reductionSteps;
  int normalForms;
  int currentDegree;
  int chainCriterions;
  int variableChainCriterions;
  int easyProductCriterions;
  int extendedProductCriterions;
  int averageLength;
  
  bool optHFE;
  bool optLazy;
  bool optModifiedLinearAlgebra;
  bool optDelayNonMinimals;
  
  bool optExchange;
  bool optAllowRecursion;
  
  bool optStepBounded;
  bool optLinearAlgebraInLastBlock;
  bool optRedTailInLastBlock;
};

END_NAMESPACE_PBORIGB

#endif /* polybori_GroebnerStrategy_h_ */