# Copyright (c) 2005-2007 by The PolyBoRi Team


from polybori.PyPolyBoRi import *
def mult_fast_sim_lex_smallest(to_mult, vars_positively_assigned=None):
    if vars_positively_assigned is None:
      vars_positively_assigned=()
      #vars_positively_assigned contains the temporary choosen indices, which are supposed to occur in the lex. smallest term in the result
    to_mult=[p for p in to_mult if not p.isOne()]
    #to_mult: the polynomials, we want to multiply
    for p in to_mult:
      if p.isZero():
        return (Polynomial(0), vars_positively_assigned)# this multiplication branch is 0, dummy result
    if len(to_mult)==0:
        return (Polynomial(1),vars_positively_assigned)# product over the empty set is 1
    to_mult=set(to_mult)
    #eliminate duplicates
    
    if len(to_mult)==1:
        return (Polynomial(list(list(to_mult)[0])[-1]),vars_positively_assigned)
    #product of one polynomial is the polynomial itself
    index=min([p.navigation().value() for p in to_mult])
    to_mult_new=[]
    prod=Polynomial(1)
    for p in to_mult:
      if len(p)<=2:
        prod=prod*p
      else:
        to_mult_new.append(p)
    SMALL_CONST=1000
    for i in reversed(xrange(0,len(to_mult_new)-1,2)):
      if len(to_mult_new[i])<SMALL_CONST and len(to_mult_new[i+1])<SMALL_CONST:
        to_mult_new[i]=to_mult_new[i]*to_mult_new[i+1]
        del to_mult_new[i+1]
    if (not prod.isOne()) and len(to_mult_new)==0:
      to_mult=[prod]
    else:
      to_mult=[prod*p for p in to_mult_new]
    
    #smallest index occuring in equations
    print index
    
    #if p=a*Variable(index)+b, Variable(index) doesn't occur in a,b, then a=p.subset1(index), b=p.subset2(index)
    (s0,vp)=mult_fast_sim_lex_smallest([Polynomial(p.set().subset0(index)) for p in to_mult],vars_positively_assigned)
    if s0.isZero():
      #we prefer the s0 branch, as we want to have the lex smallest term
      (s1,vp)=mult_fast_sim_lex_smallest([Polynomial(p.set().subset0(index)) + Polynomial(p.set().subset1(index)) for p in to_mult],vars_positively_assigned+(index,))
      return (s1,vp)
    else:
      return (s0,vp)
    
