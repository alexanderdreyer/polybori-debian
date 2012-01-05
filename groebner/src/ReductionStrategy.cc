// -*- c++ -*-
//*****************************************************************************
/** @file ReductionStrategy.cc 
 *
 * @author Michael Brickenstein 
 * @date 2011-06-30 
 *
 * This file includes the definition of the class @c ReductionStrategy.
 *
 * @par Copyright:
 *   (c) 2006-2010 by The PolyBoRi Team
 *
**/
//*****************************************************************************


// include basic definitions
#include <polybori/groebner/ReductionStrategy.h>
#include <polybori/groebner/LessWeightedLengthInStrat.h>
#include <polybori/groebner/LessWeightedLengthInStratModified.h>
#include <polybori/groebner/nf.h>
#include <polybori/groebner/red_tail.h>
#include <polybori/groebner/ll_red_nf.h>

BEGIN_NAMESPACE_PBORIGB



template <class Iterator>
inline void 
ReductionStrategy::unmarkNonminimalLeadingTerms(const MonomialSet& lm,
                                                Iterator mfm_start, Iterator mfm_end) {
  while (mfm_start != mfm_end){
    PBORI_ASSERT((*mfm_start) != *lm.expBegin());
    PBORI_ASSERT((*mfm_start).reducibleBy(*lm.expBegin()));

    access(*mfm_start).minimal = false;
    ++mfm_start;
  }
}

inline void 
ReductionStrategy::removeNonminimalLeadingTerms(const MonomialSet& lm,
                                                MonomialSet lm_multiples_min) {
  lm_multiples_min = lm_multiples_min.diff(lm);
  PBORI_ASSERT(lm_multiples_min.intersect(minimalLeadingTerms).intersect(lm).isZero());

  unmarkNonminimalLeadingTerms(lm, lm_multiples_min.expBegin(), lm_multiples_min.expEnd());
  minimalLeadingTerms = minimalLeadingTerms.diff(lm_multiples_min).unite(lm);
}


inline void 
ReductionStrategy::updateLeadingTerms(const PolyEntry& entry) {

  const MonomialSet& terms = entry.lead.set();
  leadingTerms = leadingTerms.unite(terms);

  //doesn't need to be undone on simplification
  if (entry.literal_factors.is11Factorization())
    leadingTerms11 = leadingTerms11.unite(terms);
  
  if (entry.literal_factors.is00Factorization())
    leadingTerms00 = leadingTerms00.unite(terms);
}

inline void
ReductionStrategy::updateMinimalLeadingTerms(PolyEntry& entry) {

  const Monomial& lm = entry.lead;
  MonomialSet divisors = minimalLeadingTerms.divisorsOf(lm);
  if(divisors.isZero())
    removeNonminimalLeadingTerms(lm.set(), minimalLeadingTerms.multiplesOf(lm));
  else if (!(divisors.diff(lm.set()).isZero()))
    entry.minimal = false;
}

inline void
ReductionStrategy::updateMonomials(const PolyEntry& entry) {

  if (entry.length == 1){
    PBORI_ASSERT(entry.p.length() == 1);
    monomials = monomials.unite(entry.p);
  }
}


inline void
ReductionStrategy::insertIntoLLReductor(const PolyEntry& entry) {

  Polynomial poly = ll_red_nf(entry.p, llReductor);
  PBORI_ASSERT(poly.lead() == entry.lead);

  llReductor = recursively_insert(poly.navigation().elseBranch(),
                                  entry.lead.firstIndex(),
                                  ll_red_nf(llReductor, poly.set()));
  exchange(entry.lead, poly);
}

inline void
ReductionStrategy::updateLLReductor(const PolyEntry& entry) {

  if ( (entry.leadDeg == 1) && 
       (*(entry.p.navigation()) == entry.lead.firstIndex() ) ) {

    PBORI_ASSERT (!(llReductor.isZero()));
    if (!llReductor.expBegin()->reducibleBy(entry.lead.firstIndex()))
      insertIntoLLReductor(entry);
  }
}

void ReductionStrategy::setupSetsForElement(PolyEntry& entry) {

    PBORI_ASSERT(entry.lead.exp() == entry.leadExp);

    updateMinimalLeadingTerms(entry);
    updateLeadingTerms(entry);
    updateMonomials(entry);

    #ifdef LL_RED_FOR_GROEBNER
    if (optLL)
      updateLLReductor(entry);
    #endif
}


int
ReductionStrategy::select_short_by_terms(const MonomialSet& terms) const {
  MonomialSet ms(leadingTerms.intersect(terms));
  int res = minimum(ms.begin(), ms.end(), LessWeightedLengthInStrat(*this));

  if (res == -1 || (*this)[res].weightedLength<=2)
    return res;

  return -1;
}
 

typedef LessWeightedLengthInStratModified StratComparerForSelect;


int
ReductionStrategy::select1(const Polynomial& p) const {

#ifdef LEX_LEAD_RED_STRAT
  if (p.ring().ordering().isLexicographical()) {
    MonomialSet ms = leadingTerms.divisorsOf(p.lexLead());
    return (ms.isZero()?  -1:  index(*ms.expBegin()));
  }
#endif

  return select1(p.lead());
}

int
ReductionStrategy::select1(const Monomial& m) const {
  MonomialSet ms(leadingTerms.divisorsOf(m));
  return minimum(ms.expBegin(), ms.expEnd(), StratComparerForSelect(*this));
}

Polynomial
ReductionStrategy::reducedNormalForm(const Polynomial& p) const {
  
  return red_tail(*this, headNormalForm(p));
}

Polynomial
ReductionStrategy::headNormalForm(const Polynomial& p) const {
  if UNLIKELY(p.isZero()) return p;
    
  return (p.ring().ordering().isDegreeOrder()?
	  nf3_degree_order(*this, p, p.lead()): nf3(*this, p, p.lead()));
}



END_NAMESPACE_PBORIGB
