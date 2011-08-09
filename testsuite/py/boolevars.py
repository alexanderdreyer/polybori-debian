# Copyright (c) 2005-2007 by The PolyBoRi Team
from polybori.PyPolyBoRi import *
r=Ring(5)
x=Variable(0)
y=Variable(1)
sum=Polynomial(x)


print "x:"
sum.toStdOut()
print "y:"
y.toStdOut()

sum+=y
print "sum:"
sum.toStdOut()
#del sum,x,y
#need a better solution
print "finished"
