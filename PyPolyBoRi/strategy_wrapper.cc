/*
 *  strategy_wrapper.cc
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 21.04.06.
 *  Copyright 2006 The PolyBoRi Team. See LICENSE file.
 *
 */
#include <boost/python.hpp>
#include "strategy_wrapper.h"
#include <iostream>
#include <vector>
#include <polybori/groebner/nf.h>
#include <polybori/groebner/contained_variables.h>
#include <polybori/groebner/groebner_alg.h>
#include <polybori/groebner/LiteralFactorization.h>
#include <polybori/BoolePolyRing.h>
#include "slimgb_wrapper.h"
#include <polybori/groebner/interpolate.h>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
//#include <iostream>
//#include "polybori.h"
//#include "polybori/pbori_defs.h"
using namespace boost::python;
using namespace std;
#include "variable_block.h"

#include <iterator>
USING_NAMESPACE_PBORIGB
USING_NAMESPACE_PBORI

class StrategyIndexException {};

static void translator_gi(StrategyIndexException const& x) {
    PyErr_SetString( PyExc_IndexError, "Wrong Index access at strategy");
}
class StrategyIterator{
public:
    PolyEntryVector::const_iterator it;
    StrategyIterator(PolyEntryVector::const_iterator it){
        this->it=it;
    }
    bool operator==(const StrategyIterator other){
        return it==other.it;
    }
    const Polynomial& operator*(){
        return it->p;
    }
    const Polynomial* operator->(){
        return &(it->p);
    }
    StrategyIterator operator++(int){
        StrategyIterator cp(*this);
        ++it;
        return cp;
    }
    StrategyIterator& operator++(){
        ++it;
        return *this;
    }
    typedef std::input_iterator_tag iterator_category;
    typedef Polynomial value_type;
    typedef std::iterator_traits<PolyEntryVector::const_iterator>::difference_type difference_type;
    typedef const Polynomial* pointer;
    typedef const Polynomial reference;
};
static int npairs(const GroebnerStrategy& strat){
  return strat.pairs.queue.size();
}
static int nGenerators(const GroebnerStrategy& strat){
  return strat.generators.size();
}
static int pairs_top_sugar(const GroebnerStrategy& strat){
  if (strat.pairs.pairSetEmpty())
    return -1;
  else
    return (strat.pairs.queue.top().sugar);
}
static void cleanTopByChainCriterion(GroebnerStrategy & strat){
  strat.pairs.cleanTopByChainCriterion();
}

// static void printGenerators(const GroebnerStrategy& strat){
//   for (std::size_t i=0;i<strat.generators.size();i++){
//     std::cout<<(strat.generators[i].p)<<std::endl;
//   }
// }
// static vector<Polynomial> nextDegreeSpolys(GroebnerStrategy& strat){
//   vector<Polynomial> res;
//   PBORI_ASSERT(!(strat.pairs.pairSetEmpty()));
//   strat.pairs.cleanTopByChainCriterion();
//   deg_type deg=strat.pairs.queue.top().sugar;
  
//   while((!(strat.pairs.pairSetEmpty())) &&(strat.pairs.queue.top().sugar<=deg)){
    
//     PBORI_ASSERT(strat.pairs.queue.top().sugar==deg);
//     res.push_back(strat.nextSpoly());
//     strat.pairs.cleanTopByChainCriterion();
//   }
//   return res;
  
// }

static vector<Polynomial> someNextDegreeSpolys(GroebnerStrategy& strat, int n){
  vector<Polynomial> res;
  PBORI_ASSERT(!(strat.pairs.pairSetEmpty()));
  strat.pairs.cleanTopByChainCriterion();
  deg_type deg=strat.pairs.queue.top().sugar;
  
  while((!(strat.pairs.pairSetEmpty())) &&
        (strat.pairs.queue.top().sugar<=deg) && (res.size() < (std::size_t)n)){
    
    PBORI_ASSERT(strat.pairs.queue.top().sugar==deg);
    res.push_back(strat.nextSpoly());
    strat.pairs.cleanTopByChainCriterion();
  }
  return res;
  
}
// static vector<Polynomial> small_next_degree_spolys(GroebnerStrategy& strat, double f, int n){
//   vector<Polynomial> res;
//   PBORI_ASSERT(!(strat.pairs.pairSetEmpty()));
//   strat.pairs.cleanTopByChainCriterion();
//   deg_type deg=strat.pairs.queue.top().sugar;
//   wlen_type wlen=strat.pairs.queue.top().wlen;
//   while((!(strat.pairs.pairSetEmpty())) &&(strat.pairs.queue.top().sugar<=deg) && (strat.pairs.queue.top().wlen<=wlen*f+2)&& (res.size()<(std::size_t)n)){
    
//     PBORI_ASSERT(strat.pairs.queue.top().sugar==deg);
//     res.push_back(strat.nextSpoly());
//     strat.pairs.cleanTopByChainCriterion();
//   }
//   return res;
  
// }
bool contains_one(const GroebnerStrategy& strat){
  int s=strat.generators.size();
  int i;
  for(i=0;i<s;i++){
    if (strat.generators[i].p.isOne()){
      return true;
    }
  }
  return false;
}
static void implications(GroebnerStrategy& strat, int i){
  strat.addNonTrivialImplicationsDelayed(const_cast<const GroebnerStrategy&>(strat).generators[i]);
    
}
int select_wrapped(const GroebnerStrategy & strat, const Monomial& m){
    return strat.generators.select1(m);
}

static Polynomial get_ith_gen(const GroebnerStrategy& strat, std::size_t i){
    if PBORI_UNLIKELY((i<0)||(i>=strat.generators.size())){
        throw StrategyIndexException();
    }
    return strat.generators[i].p;
}

static Polynomial get_gen_by_lead(const GroebnerStrategy& strat, const Monomial& m){
  return get_ith_gen(strat, strat.generators.checked_index(m));
}

class DuplicateLeadException{};


static void translator_g(PolynomialIsZeroException const& x) {
    PyErr_SetString( PyExc_ValueError, "zero polynomial not allowed here");
}
static void translator_d(DuplicateLeadException const& x) {
    PyErr_SetString( PyExc_ValueError, "strategy contains already a polynomial with same lead");
}


static void add_generator(GroebnerStrategy& strat, const Polynomial& p){
    if PBORI_UNLIKELY(p.isZero()) throw PolynomialIsZeroException();
    Monomial m=p.lead();
    if PBORI_UNLIKELY(strat.generators.leadingTerms.owns(m)) throw DuplicateLeadException();
    strat.addGenerator(p);
}
static StrategyIterator stratbegin(const GroebnerStrategy& strat){
    return StrategyIterator(strat.generators.begin());
}
static StrategyIterator stratend(const GroebnerStrategy& strat){
    return StrategyIterator(strat.generators.end());
}

static void add_as_you_wish(GroebnerStrategy& strat, const Polynomial& p){
    if PBORI_UNLIKELY(p.isZero()) throw PolynomialIsZeroException();
    strat.addAsYouWish(p);
}

static void add_generator_delayed(GroebnerStrategy& strat, const Polynomial& p){
    if PBORI_UNLIKELY(p.isZero()) throw PolynomialIsZeroException();
    strat.addGeneratorDelayed(p);
}

template <class Type>
void export_terms(const char* name) {
  implicitly_convertible<MonomialSet, Type>();
  implicitly_convertible<Type, MonomialSet >();

  boost::python::class_<Type,
    boost::python::bases<MonomialSet> > (name, name,
                                         init<const BoolePolyRing&>());

}

void export_strategy(){
  export_slimgb();
  export_terms<MonomialTerms>("MonomialTerms");

  def("easy_linear_factors", easy_linear_factors);
  boost::python::class_<PolyEntry>("PolyEntry",
                          "Entry with polynomial and statistical information",
                          init<const Polynomial&>())
  .def_readwrite("p",&PolyEntry::p)
  .def_readwrite("lead",&PolyEntry::lead)
  .def_readwrite("weighted_length",&PolyEntry::weightedLength)
  .def_readwrite("length",&PolyEntry::length)
  .def_readwrite("deg",&PolyEntry::deg)
  .def_readwrite("lead_deg",&PolyEntry::leadDeg)
  .def_readwrite("gcd_of_terms",&PolyEntry::gcdOfTerms)
  //.def_readwrite("usedVariables",PolyEntry::usedVariables)
  //.def_readwrite("p",PolyEntry::tailVariables)
  .def_readwrite("tail",&PolyEntry::tail)
  .def("ecart",&PolyEntry::ecart)
  .def_readwrite("minimal",&PolyEntry::minimal)
  .def("recompute_information",&PolyEntry::recomputeInformation);
  
  implicitly_convertible<BoolePolynomial, PolyEntry>();
 

  boost::python::class_<ReductionStrategy> ("ReductionStrategy",
					    "ReductionStrategy",
					    init<const BoolePolyRing&>())
        .def_readwrite("opt_brutal_reductions",&ReductionStrategy::optBrutalReductions)
        .def("add_generator", &ReductionStrategy::addGenerator)
        .def_readonly("leading_terms",&ReductionStrategy::leadingTerms)
        .def_readonly("minimal_leading_terms",&ReductionStrategy::minimalLeadingTerms)
        .def_readwrite("opt_ll",&ReductionStrategy::optLL)
        .def("cheap_reductions", cheap_reductions)
        .def_readwrite("opt_red_tail",&ReductionStrategy::optRedTail)
        .def_readwrite("opt_red_tail_deg_growth",&ReductionStrategy::optRedTailDegGrowth)
        .def("can_rewrite",&ReductionStrategy::canRewrite)
        .def("nf",&ReductionStrategy::nf)
        .def("reduced_normal_form",&ReductionStrategy::reducedNormalForm)
        .def("head_normal_form",&ReductionStrategy::headNormalForm)
        .def_readonly("monomials",&ReductionStrategy::monomials);
  
  boost::python::class_<GroebnerStrategy>("GroebnerStrategy", 
                                          "Groebner Strategy",
                                          init<const BoolePolyRing&>())
  .def(init<const GroebnerStrategy&>())
  .def("suggest_plugin_variable",&GroebnerStrategy::suggestPluginVariable)
  .def("add_generator", add_generator)//&GroebnerStrategy::addGenerator)
  .def("add_generator_delayed", add_generator_delayed)
  .def("ll_reduce_all", &GroebnerStrategy::llReduceAll)
  .def("add_as_you_wish",add_as_you_wish)
  .def("implications",implications)
  .def_readonly("reduction_strategy",&GroebnerStrategy::generators)
  
  .def("red_tail",&GroebnerStrategy::redTail)
  .def("next_spoly", &GroebnerStrategy::nextSpoly)
  .def("some_spolys_in_next_degree", someNextDegreeSpolys)
  .def("__len__",nGenerators)
  .def("__iter__",range(stratbegin, stratend))
  .def("__getitem__", get_ith_gen)
  .def("__getitem__", get_gen_by_lead)
  
  .def("clean_top_by_chain_criterion", cleanTopByChainCriterion)
  .def("all_generators", &GroebnerStrategy::allGenerators)
  
#if defined(PBORI_HAVE_NTL) || defined(PBORI_HAVE_M4RI)
  .def("noro_step", &GroebnerStrategy::noroStep)
#endif
#if defined(PBORI_HAVE_NTL) || defined(PBORI_HAVE_M4RI)
  .def("faugere_step_dense", &GroebnerStrategy::faugereStepDense)
#endif
  .def("variable_has_value",&GroebnerStrategy::variableHasValue)
  .def_readonly("chain_criterions",&GroebnerStrategy::chainCriterions)

  
  
  .def_readwrite("opt_linear_algebra_in_last_block",&GroebnerStrategy::optLinearAlgebraInLastBlock)
  .def_readwrite("opt_modified_linear_algebra",
      &GroebnerStrategy::optModifiedLinearAlgebra)
  .def_readwrite("opt_lazy",&GroebnerStrategy::optLazy)
  .def_readwrite("opt_exchange",&GroebnerStrategy::optExchange)
  .def_readwrite("opt_allow_recursion",&GroebnerStrategy::optAllowRecursion)
  .def_readwrite("enabled_log",&GroebnerStrategy::enabledLog)
  .def_readwrite("opt_draw_matrices", &GroebnerStrategy::optDrawMatrices)
  .def_readwrite("matrix_prefix", &GroebnerStrategy::matrixPrefix) 
  .def_readonly("variable_chain_criterions",&GroebnerStrategy::variableChainCriterions)
  .def_readonly("easy_product_criterions",&GroebnerStrategy::easyProductCriterions)
  .def_readonly("extended_product_criterions",&GroebnerStrategy::extendedProductCriterions)
  .def("top_sugar",pairs_top_sugar)
  .def("contains_one",contains_one)
  .def("minimalize_and_tail_reduce",&GroebnerStrategy::minimalizeAndTailReduce)
  .def("minimalize",&GroebnerStrategy::minimalize)
	
  .def("select", select_wrapped)
  .def_readwrite("opt_red_by_reduced",&GroebnerStrategy::reduceByTailReduced)
  .def("symmGB_F2",&GroebnerStrategy::symmGB_F2)
  .def("nf",&GroebnerStrategy::nf)
  .def("npairs", npairs);
  def("translate_indices",translate_indices);
  def("mult_fast_sim_C",mult_fast_sim);
  def("mod_var_set",mod_var_set);
  def("interpolate",interpolate);
  def("interpolate_smallest_lex",interpolate_smallest_lex);
  def("contained_vars",contained_variables_cudd_style);
  def("map_every_x_to_x_plus_one",map_every_x_to_x_plus_one);
  boost::python::register_exception_translator<
              PolynomialIsZeroException>(translator_g);
  boost::python::register_exception_translator<
            DuplicateLeadException>(translator_d);
        boost::python::register_exception_translator<
                    StrategyIndexException>(translator_gi);
}
