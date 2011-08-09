# Copyright (c) 2005-2007 by The PolyBoRi Team
import pathadjuster
from polybori.blocks import Block, declare_ring
from itertools import ifilter,imap,repeat
from probstat import Cartesian
from polybori.PyPolyBoRi import *
import sys
class EquivalenceRelation(object):
  """this class represents an equivalent relation,
    which is implemented by repeated evaluatation of a map
    c[n]=m means that n is equivalent to m"""
  def __init__(self):
    self.mydict={}
  def canonical(self,var):
    while var in self.mydict:
      var=self.mydict[var]
    return var
  def isCanonical(self,var):
    if self.canonical(var)==var:
        return True
    else:
        return False
  def all_rewritings(self,var):
    pass
  def rewrite(self, a,b):
    a=self.canonical(a)
    b=self.canonical(b)    
    if not a==b:
      self.mydict[a]=b
  def __getitem__(self,key):
    return self.canonical(key)
  def __setitem__(self, val, key):
    self.rewrite(val,key)
    
    
class chaintrans(object):
  def __init__(self, chain,full):
    self.table={}
    self.i=1
    full=list(full)
    for c in full:
      if not c in chain.mydict:
        self.insert(c)
    for c in full:
      self.table[c]=self.table[chain[c]]
  def __getitem__(self, key):
    return self.table[key]
  def insert(self,key):
    self.table[key]=self.i
    self.i=self.i+1
  def __str__(self):
    return str(self.table)

class modPNumber:
  """simple class for Turaev/Viro colors,
    each color has an inverse, but it doesn't have to be an algebraic
    structure"""
  def __init__(self,i,n):
    self.val=i%n
    self.mod=n
  def __neg__(self):
    return modPNumber((-self.val)%self.mod,self.mod)
  def __hash__(self):
    return self.val
    #return hash((self.val, self.mod))
  def __eq__(self, other):
    return self.val==other.val
  def __repr__(self):
    return repr(self.val)
  def __str__(self):
    return str(self.val)

colors=3
value_range=[modPNumber(i,colors) for i in xrange(colors)]

wrel=EquivalenceRelation()
for i in value_range:
  wrel[i]=-i
weights_canonical_to_index=dict((weight,i) \
    for (i,weight) in enumerate(ifilter( \
        wrel.isCanonical,value_range)))
wtrans=dict((weight,weights_canonical_to_index[wrel.canonical(weight)]) for weight in \
    value_range)
weights=len(weights_canonical_to_index)


def constr_variations():
  return imap(tuple,Cartesian(list(repeat(value_range,6))))
relation=EquivalenceRelation()
for (a,b,c,d,e,f) in constr_variations():
  relation[(a,b,c,d,e,f)]=(b,c,a,f,-d,-e)
  relation[(a,b,c,d,e,f)]=(a,-d,-e,-b,-c,-f)
canonical_to_index=dict((symbol,i) for (i,symbol) in \
    enumerate(ifilter( \
       relation.isCanonical,constr_variations())))
vartrans=dict((symbol,canonical_to_index[relation.canonical(symbol)]) for symbol in \
    constr_variations())
symbols=len(canonical_to_index)


#r=create_ring(char=0,nvars=weights+symbols)
declare_ring([Block("w",weights),Block("s",symbols)],globals())
s_cache=[s(i) for i in xrange(symbols)]
w_cache=[w(i) for i in xrange(weights)]
def six_j_symbol(v):
  i=vartrans[v]
  return s_cache[i]#var_cache[i-1]
  

def weight(i):
  return w_cache[wtrans[i]]
  
  
myideal=set()
def polysum(l):
  acc=Polynomial(0)
  for p in l:
    acc+=p
  return acc

#var_cache=[singular_var(x+1) for x in range(singular.nvars(Ring()))]
#for (j1,j2,j3,j4,j5,j6,j7,j8,j9) in Cartesian(list(repeat(value_range,9))):
#  p=\
#    six_j_symbol((j1,j2,j3,j7,j8,j9))*\
#    six_j_symbol((j4,j5,j6,-j7,-j8,-j9))+\
#    polysum([\
#      weight(j)*six_j_symbol((j,j1,j2,-j4,-j5,j7))*\
#      six_j_symbol((j,j2,j3,-j5,-j6,j9))*
#      six_j_symbol((j,j3,j1,-j6,-j4,-j8))\
#      for j in value_range])
#  print len(myideal)
#  myideal.add(p)


myideal=set((
   six_j_symbol((j1,j2,j3,j7,j8,j9))*\
   six_j_symbol((j4,j5,j6,-j7,-j8,-j9))+\
   polysum([\
     weight(j)*six_j_symbol((j,j1,j2,-j4,-j5,j7))*\
     six_j_symbol((j,j2,j3,-j5,-j6,j9))*
     six_j_symbol((j,j3,j1,-j6,-j4,-j8))\
     for j in value_range])
   for (j1,j2,j3,j4,j5,j6,j7,j8,j9) in Cartesian(list(repeat(value_range,9)))))



#back_table_v=dict((canonical_to_index[s],s) for s\
#    in canonical_to_index)
#back_table_w=dict((weights_canonical_to_index[w],w) for w\
#    in weights_canonical_to_index)
#back_table_joint=dict(back_table_v)
#back_table_joint.update(back_table_w)
#print "back", back_table_joint
#print "original length",len(myideal)
#print "now calculating"
#myideal=singular.simplify(myideal,4)
#print "simplified", len(myideal)
#gb=singular.symmGB_F2_python(myideal)
#print gb
#print len(gb), "GB elements"
myideal=list(myideal)
sys.stdout.write('declare_ring([Block("w",'+str(weights)+'),Block("s",'+str(symbols)+')],globals())\n')
sys.stdout.write("ideal=[\n")
for p in myideal[:-1]:
  sys.stdout.write(str(p)+",\n")
sys.stdout.write(str(myideal[-1])+"\n]\n")

#for p in myideal:
#  print p,","
#print len(myideal)
