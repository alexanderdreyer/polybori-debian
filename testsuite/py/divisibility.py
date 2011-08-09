# Copyright (c) 2005-2007 by The PolyBoRi Team

from polybori.PyPolyBoRi import *
from random import Random
import copy
rand=Random(12345)

nvars=10
r=Ring(nvars)

def random_reducibility_test():
    fset=set()
    gset=set()
    f=Polynomial(r.one())
    g=Polynomial(r.one())
    for i in xrange(7):
        z=rand.randrange(nvars)
        fset.add(z)
        #print repr(f)
        f=f*Polynomial(Variable(z))
    for j in xrange(2):
        z=rand.randrange(nvars)
        gset.add(z)
        g=g*Polynomial(Variable(z))
    result=f.reducibleBy(g)
    print fset, gset, result
    assert result==(fset>=gset)
    
for i in xrange(100):
    random_reducibility_test()


