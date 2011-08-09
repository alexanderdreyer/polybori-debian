# Copyright (c) 2005-2007 by The PolyBoRi Team

from probstat import Cartesian
from optparse import OptionParser
from itertools import repeat

from sys import path
path.append("../../PyPolyBoRi")
#from data import stas1
from nf import *
from re import *
from polybori.PyPolyBoRi import *
ord="dlex"
r=Ring(4,getattr(OrderCode,ord))
def x(i):
    return Variable(i)
    
p=x(0)+x(1)+x(2)+x(3)+1
s=p.set()
total=Polynomial(s.unateProduct(s).unateProduct(s).unateProduct(s))
print len(total)
print total
assert len(total)==16
terms=list(total)
loop=0
import nf
nf.PROT=False
def t2i(t):
    res=0
    for v in t:
        res=res+pow(2,v)
    return res
def p2i(p):
    res=0
    for t in p:
        res=res+pow(2,t2i(t))
    return res

res={0:0}
if __name__=='__main__':
    for e in Cartesian(list(repeat([0,1],len(terms)))):
        loop=loop+1
        print "loop:", loop
        p=Polynomial(0)
        for i in xrange(len(terms)):
            if e[i]==1:
                p=p+terms[i]
        print "Input:", p
        print "encoded", p2i(p)
        print "Result:"
        strat=GroebnerStrategy()
        
        if p!=Polynomial(0):
            strat.addGenerator(p)
            I=buchberger_C_based2(strat)
            l=[]
            for p_res in I.minimalizeAndTailReduce():
                print p_res
                print "gb element encoded:", p2i(p_res)
                l.append(p2i(p_res))
            res[p2i(p)]=l
     
        print "---------------"
    res_file=open("gb_dict4"+ord,"w")
    res_file.write(repr(res))
    res_file.close()
    print res
