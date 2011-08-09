# Copyright (c) 2005-2007 by The PolyBoRi Team

# 
# [1]:
#    _[1]=x(1)^2+x(1)
#    _[2]=x(2)^2+x(2)
#    _[3]=x(3)^2+x(3)
#    _[4]=x(4)^2+x(4)
#    _[5]=x(5)^2+x(5)
#    _[6]=x(6)^2+x(6)
#    _[7]=x(7)^2+x(7)
#    _[8]=x(8)^2+x(8)
#    _[9]=x(1)*x(2)+x(1)*x(3)+x(1)*x(5)+x(1)+x(2)*x(3)+x(2)*x(4)+x(2)*x(5)+x(3)*x(4)+x(4)*x(5)+x(4)
#    _[10]=x(1)*x(2)+x(1)+x(2)+x(3)*x(4)+x(3)+x(4)*x(5)+x(4)+x(5)
#    _[11]=x(1)*x(4)+x(2)*x(3)+x(2)*x(5)+x(3)*x(4)+x(3)+x(4)*x(5)+x(4)+x(5)+1
#    _[12]=x(1)*x(2)+x(1)*x(4)+x(1)+x(2)*x(3)+x(2)*x(5)+x(2)+1
# [2]:
#    [1]:
#       0,1,0,1,0
#    [2]:
#       1,0,0,0,0

IS="""
x1*x2+x1*x3+x1*x5+x1+x2*x3+x2*x4+x2*x5+x3*x4+x4*x5+x4,
x1*x2+x1+x2+x3*x4+x3+x4*x5+x4+x5,
x1*x4+x2*x3+x2*x5+x3*x4+x3+x4*x5+x4+x5+1,
x1*x2+x1*x4+x1+x2*x3+x2*x5+x2+1;"""

from polybori.PyPolyBoRi import *
from nf import *
import parse
import nav




(r,I)=parse.translate_ideal(IS, ["x"+str(i) for i in xrange(1,25+1)])

print I
print len(I)
#for i in I:
#    print len(i)
I= buchberger_C_based2(I)
