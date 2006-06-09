/*
 *  strategy_wrapper.cc
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 21.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "strategy_wrapper.h"
#include <iostream>
#include <vector>
#include <boost/python.hpp>
#include "nf.h"
#include <groebner_alg.h>
#include "slimgb_wrapper.h"
//#include <iostream>
//#include "polybori.h"
//#include "pbori_defs.h"
using namespace boost::python;
using namespace std;

USING_NAMESPACE_PBORIGB
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
static void printGenerators(GroebnerStrategy& strat){
  int i;
  for (i=0;i<strat.generators.size();i++){
    std::cout<<(strat.generators[i].p)<<std::endl;
  }
}
static vector<Polynomial> nextDegreeSpolys(GroebnerStrategy& strat){
  vector<Polynomial> res;
  assert(!(strat.pairs.pairSetEmpty()));
  strat.pairs.cleanTopByChainCriterion();
  deg_type deg=strat.pairs.queue.top().sugar;
  
  while((!(strat.pairs.pairSetEmpty())) &&(strat.pairs.queue.top().sugar<=deg)){
    
    assert(strat.pairs.queue.top().sugar==deg);
    res.push_back(strat.nextSpoly());
    strat.pairs.cleanTopByChainCriterion();
  }
  return res;
  
}

static vector<Polynomial> someNextDegreeSpolys(GroebnerStrategy& strat, int n){
  vector<Polynomial> res;
  assert(!(strat.pairs.pairSetEmpty()));
  strat.pairs.cleanTopByChainCriterion();
  deg_type deg=strat.pairs.queue.top().sugar;
  
  while((!(strat.pairs.pairSetEmpty())) &&(strat.pairs.queue.top().sugar<=deg) && (res.size()<n)){
    
    assert(strat.pairs.queue.top().sugar==deg);
    res.push_back(strat.nextSpoly());
    strat.pairs.cleanTopByChainCriterion();
  }
  return res;
  
}
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
void export_strategy(){
  export_slimgb();
  boost::python::class_<GroebnerStrategy>("GroebnerStrategy")
  .def(init<>())
  .def(init<const GroebnerStrategy&>())
  .def("addGenerator", &GroebnerStrategy::addGenerator)
  .def("addGeneratorDelayed", &GroebnerStrategy::addGeneratorDelayed)
  .def("implications",&GroebnerStrategy::addNonTrivialImplicationsDelayed)
  .def("nextSpoly", &GroebnerStrategy::nextSpoly)
  .def("allSpolysInNextDegree", nextDegreeSpolys)
  .def("someSpolysInNextDegree", someNextDegreeSpolys)
  .def("__len__",nGenerators)
  .def("cleanTopByChainCriterion", cleanTopByChainCriterion)
  .def("toStdOut", printGenerators)
  .def("variableHasValue",&GroebnerStrategy::variableHasValue)
  .def_readonly("chainCriterions",&GroebnerStrategy::chainCriterions)
  .def_readonly("variableChainCriterions",&GroebnerStrategy::variableChainCriterions)
  .def_readonly("easyProductCriterions",&GroebnerStrategy::easyProductCriterions)
  .def_readonly("extendedProductCriterions",&GroebnerStrategy::extendedProductCriterions)
  .def("topSugar",pairs_top_sugar)
  .def("containsOne",contains_one)
  .def("npairs", npairs);
  def("nf1",nf1);
  def("nf2",nf2);
  def("nf_delaying",nf_delaying);
  def("nf_delaying_exchanging", nf_delaying_exchanging);
  def("red_tail_self_tuning", red_tail_self_tuning);
}
