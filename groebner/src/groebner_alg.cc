/*
 *  groebner_alg.ccc
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 20.04.06.
 *  Copyright 2006 Matematisches Forschungsinstitut Oberwolfach. All rights reserved.
 *
 */

#include "groebner_alg.h"
#include <algorithm>
BEGIN_NAMESPACE_PBORIGB
void PairManager::introducePair(const Pair& pair){
  queue.push(pair);
}
bool PairManager::pairSetEmpty(){
  return queue.empty();
}
Polynomial PairManager::nextSpoly(const PolyEntryVector& gen){
  assert(!(pairSetEmpty()));
  const IJPairData* ij= dynamic_cast<const IJPairData*>(queue.top().data.get());
  if (ij!=NULL){
    this->status.setToHasTRep(ij->i,ij->j);
  }
  Polynomial res=Pair(queue.top()).extract(gen);
  
  queue.pop();
  
  return res;
  
}

/// assumes that divisibility condition is fullfilled
class ChainCriterion{
public:
  const GroebnerStrategy* strat;
  int i,j;
  ChainCriterion(const GroebnerStrategy& strat, const int& i, const int& j){
    this->strat=&strat;
    this->i=i;
    this->j=j;
  }
  bool operator() (const Monomial& lm){
    int index=strat->lm2Index.find(lm)->second;
    //we know such an entry exists
    if ((index!=i)&&(index!=j)){
      if (strat->pairs.status.hasTRep(i,index) && strat->pairs.status.hasTRep(j,index)){
        
        return true;
      }
    }
  }
};
void PairManager::cleanTopByChainCriterion(){
  while(!(this->pairSetEmpty())){
    const IJPairData* ij= dynamic_cast<const IJPairData*>(queue.top().data.get());
    if (ij!=NULL){
    ///@todo implement this
      const int i=ij->i;
      const int j=ij->j;
      const Monomial lm=queue.top().lm;
      const BooleSet lms=this->strat->leadingTerms.intersect(lm.divisors());
      if (std::find_if(lms.begin(),lms.end(),ChainCriterion(*(this->strat),i,j))!=lms.end()){
        this->queue.pop();
        strat->pairs.status.setToHasTRep(i,j);
      } else {
        return;
      }
    } else
      return;
  }
}
PolyEntry::PolyEntry(const Polynomial &p){
  this->p=p;
  this->lm=p.lead();
  this->weightedLength=p.eliminationLength();
  this->deg=p.deg();
  this->lmDeg=p.lmDeg();
}
void GroebnerStrategy::addGenerator(const BoolePolynomial& p){
  PolyEntry e(p);
  
  //do this before adding leading term
  Monomial::const_iterator it=e.lm.begin();
  Monomial::const_iterator end=e.lm.end();
  BooleSet intersecting_terms=this->leadingTerms;
  while(it!=end){
    intersecting_terms=intersecting_terms.subset0(*it);
    it++;
    
  }
  leadingTerms.uniteAssign(Polynomial(e.lm).diagram());
  
  generators.push_back(e);
  pairs.status.prolong(PairStatusSet::HAS_T_REP);
  const int s=generators.size()-1;
  lm2Index[generators[s].lm]=s;

  
  int i;
  /*for(i=0;i<s;i++){
    if (GCD(this->generators[i].lm, generators[s].lm).deg()>0){
      this->pairs.introducePair(Pair(i,s,generators));
    } else{
      //product criterion
      this->pairs.status.calculated(i,s);
    }
  }*/
  
  
  
  
  it=generators[s].lm.begin();
  end=generators[s].lm.end();
  while(it!=end){
    this->pairs.introducePair(Pair(s,*it,generators,VARIABLE_PAIR));
    it++;
    
  }
  intersecting_terms= this->leadingTerms.diff(intersecting_terms);
  BooleSet::const_iterator is_it=intersecting_terms.begin();
  BooleSet::const_iterator is_end=intersecting_terms.end();
  while(is_it!=is_end){
    int index =this->lm2Index[*is_it];
    if (index!=s){
      //product criterion doesn't hold
      this->pairs.introducePair(Pair(index,s,generators));
      this->pairs.status.setToUncalculated(index,s);
    }
    is_it++;
  }
}

void GroebnerStrategy::addGeneratorDelayed(const BoolePolynomial& p){
  this->pairs.introducePair(Pair(p));
}
END_NAMESPACE_PBORIGB
