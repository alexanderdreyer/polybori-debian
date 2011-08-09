# Copyright (c) 2005-2007 by The PolyBoRi Team
import unittest
from fpformat import fix
from sys import path
import pathadjuster
from polybori.PyPolyBoRi import *
from time import clock, time
import StringIO
import sys
import polybori.gbrefs
from polybori.blocks import declare_ring,Block
from re import match
from polybori.gbrefs import my_import,load_data, clean_data, SINGLE
from random import Random
times={}
class LeadTestCase(unittest.TestCase):
    pass
def pot_set(start,end):
    res=Polynomial(1)
    for i in xrange(end-1,start-1,-1):
        res=res+Monomial(Variable(i))*res
    return res

def add_test_case(g,code,name,blocks,test_class=LeadTestCase):
    assert name


    def test_method(self):
        
        (lm,p)=g()
         
        change_ordering(code)
        for s in blocks:
            append_ring_block(s)

        
        
        self.assertEquals(p.lead(),lm)
        iterated_order=tuple(p.terms())
        sorted_order=tuple(sorted(p.terms(),reverse=True))
        
        self.assertEquals(max(list(p.terms())),lm)
        self.assertEquals(sorted_order,iterated_order)
        
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

          sys.exit(not result.wasSuccessful())
          


def gen_random_poly(l,deg=10,vars_set=list(xrange(100)),seed=123):
    myrange=vars_set
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
    p=Polynomial(0)
    while(len(p)<l):
        p=Polynomial(p.set().union(helper(l-len(p)).set()))
    return p

def add_up_simple(l):
    v=BoolePolynomialVector()
    for p in l:
        v.append(Polynomial(p))
    return add_up_polynomials(v)


def gen_random_poly_two_blocks(l,block1_samples,block2_samples,block1_deg,block2_deg,block2_start,block2_end,simple_order_code,same_in_component1=False,seed=123):
    p1=gen_random_poly(block1_samples,block1_deg,list(xrange(block2_start)),seed)
    p2=gen_random_poly(block2_samples,block2_deg,list(xrange(block2_start,block2_end)),seed+1000)
    change_ordering(simple_order_code)
    lm1=p1.lead()
    lm2=p2.lead()
    if same_in_component1:
        r=Random(seed+2000)
        lm1=p1.lead()
        assert l>3
        assert block2_samples>=3
        three_cans=r.sample(p2.set(),3)
        front=max(three_cans)
        
        assert block1_samples>1
        p1_tail=p1+lm1
        return (lm1*front,add_up_simple([c*lm1 for c in three_cans]+r.sample(list((p1_tail*p2).set()),l-3)))
        
        
    else:
        p1=p1+lm1
        
        r=Random(seed+2000)
        lm_part2=gen_random_poly(1,block2_deg,list(xrange(block2_start,block2_end)),seed=seed+3000)
        lm=(lm1*lm_part2).lead()
        
        return (lm,add_up_simple(list(r.sample(list((p1*p2).set()),l-1))+[lm]))


def gen_random_poly_two_blocks_delayed(*args,**keywords):
    def generator():
        return gen_random_poly_two_blocks(*args,**keywords)
    return generator
if __name__=='__main__':
    r=declare_ring([Block("x",1000)],globals())
    #code=OrderCode.block_dlex
    b2=20
    for (simple_order_code,code,suffix) in\
        ((OrderCode.dlex,OrderCode.block_dlex,"dlex"),(OrderCode.dp_asc,OrderCode.block_dp_asc,"dp_asc")):
        for i in xrange(50):
            add_test_case(
                gen_random_poly_two_blocks_delayed(
                    l=100,block1_samples=40,block2_samples=40,block1_deg=5,block2_deg=8,block2_start=b2,block2_end=100,simple_order_code=simple_order_code,seed=i
                ),code,"random_first_comp_crit_"+suffix+str(i),blocks=[b2])
            add_test_case(
                gen_random_poly_two_blocks_delayed(
                    l=100,block1_samples=40,block2_samples=40,block1_deg=5,block2_deg=8,block2_start=b2,block2_end=100,simple_order_code=simple_order_code,seed=i,same_in_component1=True
                ),code,"random_second_comp_crit_"+suffix+str(i),blocks=[b2])

    
    mymain()
    #for f in times:

    #    print f, (25-len(f))*" ", ":", times[f]
