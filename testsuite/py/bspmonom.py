# Copyright (c) 2005-2007 by The PolyBoRi Team


from polybori.PyPolyBoRi import *
r=Ring(5)
a=Variable(0)
b=Variable(1)

m=Monomial(a)*Monomial(b)

m


for i in m:
    print i


print "finished"
