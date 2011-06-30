// -*- c++ -*-
//*****************************************************************************
/** @file PolynomialSugar.h 
 *
 * @author Michael Brickenstein 
 * @date 2011-06-30 
 *
 * This file includes the definition of the class @c PolynomialSugar.
 *
 * @par Copyright:
 *   (c) 2006-2010 by The PolyBoRi Team
 *
**/
//*****************************************************************************

#ifndef polybori_groebner_PolynomialSugar_h_
#define polybori_groebner_PolynomialSugar_h_

// include basic definitions
#include "groebner_defs.h"

BEGIN_NAMESPACE_PBORIGB

/** @class PolynomialSugar
 * @brief This class defines PolynomialSugar.
 *
 **/
class PolynomialSugar{
public:
  PolynomialSugar(const Polynomial& poly): lm(poly.ring()), exp(), p(poly) {
    sugar=p.deg();
    if (!(p.isZero())){
      this->lm=p.boundedLead(sugar);
      this->exp=lm.exp();
      assert(lm==p.lead());
      assert(exp==p.leadExp());
    }

    length=p.length();
  }
  PolynomialSugar(const Polynomial& poly, int sugar, len_type length):
    lm(poly.ring()), exp(), p(poly) {

    assert(length>=0);
    
    //sugar=p.deg();
    this->sugar=sugar;
    this->length=length;
    assert(sugar>=p.deg());
    assert(length>=p.length());
    if (!(p.isZero())){
      this->lm=p.boundedLead(sugar);
      this->exp=lm.exp();
      assert(lm==p.lead());
      assert(exp==p.leadExp());
    }
  }
  const BooleMonomial& lead() const{
    return this->lm;
  }
  const Exponent& leadExp() const{
    return this->exp;
  }
  deg_type getSugar() const{
    return sugar;
  }
  wlen_type getLengthEstimation() const {
    return length;
  }
  bool isZero() const{
    return p.isZero();
  }
  void add(const Polynomial p2, deg_type sugar2, wlen_type length){
    assert(p2.leadExp()==exp);
    assert(length>=0);
    assert(length>=p2.length());
    this->p=p+p2;
    this->sugar=std::max(sugar2,this->sugar);

    if (!(p.isZero())){
      this->lm=this->p.boundedLead(sugar);
      this->exp=this->lm.exp();
    } else {
      lm=Monomial(p2.ring());
      exp=Exponent();
    }
    this->length+=length;
    this->length-=2;
    if (p2.ring().ordering().isTotalDegreeOrder()) this->sugar=this->lm.deg();
    
    assert((p.isZero())|| (lm==p.lead()));
    assert((p.isZero())||(exp==p.leadExp()));
  }
  void adjustSugar(){
    sugar=p.deg();
  }
  bool isOne(){
    return p.isOne();
  }
  Polynomial value() const{
    return p;
  }
  wlen_type eliminationLength() const{
    ///@todo optimize that using length optimization
    wlen_type res=1;
    if (isZero()) return 0;
    res=res+(sugar-exp.deg()+1)*(length-1);
    assert(res>=p.eliminationLengthWithDegBound(sugar));
    return res;
    //return p.eliminationLengthWithDegBound(sugar);
  }
  void adjustLm(){
    this->lm=this->p.lead();
    exp=lm.exp();
    assert(lm==p.lead());
    assert(exp==p.leadExp());
  }
protected:
  Monomial lm;
  len_type length;
  deg_type sugar;
  Polynomial p;
  Exponent exp;
};

END_NAMESPACE_PBORIGB

#endif /* polybori_PolynomialSugar_h_ */
