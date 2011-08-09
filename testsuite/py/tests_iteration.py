# Copyright (c) 2005-2007 by The PolyBoRi Team

import unittest
from fpformat import fix
from sys import path
import pathadjuster
from polybori.PyPolyBoRi import *
from time import clock, time
import StringIO
import sys
from polybori.blocks import declare_ring,Block
from re import match
from polybori.gbrefs import my_import,load_data, clean_data, SINGLE
from random import Random
times={}
class IterTestCase(unittest.TestCase):
    pass
def pot_set(start,end):
    res=Polynomial(1)
    for i in xrange(end-1,start-1,-1):
        res=res+Monomial(Variable(i))*res
    return res

def add_iteration_test_case(p, method, test_class=IterTestCase,ordering="lp",name=None, blocks=range(10,100,10)):
    assert name

    name=name+"_"+method.__name__+"_"+ordering
    if match("block",ordering):
        name=name+"_"+"_".join([str(b) for b in blocks])
    def test_method(self):
        

        change_ordering(getattr(OrderCode, ordering))
        if match("block",ordering):
            for s in blocks:
                append_ring_block(s)
        t=time()
        l1=method(p)
        t2=time()
        l2=len(p)
        sys.stderr.write(str(round(t2-t,2))+"s\n")
        times[name]=t2-t
        self.assertEquals(l1,l2)
        self.assertEquals(list(p.terms()),sorted(list(p.terms()),reverse=True))

    test_method.__name__="test_"+name
    setattr(test_class,"test_"+name, test_method)

#for i in [12]:
#      name="et.easytop.mult"+str(i)+"x"+str(i)+"mit"
#      add_unsat_test_case(UnSatTestCaseWeekend,name)
class mymain(unittest.main):
  def runTests(self):
          if self.testRunner is None:
              self.testRunner = unittest.TextTestRunner(verbosity=self.verbosity)
          result = self.testRunner.run(self.test)
          for f in sorted(times):
              print f, max(25-len(f),0)*" ", ":", fix(times[f],2)
          # cleaning up tests (deletion because they own copies of polynomials)
          for attr in dir(IterTestCase):
              if match("test_", attr):
                  delattr(IterTestCase, attr)
          sys.exit(not result.wasSuccessful())
          
def add_iteration_test_case_all_methods(p,name):
    methods_lp=[test_iterate_reference_ordered,test_iterate_lex,test_iterate_ordered]
    methods_general=[test_iterate_reference_ordered,test_iterate_ordered]
    for o in ["dp_asc","dlex","block_dlex","block_dp_asc"]:
        for m in methods_general:
            add_iteration_test_case(p=p,method=m,name=name,ordering=o)
    for m in methods_lp:
        add_iteration_test_case(p=p,method=m,name=name)

def gen_random_poly(samples=10000,deg=10,vars=100,seed=123):
    myrange=range(vars)
    r=Random(seed)
    def helper(samples):
        if samples==0:
            return Polynomial(0)
        if samples==1:
            d=r.randint(0,deg)
            variables=r.sample(myrange,d)
            m=Monomial()
            for v in sorted(variables,reverse=True):
                m=Monomial(Variable(v))*m
            return Polynomial(m)
        assert samples>=2
        return helper(samples/2)+helper(samples-samples/2)
    return helper(samples)
        
if __name__=='__main__':
    r=declare_ring([Block("x",1000)],globals())
    for i in [4]+range(10,17):
        p=pot_set(0,i)
        add_iteration_test_case_all_methods(p,name="pot"+str(i))
    p=pot_set(0,16)+pot_set(8,24)
    add_iteration_test_case_all_methods(p,name="pot16p16")
    for (d,s) in [(15,1000),(3,1000),(50,5000),(15,5000),(3,5000),(50,5000),(15,10000),(3,10000),(50,10000)]:
      p=gen_random_poly(deg=d,samples=s)
      add_iteration_test_case_all_methods(p,name="r"+str(d)+"_"+str(s))
    
    del p
    mymain()
    #for f in times:
    #    print f, (25-len(f))*" ", ":", times[f]
