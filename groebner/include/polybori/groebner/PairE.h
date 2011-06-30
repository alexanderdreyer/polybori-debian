// -*- c++ -*-
//*****************************************************************************
/** @file PairE.h 
 *
 * @author Michael Brickenstein 
 * @date 2011-06-30 
 *
 * This file includes the definition of the class @c PairE.
 *
 * @par Copyright:
 *   (c) 2006-2010 by The PolyBoRi Team
 *
**/
//*****************************************************************************

#ifndef polybori_groebner_PairE_h_
#define polybori_groebner_PairE_h_

// include basic definitions
#include "groebner_defs.h"

BEGIN_NAMESPACE_PBORIGB

/** @class PairE
 * @brief This class defines PairE.
 *
 **/
class PairE{
private:
  int type;
public:
  int getType() const{
    return type;
  }
  wlen_type wlen;
  deg_type sugar;
  //three sorts of pairs
  //x*poly, poly, i,j
  pair_data_ptr data;
  Exponent lm; //must not be the real lm, can be lm of syzygy or something else

 PairE(const PairE& rhs):
  type(rhs.getType()), wlen(rhs.wlen), sugar(rhs.sugar), 
    data(rhs.data), lm(rhs.lm) {}


  Polynomial extract(const PolyEntryVector& v){
    return data->extract(v);
  }
  PairE(int i, int j, const PolyEntryVector &v):
    data(new IJPairData(i,j)),
    lm(v[i].leadExp+v[j].leadExp),
    wlen(v[i].weightedLength+v[j].weightedLength-2)
  {
    type=IJ_PAIR;
    sugar=lm.deg()+std::max(v[i].ecart(),v[j].ecart());
  }
  PairE(int i, idx_type v, const PolyEntryVector &gen,int type):
    data(new VariablePairData(i,v)),
    sugar(gen[i].deg+1),
   // sugar(gen[i].lmDeg+1),///@only do that because of bad criteria impl
    wlen(gen[i].weightedLength+gen[i].length),
  lm(gen[i].leadExp)
  
  {
    assert(type==VARIABLE_PAIR);
    this->type=type;
    if (gen[i].leadExp==gen[i].usedVariables)
        sugar=gen[i].deg;
    if (gen[i].tailVariables.deg()<gen[i].deg)
        sugar=gen[i].deg;
  }
  
  PairE(const Polynomial& delayed):
    data(new PolyPairData(delayed)),
    //lm(delayed.lead()),
    lm(delayed.leadExp()),
    sugar(delayed.deg()), wlen(delayed.eliminationLength()){
      this->type=DELAYED_PAIR;
  }
  
};

END_NAMESPACE_PBORIGB

#endif /* polybori_PairE_h_ */
