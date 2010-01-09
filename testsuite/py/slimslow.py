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
x10^2+x10+x11^2*x12+x11*x12^2,
x9^2+x9+x10^2+x11^3+x11*x12^2+x12^3,
x4^2+x4+x5^2*x6+x5*x6^2,
x3^2+x3+x4^2+x5^3+x5*x6^2+x6^3,
x2+x8+x14,
x1+x7+x13,
x1*x6+x2*x5+x2*x6+x7*x12+x8*x11+x8*x12+x16,
x1*x5+x2*x6+x7*x11+x8*x12+x15,
x1*x4+x2*x3+x2*x4+x7*x10+x8*x9+x8*x10+x18,
x1*x3+x2*x4+x7*x9+x8*x10+x17,
x1*x6^2+x2*x5^2+x7*x12^2+x8*x11^2+x20,
x1*x5^2+x1*x6^2+x2*x6^2+x7*x11^2+x7*x12^2+x8*x12^2+x19,
x1*x3*x6+x1*x4*x5+x1*x4*x6+x2*x3*x5+x2*x3*x6+x2*x4*x5+x7*x9*x12+x7*x10*x11+x7*x10*x12+x8*x9*x11+x8*x9*x12+x8*x10*x11+x22,
x1*x3*x5+x1*x4*x6+x2*x3*x6+x2*x4*x5+x2*x4*x6+x7*x9*x11+x7*x10*x12+x8*x9*x12+x8*x10*x11+x8*x10*x12+x21,
x3^3*x5^2*x6+x3^3*x5^2*x12+x3^3*x5*x6^2+x3^3*x5*x12^2+x3^3*x6^2*x11+x3^3*x6*x11^2+x3^3*x11^2*x12+x3^3*x11*x12^2+x3^2*x4*x5^3+x3^2*x4*x5^2*x6+x3^2*x4*x5^2*x11+x3^2*x4*x5^2*x12+x3^2*x4*x5*x11^2+x3^2*x4*x6^3+x3^2*x4*x6^2*x12+x3^2*x4*x6*x11^2+x3^2*x4*x6*x12^2+x3^2*x4*x11^3+x3^2*x4*x11^2*x12+x3^2*x4*x12^3+x3^2*x4+x3^2*x5^3*x10+x3^2*x5^2*x6*x9+x3^2*x5^2*x6*x10+x3^2*x5^2*x9*x12+x3^2*x5^2*x10*x11+x3^2*x5^2*x10*x12+x3^2*x5*x6^2*x9+x3^2*x5*x9*x12^2+x3^2*x5*x10*x11^2+x3^2*x6^3*x10+x3^2*x6^2*x9*x11+x3^2*x6^2*x10*x12+x3^2*x6*x9*x11^2+x3^2*x6*x10*x11^2+x3^2*x6*x10*x12^2+x3^2*x9*x11^2*x12+x3^2*x9*x11*x12^2+x3^2*x10*x11^3+x3^2*x10*x11^2*x12+x3^2*x10*x12^3+x3^2*x10+x3*x4^2*x5^3+x3*x4^2*x5^2*x11+x3*x4^2*x5*x6^2+x3*x4^2*x5*x11^2+x3*x4^2*x5*x12^2+x3*x4^2*x6^3+x3*x4^2*x6^2*x11+x3*x4^2*x6^2*x12+x3*x4^2*x6*x12^2+x3*x4^2*x11^3+x3*x4^2*x11*x12^2+x3*x4^2*x12^3+x3*x4^2+x3*x5^3*x10^2+x3*x5^2*x6*x9^2+x3*x5^2*x9^2*x12+x3*x5^2*x10^2*x11+x3*x5*x6^2*x9^2+x3*x5*x6^2*x10^2+x3*x5*x9^2*x12^2+x3*x5*x10^2*x11^2+x3*x5*x10^2*x12^2+x3*x6^3*x10^2+x3*x6^2*x9^2*x11+x3*x6^2*x10^2*x11+x3*x6^2*x10^2*x12+x3*x6*x9^2*x11^2+x3*x6*x10^2*x12^2+x3*x9^2*x11^2*x12+x3*x9^2*x11*x12^2+x3*x10^2*x11^3+x3*x10^2*x11*x12^2+x3*x10^2*x12^3+x3*x10^2+x4^3*x5^2*x6+x4^3*x5^2*x12+x4^3*x5*x6^2+x4^3*x5*x12^2+x4^3*x6^2*x11+x4^3*x6*x11^2+x4^3*x11^2*x12+x4^3*x11*x12^2+x4^2*x5^3*x9+x4^2*x5^2*x6*x10+x4^2*x5^2*x9*x11+x4^2*x5^2*x10*x12+x4^2*x5*x6^2*x9+x4^2*x5*x6^2*x10+x4^2*x5*x9*x11^2+x4^2*x5*x9*x12^2+x4^2*x5*x10*x12^2+x4^2*x6^3*x9+x4^2*x6^2*x9*x11+x4^2*x6^2*x9*x12+x4^2*x6^2*x10*x11+x4^2*x6*x9*x12^2+x4^2*x6*x10*x11^2+x4^2*x9*x11^3+x4^2*x9*x11*x12^2+x4^2*x9*x12^3+x4^2*x9+x4^2*x10*x11^2*x12+x4^2*x10*x11*x12^2+x4*x5^3*x9^2+x4*x5^2*x6*x9^2+x4*x5^2*x6*x10^2+x4*x5^2*x9^2*x11+x4*x5^2*x9^2*x12+x4*x5^2*x10^2*x12+x4*x5*x6^2*x10^2+x4*x5*x9^2*x11^2+x4*x5*x10^2*x12^2+x4*x6^3*x9^2+x4*x6^2*x9^2*x12+x4*x6^2*x10^2*x11+x4*x6*x9^2*x11^2+x4*x6*x9^2*x12^2+x4*x6*x10^2*x11^2+x4*x9^2*x11^3+x4*x9^2*x11^2*x12+x4*x9^2*x12^3+x4*x9^2+x4*x10^2*x11^2*x12+x4*x10^2*x11*x12^2+x5^3*x9^2*x10+x5^3*x9*x10^2+x5^2*x6*x9^3+x5^2*x6*x9^2*x10+x5^2*x6*x10^3+x5^2*x6+x5^2*x9^3*x12+x5^2*x9^2*x10*x11+x5^2*x9^2*x10*x12+x5^2*x9*x10^2*x11+x5^2*x10^3*x12+x5^2*x12+x5*x6^2*x9^3+x5*x6^2*x9*x10^2+x5*x6^2*x10^3+x5*x6^2+x5*x9^3*x12^2+x5*x9^2*x10*x11^2+x5*x9*x10^2*x11^2+x5*x9*x10^2*x12^2+x5*x10^3*x12^2+x5*x12^2+x6^3*x9^2*x10+x6^3*x9*x10^2+x6^2*x9^3*x11+x6^2*x9^2*x10*x12+x6^2*x9*x10^2*x11+x6^2*x9*x10^2*x12+x6^2*x10^3*x11+x6^2*x11+x6*x9^3*x11^2+x6*x9^2*x10*x11^2+x6*x9^2*x10*x12^2+x6*x9*x10^2*x12^2+x6*x10^3*x11^2+x6*x11^2+x9^3*x11^2*x12+x9^3*x11*x12^2+x9^2*x10*x11^3+x9^2*x10*x11^2*x12+x9^2*x10*x12^3+x9^2*x10+x9*x10^2*x11^3+x9*x10^2*x11*x12^2+x9*x10^2*x12^3+x9*x10^2+x10^3*x11^2*x12+x10^3*x11*x12^2+x11^2*x12+x11*x12^2,
x3^3*x5^3+x3^3*x5^2*x11+x3^3*x5*x6^2+x3^3*x5*x11^2+x3^3*x5*x12^2+x3^3*x6^3+x3^3*x6^2*x11+x3^3*x6^2*x12+x3^3*x6*x12^2+x3^3*x11^3+x3^3*x11*x12^2+x3^3*x12^3+x3^3+x3^2*x4*x5^2*x6+x3^2*x4*x5^2*x12+x3^2*x4*x5*x6^2+x3^2*x4*x5*x12^2+x3^2*x4*x6^2*x11+x3^2*x4*x6*x11^2+x3^2*x4*x11^2*x12+x3^2*x4*x11*x12^2+x3^2*x5^3*x9+x3^2*x5^2*x6*x10+x3^2*x5^2*x9*x11+x3^2*x5^2*x10*x12+x3^2*x5*x6^2*x9+x3^2*x5*x6^2*x10+x3^2*x5*x9*x11^2+x3^2*x5*x9*x12^2+x3^2*x5*x10*x12^2+x3^2*x6^3*x9+x3^2*x6^2*x9*x11+x3^2*x6^2*x9*x12+x3^2*x6^2*x10*x11+x3^2*x6*x9*x12^2+x3^2*x6*x10*x11^2+x3^2*x9*x11^3+x3^2*x9*x11*x12^2+x3^2*x9*x12^3+x3^2*x9+x3^2*x10*x11^2*x12+x3^2*x10*x11*x12^2+x3*x4^2*x5^3+x3*x4^2*x5^2*x6+x3*x4^2*x5^2*x11+x3*x4^2*x5^2*x12+x3*x4^2*x5*x11^2+x3*x4^2*x6^3+x3*x4^2*x6^2*x12+x3*x4^2*x6*x11^2+x3*x4^2*x6*x12^2+x3*x4^2*x11^3+x3*x4^2*x11^2*x12+x3*x4^2*x12^3+x3*x4^2+x3*x5^3*x9^2+x3*x5^3*x10^2+x3*x5^2*x6*x10^2+x3*x5^2*x9^2*x11+x3*x5^2*x10^2*x11+x3*x5^2*x10^2*x12+x3*x5*x6^2*x9^2+x3*x5*x9^2*x11^2+x3*x5*x9^2*x12^2+x3*x5*x10^2*x11^2+x3*x6^3*x9^2+x3*x6^3*x10^2+x3*x6^2*x9^2*x11+x3*x6^2*x9^2*x12+x3*x6^2*x10^2*x12+x3*x6*x9^2*x12^2+x3*x6*x10^2*x11^2+x3*x6*x10^2*x12^2+x3*x9^2*x11^3+x3*x9^2*x11*x12^2+x3*x9^2*x12^3+x3*x9^2+x3*x10^2*x11^3+x3*x10^2*x11^2*x12+x3*x10^2*x12^3+x3*x10^2+x4^3*x5^3+x4^3*x5^2*x11+x4^3*x5*x6^2+x4^3*x5*x11^2+x4^3*x5*x12^2+x4^3*x6^3+x4^3*x6^2*x11+x4^3*x6^2*x12+x4^3*x6*x12^2+x4^3*x11^3+x4^3*x11*x12^2+x4^3*x12^3+x4^3+x4^2*x5^3*x9+x4^2*x5^3*x10+x4^2*x5^2*x6*x9+x4^2*x5^2*x9*x11+x4^2*x5^2*x9*x12+x4^2*x5^2*x10*x11+x4^2*x5*x6^2*x10+x4^2*x5*x9*x11^2+x4^2*x5*x10*x11^2+x4^2*x5*x10*x12^2+x4^2*x6^3*x9+x4^2*x6^3*x10+x4^2*x6^2*x9*x12+x4^2*x6^2*x10*x11+x4^2*x6^2*x10*x12+x4^2*x6*x9*x11^2+x4^2*x6*x9*x12^2+x4^2*x6*x10*x12^2+x4^2*x9*x11^3+x4^2*x9*x11^2*x12+x4^2*x9*x12^3+x4^2*x9+x4^2*x10*x11^3+x4^2*x10*x11*x12^2+x4^2*x10*x12^3+x4^2*x10+x4*x5^3*x10^2+x4*x5^2*x6*x9^2+x4*x5^2*x9^2*x12+x4*x5^2*x10^2*x11+x4*x5*x6^2*x9^2+x4*x5*x6^2*x10^2+x4*x5*x9^2*x12^2+x4*x5*x10^2*x11^2+x4*x5*x10^2*x12^2+x4*x6^3*x10^2+x4*x6^2*x9^2*x11+x4*x6^2*x10^2*x11+x4*x6^2*x10^2*x12+x4*x6*x9^2*x11^2+x4*x6*x10^2*x12^2+x4*x9^2*x11^2*x12+x4*x9^2*x11*x12^2+x4*x10^2*x11^3+x4*x10^2*x11*x12^2+x4*x10^2*x12^3+x4*x10^2+x5^3*x9^3+x5^3*x9*x10^2+x5^3*x10^3+x5^3+x5^2*x6*x9^2*x10+x5^2*x6*x9*x10^2+x5^2*x9^3*x11+x5^2*x9^2*x10*x12+x5^2*x9*x10^2*x11+x5^2*x9*x10^2*x12+x5^2*x10^3*x11+x5^2*x11+x5*x6^2*x9^3+x5*x6^2*x9^2*x10+x5*x6^2*x10^3+x5*x6^2+x5*x9^3*x11^2+x5*x9^3*x12^2+x5*x9^2*x10*x12^2+x5*x9*x10^2*x11^2+x5*x10^3*x11^2+x5*x10^3*x12^2+x5*x11^2+x5*x12^2+x6^3*x9^3+x6^3*x9*x10^2+x6^3*x10^3+x6^3+x6^2*x9^3*x11+x6^2*x9^3*x12+x6^2*x9^2*x10*x11+x6^2*x9*x10^2*x12+x6^2*x10^3*x11+x6^2*x10^3*x12+x6^2*x11+x6^2*x12+x6*x9^3*x12^2+x6*x9^2*x10*x11^2+x6*x9*x10^2*x11^2+x6*x9*x10^2*x12^2+x6*x10^3*x12^2+x6*x12^2+x9^3*x11^3+x9^3*x11*x12^2+x9^3*x12^3+x9^3+x9^2*x10*x11^2*x12+x9^2*x10*x11*x12^2+x9*x10^2*x11^3+x9*x10^2*x11^2*x12+x9*x10^2*x12^3+x9*x10^2+x10^3*x11^3+x10^3*x11*x12^2+x10^3*x12^3+x10^3+x11^3+x11*x12^2+x12^3+1;
"""

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