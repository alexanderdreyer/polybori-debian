# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import argv,path
import pathadjuster
from polybori.PyPolyBoRi import Monomial
from gbrefs import load_data, clean_data
data=argv[1]
data=load_data(data)
print "Equations", len([p for p in data.ideal if not p.isZero()])
m=Monomial()
for p in data.ideal:
    m=m*p.vars()
print "Variables", m.deg()
clean_data(data)
