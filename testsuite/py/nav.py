# Copyright (c) 2005-2007 by The PolyBoRi Team

from polybori.PyPolyBoRi import *
from random import Random
import copy
import sys
from nf import *
import parse





def find_ways(nav, path):
    if nav.constant():
        if nav.terminalOne():
            yield path
    else:
        v=nav.value()
        #path=path+(v,)
        for p in find_ways(nav.thenBranch(), path+(v,)):
            yield p
        for p in find_ways(nav.elseBranch(), path):
            yield p
      

def support(p):
    return list(find_ways(p.navigation(),()))


if __name__=="__main__":    
    (r,p)=parse.translate_ideal("u*x+v*w+v*x+x*y+w*x+x*y*z", ["u", "v","w","x","y","z"])
    p=p[0]
    
    p.plot("tree.dot")
    nav=p.navigation()
    
    print len(p)      
    for w in find_ways(nav,()):
        print w
    
    
    
    x=Polynomial(Variable(3))
    x=x.set()
    p=p.set()
    q=p.change(3).divide(x)#.weakDivide(x)
    q2=p.subset0(3)
    print support(p)
    print support(q)
    print support(q2)
