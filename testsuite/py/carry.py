# Copyright (c) 2005-2007 by The PolyBoRi Team

import sys
sys.path.append("../../PyPolyBoRi")
from blocks import declare_ring,Block,AlternatingBlock
from polybori.PyPolyBoRi import *
n=2048
#declare_ring([Block("a",n,reverse=True),Block("b",n,reverse=True)],globals())
declare_ring([AlternatingBlock(("a","b"),n,reverse=True)],globals())
carries=[Polynomial(0)]
for i in xrange(n):
  print i, ":"
  c=1+(1+a(i)*b(i))*(1+carries[-1]*a(i))*(1+carries[-1]*b(i))
  print c.set().nNodes(), len(c)
  carries.append(c)
