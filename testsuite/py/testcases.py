# Copyright (c) 2005-2007 by The PolyBoRi Team
from polybori.PyPolyBoRi import *
from random import Random
import copy
import sys
from nf import *

from optparse import OptionParser
linear_complete="linear_complete"
binomial_complete="quadratic_complete"
var_G="variables"
vp1_G="variables_p_1"
mixed_G="mixed"


parser = OptionParser()
parser.add_option("-n", "--nvars", dest="nvars",
                  help="number of variables", 
                  action="store", default=100, type="int")
parser.add_option("-p", "--psyco",
                  action="store_true", dest="psyco", default=False,
                  help="toggle psyco")
parser.add_option("-e", "--example",
                  action="store", dest="example", type="string", default=linear_complete,
                  help="choose f")
parser.add_option("-F", "--normal-form",
                  action="store", dest="nf", type="int", default=2,
                  help="choose normal form")
parser.add_option("-t", "--task",
                  action="store", dest="task", type="string", default="NF",
                  help="choose task from NF/GB")                  
                  
parser.add_option("-g", "--generators",
                  action="store", dest="G", type="string", default=mixed_G,
                  help="choose G")
(options, args) = parser.parse_args()


if options.psyco:
    import psyco
    psyco.full()
    print "using psyco"


nvars=options.nvars
r=Ring(nvars)

# if not "reducibleBy" in dir(Polynomial):
#     def reducibleBy(f,g):
#         lf=f.lead()
#         lg=g.lead()
#         
#         p=lf*lg
#         return p.deg()==lf.deg()
#     Polynomial.reducibleBy=reducibleBy

#var=Variable
def var(i):
    return Monomial(Variable(i))

#f=var(0)




if not options.example in [binomial_complete, linear_complete]:
    raise Exception("unknown example")
if options.example==binomial_complete:
    f=Polynomial()
    for i in xrange(nvars):
        f=f+var(i)
    f=Polynomial(f.set().unateProduct(f.set()))
    print "len(f): ",len(f)
    # qr=nvars
#     for (i,j) in ((i,j) for i in xrange(qr) for j in xrange(qr) if i>=j):
#         f=f+var(i)*var(j)
else:
    if options.example==linear_complete:
        f=var(0)
        for i in xrange(1,r.nVars()):
            f=f+var(i)



one=Polynomial(r.one())
if not options.G in [mixed_G,var_G, vp1_G]:
    raise Exception("unknown generating system G")
if options.G==mixed_G:
    G=[var(i) for i in xrange(0,nvars,2)]+[var(i) + one for i in xrange(1,nvars,2)]
if options.G==var_G:
    G=[var(i) for i in xrange(0,nvars)]
if options.G==vp1_G:
    G=[var(i)+one for i in xrange(0,nvars)]

G=[Polynomial(g) for g in G]
for g in G:
    g.el=g.elength()

assert options.nf in range(1,5)


def generateStrategy(G):
    strat=GroebnerStrategy()
    for g in reversed(G):
        strat.addGenerator(g)
    print "pairs: ", strat.npairs()
    return strat
def nf1_hull(strat,f):
    return nf1(strat,f)
def nf2_hull(strat,f):
    return nf2(strat,f)
    
assert options.task in ["NF","GB"]
if options.task=="NF":
    if options.nf==1:
        cache=gen_divisor_cache(G)
        fr=NF_cached(f,G, cache)
    if options.nf==2:
        cache=gen_divisor_cache2(G)
        fr=NF_cached2(f,G, cache)
    
    if options.nf==3:
        strat=generateStrategy(G)
        fr=nf1_hull(strat,f)
    if options.nf==4:
        strat=generateStrategy(G)
        fr=nf2_hull(strat,f)

    print "nf vars: ", fr.nVars()
    print "nf: nodes ", fr.nNodes()
    print "nf: len", len(fr)
if options.task=="GB":

    print buchberger_C_based(G)
