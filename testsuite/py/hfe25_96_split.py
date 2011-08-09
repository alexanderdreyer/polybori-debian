# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
path.append("../../PyPolyBoRi")
from polybori.PyPolyBoRi import *
from nf import *
import parse
import nav   
r=Ring(10000)
for i in xrange(0,1000):
    locals()["x"+str(i)]=Monomial(Variable(i))

 

IS=[
x1+x2+x7+x9+x11+x12+x19+x20+x21+x25+x1*x4+x1*x6+x1*x9+x1*x13+x1*x16+x1*x21+x1*x23+x2*x3+x2*x4+x2*x5+x2*x7+x2*x9+x2*x10+x2*x13+x2*x16+x2*x17+x2*x18+x2*x19+x2*x20+x2*x23+x3*x6+x3*x9+x3*x11+x3*x16+x3*x19+x3*x20+x3*x22+x3*x25+x4*x6+x4*x7+x4*x9+x4*x10+x4*x11+x4*x12+x4*x16+x4*x17+x4*x18+x4*x19+x4*x22+x4*x24+x5*x6+x5*x12+x5*x13+x5*x14+x5*x18+x5*x20+x5*x21+x5*x23+x5*x25+x6*x8+x6*x11+x6*x12+x6*x13+x6*x14+x6*x15+x6*x17+x6*x19+x6*x20+x6*x22+x6*x23+x7*x8+x7*x9+x7*x10+x7*x11+x7*x12+x7*x15+x7*x16+x7*x18+x7*x19+x7*x21+x7*x22+x7*x24+x8*x10+x8*x11+x8*x15+x8*x19+x8*x23+x8*x24+x8*x25+x9*x11+x9*x12+x9*x13+x9*x15+x9*x16+x9*x17+x9*x21+x9*x22+x9*x24+x9*x25+x10*x11+x10*x12+x10*x15+x10*x16+x10*x17+x10*x18+x10*x19+x10*x21+x10*x22+x10*x23+x10*x24+x11*x12+x11*x13+x11*x14+x11*x17+x11*x20+x11*x25+x12*x13+x12*x15+x12*x16+x12*x19+x12*x20+x12*x22+x12*x23+x12*x24+x12*x25+x13*x14+x13*x15+x13*x16+x13*x18+x13*x19+x13*x20+x13*x24+x13*x25+x14*x16+x14*x18+x14*x20+x14*x22+x14*x24+x14*x25+x15*x16+x15*x17+x15*x19+x15*x22+x15*x25+x16*x17+x16*x18+x16*x19+x16*x21+x17*x18+x17*x19+x17*x20+x17*x21+x17*x22+x17*x23+x18*x19+x18*x22+x18*x23+x19*x20+x19*x21+x19*x22+x19*x23+x19*x24+x20*x22+x20*x25+x21*x22+x21*x24+x21*x25+x22*x25+x23*x25,
x1+x7+x11+x15+x16+x22+x23+x24+x1*x3+x1*x5+x1*x6+x1*x7+x1*x8+x1*x9+x1*x11+x1*x13+x1*x14+x1*x15+x1*x17+x1*x19+x1*x20+x1*x21+x1*x24+x1*x25+x2*x7+x2*x9+x2*x11+x2*x15+x2*x16+x2*x17+x2*x18+x2*x21+x3*x4+x3*x5+x3*x7+x3*x9+x3*x11+x3*x13+x3*x16+x3*x17+x3*x19+x3*x22+x3*x23+x3*x25+x4*x5+x4*x6+x4*x10+x4*x14+x4*x16+x4*x18+x4*x19+x4*x23+x4*x24+x4*x25+x5*x8+x5*x11+x5*x13+x5*x14+x5*x15+x5*x18+x5*x20+x5*x21+x5*x23+x5*x24+x5*x25+x6*x9+x6*x10+x6*x13+x6*x14+x6*x17+x6*x18+x6*x20+x6*x23+x7*x11+x7*x15+x7*x17+x7*x18+x7*x19+x7*x20+x7*x21+x7*x24+x7*x25+x8*x11+x8*x12+x8*x16+x8*x19+x8*x21+x8*x22+x8*x23+x9*x13+x9*x14+x9*x16+x9*x17+x9*x22+x9*x24+x10*x11+x10*x12+x10*x15+x10*x17+x10*x18+x10*x22+x10*x24+x10*x25+x11*x12+x11*x13+x11*x16+x11*x17+x11*x18+x11*x19+x11*x22+x11*x25+x12*x13+x12*x16+x12*x19+x12*x24+x13*x14+x13*x15+x13*x17+x13*x19+x13*x20+x13*x21+x13*x24+x14*x18+x14*x25+x15*x17+x15*x18+x15*x19+x15*x20+x15*x21+x15*x24+x15*x25+x16*x17+x16*x19+x16*x22+x16*x25+x17*x19+x17*x20+x17*x21+x17*x22+x17*x23+x17*x25+x18*x19+x18*x21+x19*x20+x19*x21+x19*x23+x19*x24+x19*x25+x20*x22+x22*x24+x23*x24,
x1+x2+x6+x7+x8+x10+x11+x13+x15+x16+x17+x19+x22+x23+x25+x1*x3+x1*x4+x1*x5+x1*x9+x1*x11+x1*x13+x1*x15+x1*x16+x1*x17+x1*x21+x1*x25+x2*x3+x2*x4+x2*x5+x2*x8+x2*x12+x2*x13+x2*x14+x2*x16+x2*x18+x2*x24+x3*x7+x3*x9+x3*x10+x3*x12+x3*x13+x3*x14+x3*x15+x3*x16+x3*x18+x3*x19+x3*x20+x3*x21+x3*x22+x3*x23+x3*x24+x4*x8+x4*x10+x4*x17+x4*x18+x4*x19+x4*x20+x4*x21+x4*x22+x4*x23+x4*x24+x4*x25+x5*x11+x5*x12+x5*x16+x5*x17+x5*x18+x5*x19+x5*x23+x5*x24+x5*x25+x6*x7+x6*x9+x6*x10+x6*x13+x6*x14+x6*x15+x6*x17+x6*x18+x6*x19+x6*x20+x6*x24+x6*x25+x7*x13+x7*x14+x7*x15+x7*x21+x8*x10+x8*x12+x8*x13+x8*x14+x8*x15+x8*x24+x8*x25+x9*x10+x9*x11+x9*x14+x9*x15+x9*x16+x9*x17+x9*x19+x9*x21+x9*x22+x9*x23+x9*x25+x10*x12+x10*x14+x10*x16+x10*x17+x10*x19+x10*x22+x10*x23+x11*x12+x11*x14+x11*x17+x11*x18+x11*x20+x11*x21+x11*x22+x11*x24+x12*x14+x12*x17+x12*x18+x12*x21+x12*x23+x12*x24+x12*x25+x13*x14+x13*x15+x13*x16+x13*x17+x13*x18+x13*x19+x13*x20+x13*x23+x13*x25+x14*x21+x14*x25+x15*x16+x15*x17+x15*x18+x15*x23+x16*x19+x16*x21+x16*x23+x17*x19+x17*x20+x17*x21+x17*x23+x17*x25+x18*x21+x18*x22+x19*x20+x19*x21+x20*x24+x21*x22+x21*x23+x21*x24+x21*x25+x22*x23+x22*x24+x22*x25,
1+x2+x4+x5+x6+x9+x10+x11+x12+x13+x15+x17+x18+x19+x20+x21+x22+x24+x25+x1*x5+x1*x8+x1*x10+x1*x11+x1*x13+x1*x14+x1*x17+x1*x18+x1*x19+x1*x22+x2*x3+x2*x4+x2*x5+x2*x7+x2*x8+x2*x10+x2*x12+x2*x14+x2*x15+x2*x16+x2*x22+x2*x23+x2*x25+x3*x8+x3*x9+x3*x11+x3*x12+x3*x13+x3*x15+x3*x16+x3*x18+x3*x20+x3*x21+x3*x22+x3*x24+x3*x25+x4*x8+x4*x9+x4*x11+x4*x14+x4*x17+x4*x18+x4*x21+x4*x22+x4*x23+x4*x24+x4*x25+x5*x8+x5*x9+x5*x12+x5*x14+x5*x16+x5*x20+x5*x21+x5*x22+x5*x23+x5*x25+x6*x7+x6*x8+x6*x9+x6*x12+x6*x15+x6*x18+x6*x20+x7*x9+x7*x10+x7*x13+x7*x15+x7*x18+x7*x19+x7*x20+x7*x21+x7*x22+x7*x23+x7*x24+x8*x17+x8*x18+x8*x19+x8*x20+x8*x22+x8*x23+x9*x10+x9*x12+x9*x14+x9*x15+x9*x17+x9*x21+x9*x22+x9*x24+x10*x11+x10*x14+x10*x16+x10*x17+x10*x18+x10*x20+x10*x25+x11*x12+x11*x16+x11*x18+x11*x21+x11*x23+x11*x25+x12*x16+x12*x18+x12*x19+x12*x20+x12*x22+x12*x23+x12*x24+x12*x25+x13*x14+x13*x15+x13*x20+x13*x21+x13*x22+x13*x24+x14*x16+x14*x17+x14*x19+x14*x20+x14*x24+x15*x16+x15*x17+x15*x18+x15*x20+x15*x22+x15*x23+x15*x24+x15*x25+x16*x17+x16*x21+x16*x22+x16*x24+x17*x19+x17*x21+x17*x25+x18*x22+x18*x24+x19*x20+x20*x21+x20*x22+x20*x24+x21*x22+x21*x25+x23*x25,
1+x1+x3+x5+x13+x14+x16+x17+x18+x19+x20+x22+x23+x1*x2+x1*x7+x1*x8+x1*x9+x1*x11+x1*x13+x1*x15+x1*x16+x1*x19+x1*x20+x1*x21+x2*x7+x2*x11+x2*x13+x2*x14+x2*x15+x2*x16+x2*x21+x2*x23+x2*x24+x2*x25+x3*x4+x3*x5+x3*x8+x3*x10+x3*x11+x3*x13+x3*x14+x3*x15+x3*x17+x3*x18+x3*x19+x3*x21+x3*x22+x3*x23+x3*x24+x3*x25+x4*x6+x4*x7+x4*x8+x4*x9+x4*x11+x4*x13+x4*x14+x4*x16+x4*x17+x4*x20+x4*x21+x4*x25+x5*x7+x5*x9+x5*x12+x5*x13+x5*x14+x5*x15+x5*x19+x5*x20+x5*x22+x5*x23+x6*x7+x6*x8+x6*x9+x6*x10+x6*x13+x6*x15+x6*x17+x6*x21+x6*x25+x7*x9+x7*x11+x7*x13+x7*x15+x7*x17+x7*x21+x7*x23+x7*x25+x8*x11+x8*x14+x8*x18+x8*x19+x8*x22+x8*x24+x8*x25+x9*x10+x9*x13+x9*x17+x9*x20+x9*x21+x9*x22+x9*x23+x9*x24+x9*x25+x10*x11+x10*x14+x10*x16+x10*x17+x10*x21+x10*x24+x10*x25+x11*x12+x11*x16+x11*x19+x11*x21+x11*x23+x11*x25+x12*x13+x12*x16+x12*x17+x12*x19+x12*x20+x13*x14+x13*x15+x13*x16+x13*x17+x13*x19+x13*x20+x13*x21+x13*x22+x13*x24+x14*x16+x14*x19+x14*x20+x14*x22+x14*x24+x15*x17+x15*x23+x15*x24+x16*x22+x16*x24+x17*x18+x17*x21+x17*x22+x17*x23+x17*x24+x17*x25+x18*x19+x18*x20+x18*x22+x18*x23+x19*x21+x19*x25+x20*x23+x21*x22+x21*x23+x21*x24+x22*x23,
1+x1+x2+x3+x4+x6+x8+x9+x10+x12+x13+x15+x17+x20+x22+x25+x1*x2+x1*x5+x1*x6+x1*x8+x1*x9+x1*x12+x1*x14+x1*x20+x1*x21+x1*x23+x1*x24+x1*x25+x2*x3+x2*x6+x2*x7+x2*x9+x2*x10+x2*x12+x2*x13+x2*x15+x2*x16+x2*x17+x2*x18+x2*x20+x2*x21+x2*x22+x2*x24+x2*x25+x3*x12+x3*x13+x3*x16+x3*x17+x3*x19+x3*x22+x3*x24+x4*x5+x4*x6+x4*x8+x4*x9+x4*x10+x4*x11+x4*x15+x4*x19+x4*x23+x4*x24+x5*x12+x5*x17+x5*x21+x5*x22+x5*x23+x5*x25+x6*x8+x6*x9+x6*x10+x6*x13+x6*x14+x6*x15+x6*x16+x6*x18+x6*x19+x6*x20+x6*x21+x6*x23+x6*x24+x6*x25+x7*x13+x7*x14+x7*x15+x7*x16+x7*x19+x7*x20+x7*x21+x7*x23+x7*x25+x8*x9+x8*x10+x8*x17+x8*x19+x8*x20+x8*x21+x8*x23+x8*x24+x8*x25+x9*x16+x9*x17+x9*x18+x9*x19+x9*x21+x9*x22+x9*x25+x10*x12+x10*x14+x10*x17+x10*x19+x10*x20+x10*x21+x10*x22+x10*x23+x10*x24+x10*x25+x11*x12+x11*x15+x11*x19+x11*x20+x11*x21+x11*x22+x11*x25+x12*x13+x12*x14+x12*x19+x12*x20+x12*x21+x12*x25+x13*x15+x13*x18+x13*x19+x13*x20+x13*x22+x13*x23+x13*x24+x14*x15+x14*x19+x14*x21+x15*x16+x15*x17+x15*x18+x15*x22+x15*x25+x16*x18+x16*x23+x16*x25+x17*x18+x17*x20+x17*x22+x17*x23+x17*x24+x17*x25+x18*x20+x18*x22+x19*x20+x19*x22+x19*x25+x20*x24+x21*x22+x21*x24+x22*x24+x22*x25+x23*x24+x24*x25,
x1+x5+x8+x9+x12+x13+x14+x16+x18+x19+x20+x22+x23+x24+x1*x2+x1*x4+x1*x6+x1*x7+x1*x8+x1*x9+x1*x11+x1*x12+x1*x16+x1*x20+x1*x23+x1*x24+x1*x25+x2*x9+x2*x11+x2*x15+x2*x17+x2*x19+x2*x22+x2*x23+x2*x24+x3*x4+x3*x6+x3*x8+x3*x10+x3*x14+x3*x15+x3*x17+x3*x18+x3*x19+x3*x21+x3*x22+x3*x23+x3*x24+x3*x25+x4*x6+x4*x7+x4*x8+x4*x9+x4*x10+x4*x11+x4*x12+x4*x13+x4*x17+x4*x19+x4*x22+x4*x24+x4*x25+x5*x7+x5*x13+x5*x14+x5*x20+x5*x21+x5*x23+x5*x24+x6*x7+x6*x9+x6*x10+x6*x14+x6*x15+x6*x16+x6*x24+x7*x8+x7*x12+x7*x16+x7*x17+x7*x20+x7*x21+x7*x22+x7*x24+x7*x25+x8*x11+x8*x16+x8*x19+x8*x20+x8*x23+x8*x24+x9*x11+x9*x12+x9*x13+x9*x17+x9*x22+x9*x25+x10*x11+x10*x14+x10*x18+x10*x20+x10*x21+x10*x22+x10*x23+x11*x12+x11*x13+x11*x17+x11*x20+x11*x21+x11*x22+x11*x23+x11*x25+x12*x13+x12*x16+x12*x18+x12*x20+x12*x22+x13*x15+x13*x16+x13*x19+x13*x23+x14*x15+x14*x17+x14*x19+x14*x21+x14*x22+x15*x16+x15*x17+x15*x18+x15*x21+x15*x25+x16*x18+x16*x19+x16*x20+x16*x21+x16*x24+x17*x22+x17*x23+x17*x24+x17*x25+x18*x20+x18*x24+x19*x21+x19*x23+x19*x24+x19*x25+x20*x24+x21*x25+x22*x24,
1+x1+x3+x8+x11+x12+x13+x14+x16+x18+x20+x21+x23+x1*x2+x1*x3+x1*x6+x1*x8+x1*x9+x1*x13+x1*x14+x1*x15+x1*x16+x1*x17+x1*x18+x1*x19+x1*x20+x1*x23+x2*x4+x2*x5+x2*x6+x2*x7+x2*x9+x2*x10+x2*x11+x2*x12+x2*x13+x2*x20+x2*x23+x2*x24+x3*x4+x3*x7+x3*x9+x3*x10+x3*x11+x3*x13+x3*x17+x3*x18+x3*x20+x3*x21+x3*x24+x3*x25+x4*x5+x4*x7+x4*x10+x4*x11+x4*x12+x4*x14+x4*x15+x4*x16+x4*x17+x4*x22+x4*x23+x4*x24+x5*x7+x5*x11+x5*x13+x5*x14+x5*x15+x5*x16+x5*x18+x5*x22+x5*x25+x6*x8+x6*x11+x6*x13+x6*x15+x6*x17+x6*x22+x6*x23+x6*x24+x7*x11+x7*x14+x7*x15+x7*x16+x7*x18+x7*x23+x7*x24+x7*x25+x8*x10+x8*x16+x8*x17+x8*x18+x8*x19+x8*x20+x8*x23+x8*x24+x9*x12+x9*x16+x9*x25+x10*x13+x10*x15+x10*x18+x10*x22+x10*x23+x11*x12+x11*x14+x11*x21+x11*x23+x11*x25+x12*x14+x12*x15+x12*x16+x12*x18+x12*x19+x12*x21+x12*x23+x12*x24+x13*x15+x13*x20+x13*x23+x14*x15+x14*x18+x14*x21+x14*x22+x15*x16+x15*x20+x15*x21+x15*x22+x15*x23+x16*x20+x17*x18+x17*x19+x17*x21+x17*x23+x17*x24+x18*x20+x18*x21+x20*x22+x20*x23+x20*x25+x22*x24+x22*x25+x23*x25+x24*x25,
1+x1+x2+x3+x4+x5+x8+x9+x10+x11+x19+x22+x25+x1*x4+x1*x5+x1*x7+x1*x8+x1*x9+x1*x10+x1*x13+x1*x15+x1*x16+x1*x19+x1*x20+x1*x21+x1*x22+x1*x23+x2*x5+x2*x7+x2*x8+x2*x13+x2*x15+x2*x17+x2*x18+x2*x19+x2*x20+x2*x21+x2*x24+x3*x4+x3*x6+x3*x10+x3*x12+x3*x15+x3*x16+x3*x18+x3*x20+x3*x21+x3*x23+x3*x24+x4*x5+x4*x6+x4*x7+x4*x8+x4*x11+x4*x14+x4*x18+x4*x19+x4*x23+x4*x25+x5*x7+x5*x8+x5*x9+x5*x13+x5*x15+x5*x19+x5*x23+x6*x7+x6*x9+x6*x13+x6*x15+x6*x16+x6*x17+x6*x21+x6*x24+x6*x25+x7*x8+x7*x9+x7*x10+x7*x11+x7*x12+x7*x13+x7*x15+x7*x16+x7*x18+x7*x22+x7*x24+x8*x9+x8*x10+x8*x13+x8*x15+x8*x18+x8*x19+x8*x21+x8*x23+x8*x24+x8*x25+x9*x11+x9*x12+x9*x13+x9*x14+x9*x15+x9*x16+x9*x17+x9*x18+x9*x19+x9*x20+x9*x22+x9*x23+x10*x15+x10*x16+x10*x20+x10*x21+x10*x23+x10*x25+x11*x12+x11*x13+x11*x14+x11*x17+x11*x21+x11*x23+x12*x13+x12*x14+x12*x16+x12*x20+x12*x23+x13*x16+x13*x20+x13*x21+x13*x22+x14*x16+x14*x17+x14*x18+x14*x20+x14*x23+x15*x16+x15*x18+x15*x19+x15*x23+x15*x25+x16*x17+x16*x23+x16*x24+x17*x23+x17*x25+x18*x20+x18*x21+x18*x23+x19*x23+x19*x24+x20*x21+x21*x25+x22*x25+x23*x25,
1+x2+x6+x7+x10+x11+x14+x16+x17+x18+x19+x24+x1*x3+x1*x4+x1*x6+x1*x10+x1*x11+x1*x13+x1*x14+x1*x19+x1*x20+x1*x22+x1*x23+x1*x24+x1*x25+x2*x5+x2*x8+x2*x11+x2*x12+x2*x14+x2*x15+x2*x17+x2*x20+x2*x21+x2*x23+x2*x25+x3*x8+x3*x11+x3*x14+x3*x16+x3*x17+x3*x21+x3*x22+x3*x25+x4*x6+x4*x8+x4*x10+x4*x11+x4*x15+x4*x20+x4*x21+x4*x24+x5*x6+x5*x7+x5*x8+x5*x10+x5*x11+x5*x12+x5*x15+x5*x16+x5*x17+x5*x21+x5*x24+x5*x25+x6*x7+x6*x12+x6*x13+x6*x14+x6*x17+x6*x18+x6*x20+x6*x22+x6*x23+x7*x10+x7*x11+x7*x15+x7*x17+x7*x18+x7*x19+x7*x22+x8*x11+x8*x12+x8*x13+x8*x15+x8*x16+x8*x17+x9*x11+x9*x12+x9*x14+x9*x16+x9*x18+x9*x19+x9*x20+x9*x21+x9*x22+x9*x23+x9*x25+x10*x11+x10*x12+x10*x13+x10*x17+x10*x18+x10*x19+x10*x20+x10*x21+x10*x22+x10*x24+x10*x25+x11*x12+x11*x13+x11*x14+x11*x15+x11*x16+x11*x17+x11*x19+x11*x22+x11*x23+x11*x24+x12*x13+x12*x15+x12*x16+x12*x17+x12*x18+x12*x22+x12*x23+x12*x24+x13*x15+x13*x16+x13*x17+x13*x18+x13*x20+x14*x17+x14*x18+x14*x19+x14*x21+x14*x22+x14*x23+x15*x16+x15*x17+x15*x18+x15*x21+x15*x23+x15*x24+x15*x25+x16*x18+x16*x20+x16*x23+x17*x18+x17*x20+x17*x22+x17*x24+x17*x25+x18*x20+x18*x22+x18*x24+x18*x25+x19*x20+x19*x22+x19*x23+x19*x25+x20*x23+x20*x24+x20*x25+x21*x22+x21*x25+x22*x23+x22*x25+x23*x24+x24*x25,
1+x1+x6+x9+x10+x13+x14+x15+x19+x21+x24+x25+x1*x4+x1*x5+x1*x6+x1*x9+x1*x13+x1*x14+x1*x17+x1*x18+x1*x19+x1*x20+x1*x22+x1*x23+x2*x8+x2*x9+x2*x10+x2*x11+x2*x15+x2*x16+x2*x18+x2*x20+x2*x24+x3*x7+x3*x11+x3*x18+x3*x19+x3*x20+x3*x25+x4*x5+x4*x8+x4*x10+x4*x13+x4*x16+x4*x17+x4*x19+x4*x21+x4*x23+x4*x24+x4*x25+x5*x7+x5*x8+x5*x11+x5*x13+x5*x18+x5*x19+x5*x21+x5*x23+x5*x24+x6*x9+x6*x12+x6*x16+x6*x18+x6*x19+x6*x20+x6*x21+x6*x24+x6*x25+x7*x8+x7*x10+x7*x12+x7*x15+x7*x16+x7*x17+x7*x21+x7*x22+x7*x24+x8*x10+x8*x12+x8*x15+x8*x18+x8*x19+x8*x20+x8*x21+x8*x23+x9*x11+x9*x12+x9*x13+x9*x15+x9*x17+x9*x18+x9*x22+x9*x24+x10*x12+x10*x14+x10*x15+x10*x16+x10*x17+x10*x19+x10*x20+x10*x21+x10*x23+x11*x13+x11*x15+x11*x18+x11*x21+x11*x23+x12*x13+x12*x15+x13*x15+x13*x16+x13*x20+x13*x23+x13*x24+x13*x25+x14*x15+x14*x17+x14*x18+x14*x21+x14*x22+x14*x25+x15*x16+x15*x17+x15*x18+x15*x19+x15*x21+x15*x22+x15*x25+x16*x17+x16*x20+x16*x21+x16*x22+x16*x23+x17*x18+x17*x22+x17*x23+x17*x24+x17*x25+x18*x19+x18*x21+x18*x24+x19*x20+x19*x22+x19*x24+x20*x21+x20*x24+x21*x24+x22*x23+x23*x25,
x1+x2+x3+x7+x9+x10+x11+x15+x16+x17+x18+x19+x20+x21+x22+x23+x25+x1*x2+x1*x4+x1*x6+x1*x10+x1*x12+x1*x13+x1*x15+x1*x17+x1*x18+x2*x8+x2*x10+x2*x11+x2*x12+x2*x16+x2*x17+x2*x18+x2*x19+x2*x21+x2*x22+x2*x23+x2*x25+x3*x4+x3*x5+x3*x6+x3*x11+x3*x12+x3*x14+x3*x15+x3*x16+x3*x17+x3*x18+x3*x22+x3*x24+x3*x25+x4*x6+x4*x11+x4*x12+x4*x14+x4*x15+x4*x16+x4*x17+x4*x19+x4*x20+x5*x7+x5*x8+x5*x11+x5*x12+x5*x13+x5*x14+x5*x16+x5*x18+x5*x21+x5*x22+x5*x25+x6*x13+x6*x14+x6*x18+x6*x20+x6*x23+x6*x25+x7*x8+x7*x10+x7*x11+x7*x13+x7*x15+x7*x16+x7*x17+x7*x19+x7*x20+x7*x21+x7*x23+x7*x24+x7*x25+x8*x14+x8*x16+x8*x17+x8*x21+x8*x22+x8*x24+x9*x10+x9*x11+x9*x15+x9*x16+x9*x19+x9*x23+x9*x24+x9*x25+x10*x12+x10*x13+x10*x14+x10*x16+x10*x18+x10*x20+x10*x22+x10*x23+x10*x24+x11*x15+x11*x16+x11*x18+x11*x19+x11*x23+x11*x24+x12*x14+x12*x18+x12*x19+x12*x20+x12*x22+x13*x14+x13*x16+x13*x17+x13*x19+x13*x21+x13*x24+x13*x25+x14*x15+x14*x19+x14*x20+x14*x22+x14*x25+x15*x19+x15*x21+x15*x22+x15*x23+x15*x24+x15*x25+x16*x18+x16*x19+x16*x20+x16*x22+x17*x18+x17*x19+x17*x23+x17*x25+x18*x19+x18*x21+x18*x24+x19*x20+x19*x21+x19*x22+x19*x23+x19*x25+x20*x21+x20*x22+x20*x23+x20*x24+x20*x25+x21*x22+x21*x25+x24*x25,
x1+x2+x3+x4+x5+x6+x7+x9+x11+x13+x14+x17+x18+x20+x22+x24+x25+x1*x3+x1*x7+x1*x10+x1*x11+x1*x13+x1*x14+x1*x15+x1*x17+x1*x19+x1*x20+x1*x22+x1*x23+x2*x4+x2*x5+x2*x6+x2*x16+x2*x20+x2*x23+x2*x24+x2*x25+x3*x4+x3*x5+x3*x6+x3*x7+x3*x8+x3*x11+x3*x17+x3*x18+x3*x22+x3*x23+x4*x7+x4*x8+x4*x10+x4*x11+x4*x12+x4*x13+x4*x14+x4*x15+x4*x16+x4*x17+x4*x20+x5*x7+x5*x8+x5*x9+x5*x12+x5*x15+x5*x20+x5*x21+x5*x23+x6*x8+x6*x9+x6*x11+x6*x13+x6*x14+x6*x17+x6*x18+x6*x19+x6*x22+x6*x24+x6*x25+x7*x9+x7*x13+x7*x14+x7*x16+x7*x17+x7*x19+x7*x20+x7*x22+x7*x24+x8*x11+x8*x12+x8*x13+x8*x14+x8*x17+x8*x19+x8*x20+x8*x21+x9*x10+x9*x12+x9*x13+x9*x17+x9*x18+x9*x20+x9*x22+x9*x24+x10*x12+x10*x14+x10*x15+x10*x16+x10*x17+x10*x18+x10*x19+x10*x22+x11*x12+x11*x13+x11*x15+x11*x18+x11*x19+x11*x20+x11*x21+x11*x23+x12*x18+x12*x22+x12*x24+x12*x25+x13*x14+x13*x17+x13*x20+x13*x22+x13*x23+x13*x25+x14*x15+x14*x18+x14*x19+x14*x21+x14*x22+x14*x23+x15*x17+x15*x23+x15*x25+x16*x17+x16*x18+x16*x20+x16*x21+x16*x22+x16*x23+x16*x24+x17*x21+x17*x22+x17*x23+x17*x25+x18*x20+x18*x22+x18*x23+x18*x24+x18*x25+x19*x20+x19*x24+x20*x21+x20*x22+x20*x23+x20*x24+x21*x22+x21*x23+x21*x25+x22*x25+x23*x25,
x2+x3+x5+x11+x14+x16+x24+x25+x1*x3+x1*x4+x1*x5+x1*x9+x1*x11+x1*x12+x1*x15+x1*x16+x1*x18+x1*x19+x1*x20+x1*x23+x1*x24+x1*x25+x2*x3+x2*x7+x2*x8+x2*x10+x2*x12+x2*x15+x2*x17+x2*x20+x2*x22+x2*x24+x2*x25+x3*x5+x3*x6+x3*x7+x3*x8+x3*x9+x3*x10+x3*x11+x3*x14+x3*x16+x3*x22+x3*x23+x3*x24+x3*x25+x4*x6+x4*x10+x4*x13+x4*x16+x4*x17+x4*x20+x4*x21+x4*x23+x4*x24+x4*x25+x5*x6+x5*x8+x5*x9+x5*x10+x5*x12+x5*x14+x5*x15+x5*x18+x5*x20+x5*x21+x5*x25+x6*x8+x6*x11+x6*x13+x6*x14+x6*x16+x6*x17+x6*x19+x6*x21+x6*x25+x7*x8+x7*x10+x7*x11+x7*x13+x7*x21+x7*x22+x7*x24+x8*x9+x8*x10+x8*x11+x8*x14+x8*x16+x8*x17+x8*x21+x8*x22+x8*x23+x9*x10+x9*x12+x9*x13+x9*x16+x9*x18+x9*x22+x10*x11+x10*x13+x10*x15+x10*x16+x10*x18+x10*x19+x10*x22+x10*x25+x11*x12+x11*x14+x11*x15+x11*x16+x11*x18+x11*x19+x12*x13+x12*x14+x12*x16+x12*x19+x12*x20+x12*x21+x12*x22+x12*x23+x12*x24+x12*x25+x13*x14+x13*x17+x13*x18+x13*x22+x13*x23+x14*x16+x14*x17+x14*x22+x14*x23+x14*x24+x14*x25+x15*x16+x15*x17+x15*x19+x15*x23+x15*x24+x15*x25+x16*x19+x16*x21+x16*x23+x17*x18+x17*x19+x17*x21+x17*x22+x17*x23+x17*x25+x18*x19+x18*x21+x18*x23+x18*x24+x19*x20+x19*x21+x19*x23+x19*x24+x21*x22+x21*x24+x21*x25+x22*x23+x22*x24+x22*x25+x24*x25,
x2+x3+x4+x5+x6+x7+x8+x10+x11+x15+x16+x22+x24+x1*x4+x1*x7+x1*x8+x1*x9+x1*x10+x1*x12+x1*x13+x1*x16+x1*x17+x1*x20+x1*x22+x1*x23+x1*x24+x2*x3+x2*x5+x2*x8+x2*x10+x2*x11+x2*x12+x2*x14+x2*x15+x2*x16+x2*x17+x2*x18+x2*x21+x2*x22+x3*x12+x3*x14+x3*x18+x3*x19+x3*x20+x3*x22+x4*x5+x4*x9+x4*x10+x4*x12+x4*x15+x4*x16+x4*x17+x4*x18+x4*x20+x4*x21+x4*x23+x4*x24+x4*x25+x5*x7+x5*x11+x5*x12+x5*x14+x5*x17+x5*x18+x5*x19+x5*x22+x6*x9+x6*x10+x6*x11+x6*x12+x6*x13+x6*x18+x6*x19+x6*x21+x6*x25+x7*x9+x7*x12+x7*x15+x7*x18+x7*x21+x7*x23+x8*x10+x8*x11+x8*x12+x8*x13+x8*x15+x8*x18+x8*x19+x9*x10+x9*x12+x9*x15+x9*x16+x9*x17+x9*x19+x10*x11+x10*x14+x10*x15+x10*x16+x10*x17+x10*x19+x10*x21+x10*x23+x10*x24+x10*x25+x11*x12+x11*x13+x11*x16+x11*x17+x11*x24+x12*x15+x12*x17+x12*x18+x12*x22+x12*x25+x13*x15+x13*x17+x13*x19+x13*x21+x13*x25+x14*x17+x14*x20+x14*x21+x15*x19+x15*x20+x15*x22+x15*x24+x15*x25+x16*x18+x16*x20+x16*x22+x16*x23+x16*x24+x17*x19+x17*x20+x18*x20+x18*x21+x18*x22+x19*x21+x19*x23+x19*x24+x20*x23+x20*x24+x21*x22+x21*x24+x21*x25+x22*x25+x23*x24+x24*x25,
x1+x2+x3+x4+x5+x6+x9+x10+x13+x16+x20+x21+x25+x1*x2+x1*x4+x1*x6+x1*x7+x1*x8+x1*x11+x1*x14+x1*x16+x1*x17+x1*x18+x1*x23+x2*x3+x2*x4+x2*x8+x2*x9+x2*x11+x2*x12+x2*x13+x2*x16+x2*x18+x2*x23+x2*x25+x3*x4+x3*x5+x3*x7+x3*x8+x3*x11+x3*x14+x3*x15+x3*x16+x3*x17+x3*x19+x3*x21+x3*x23+x4*x7+x4*x8+x4*x9+x4*x10+x4*x11+x4*x12+x4*x13+x4*x18+x4*x19+x4*x20+x5*x6+x5*x9+x5*x10+x5*x13+x5*x15+x5*x17+x5*x18+x5*x20+x5*x22+x5*x23+x5*x25+x6*x7+x6*x10+x6*x11+x6*x12+x6*x13+x6*x14+x6*x15+x6*x16+x6*x18+x6*x20+x6*x21+x6*x23+x6*x24+x7*x9+x7*x11+x7*x12+x7*x13+x7*x16+x7*x17+x7*x19+x7*x20+x7*x24+x8*x12+x8*x14+x8*x15+x8*x18+x8*x22+x8*x25+x9*x11+x9*x12+x9*x13+x9*x21+x9*x24+x10*x12+x10*x18+x10*x20+x10*x21+x10*x22+x11*x12+x11*x13+x11*x15+x11*x17+x11*x20+x11*x21+x11*x22+x11*x23+x11*x24+x11*x25+x12*x14+x12*x15+x12*x16+x12*x18+x12*x19+x12*x20+x12*x22+x12*x24+x13*x14+x13*x17+x13*x19+x13*x23+x13*x25+x14*x15+x14*x20+x14*x23+x15*x22+x15*x24+x15*x25+x16*x18+x16*x21+x16*x22+x16*x25+x17*x20+x17*x22+x17*x23+x17*x24+x17*x25+x18*x19+x18*x20+x19*x20+x19*x21+x19*x22+x19*x23+x19*x24+x19*x25+x20*x21+x21*x22+x22*x23+x22*x25,
x1+x5+x9+x10+x11+x14+x15+x18+x19+x23+x24+x25+x1*x4+x1*x5+x1*x7+x1*x9+x1*x13+x1*x14+x1*x21+x1*x24+x1*x25+x2*x5+x2*x6+x2*x7+x2*x8+x2*x9+x2*x14+x2*x16+x2*x18+x2*x20+x2*x22+x2*x23+x2*x24+x3*x6+x3*x7+x3*x9+x3*x10+x3*x14+x3*x15+x3*x17+x3*x21+x3*x22+x3*x23+x3*x24+x3*x25+x4*x6+x4*x7+x4*x8+x4*x10+x4*x11+x4*x12+x4*x13+x4*x14+x4*x19+x4*x22+x4*x23+x4*x24+x5*x7+x5*x8+x5*x9+x5*x10+x5*x12+x5*x14+x5*x15+x5*x16+x5*x20+x5*x23+x6*x10+x6*x13+x6*x14+x6*x15+x6*x16+x6*x21+x6*x24+x7*x9+x7*x11+x7*x13+x7*x14+x7*x16+x7*x18+x7*x19+x7*x22+x7*x24+x7*x25+x8*x9+x8*x10+x8*x12+x8*x13+x8*x14+x8*x16+x8*x18+x8*x20+x8*x21+x8*x23+x9*x10+x9*x11+x9*x13+x9*x14+x9*x15+x9*x16+x9*x17+x9*x20+x9*x21+x9*x23+x9*x25+x10*x11+x10*x12+x10*x13+x10*x14+x10*x15+x10*x19+x10*x22+x10*x24+x11*x12+x11*x13+x11*x14+x11*x15+x11*x16+x11*x19+x11*x21+x11*x22+x11*x23+x12*x13+x12*x15+x12*x16+x12*x20+x12*x21+x12*x25+x13*x16+x13*x17+x13*x20+x13*x22+x14*x16+x14*x19+x14*x21+x14*x22+x14*x23+x14*x25+x15*x17+x15*x19+x15*x23+x15*x25+x16*x18+x16*x19+x16*x21+x16*x22+x16*x23+x16*x24+x17*x18+x17*x19+x17*x21+x17*x23+x17*x24+x18*x20+x19*x21+x19*x22+x19*x23+x19*x24+x21*x22+x22*x25+x24*x25,
1+x2+x5+x12+x13+x14+x16+x18+x19+x24+x1*x3+x1*x5+x1*x7+x1*x9+x1*x11+x1*x13+x1*x17+x1*x18+x1*x19+x1*x20+x1*x21+x1*x22+x1*x25+x2*x5+x2*x13+x2*x15+x2*x17+x2*x18+x2*x19+x2*x23+x2*x24+x2*x25+x3*x4+x3*x5+x3*x7+x3*x8+x3*x9+x3*x11+x3*x14+x3*x15+x3*x22+x3*x23+x3*x24+x4*x6+x4*x8+x4*x11+x4*x12+x4*x14+x4*x17+x4*x19+x4*x22+x4*x24+x4*x25+x5*x6+x5*x7+x5*x9+x5*x16+x5*x18+x5*x19+x5*x21+x5*x24+x6*x9+x6*x13+x6*x15+x6*x16+x6*x17+x6*x18+x6*x19+x6*x21+x6*x22+x6*x23+x6*x24+x6*x25+x7*x10+x7*x11+x7*x13+x7*x14+x7*x16+x7*x19+x7*x20+x7*x22+x7*x23+x7*x24+x8*x10+x8*x14+x8*x16+x8*x18+x8*x20+x8*x22+x8*x23+x9*x10+x9*x11+x9*x16+x9*x17+x9*x19+x9*x22+x9*x23+x9*x25+x10*x12+x10*x14+x10*x16+x10*x17+x10*x19+x10*x20+x10*x21+x10*x23+x11*x13+x11*x14+x11*x22+x11*x23+x11*x25+x12*x13+x12*x15+x12*x18+x12*x19+x12*x21+x12*x22+x12*x23+x13*x15+x13*x16+x13*x17+x13*x19+x13*x21+x13*x22+x13*x23+x13*x24+x13*x25+x14*x16+x14*x17+x14*x18+x14*x19+x14*x21+x14*x24+x15*x18+x15*x20+x15*x21+x15*x22+x15*x23+x15*x25+x16*x17+x16*x18+x16*x19+x16*x20+x16*x21+x16*x23+x17*x18+x17*x21+x17*x25+x18*x19+x18*x21+x18*x22+x18*x23+x18*x24+x19*x23+x19*x25+x20*x25+x21*x25+x22*x23+x23*x24+x23*x25+x24*x25,
1+x4+x6+x8+x10+x12+x13+x15+x16+x21+x22+x23+x24+x25+x1*x3+x1*x7+x1*x11+x1*x12+x1*x14+x1*x16+x1*x17+x1*x20+x1*x24+x2*x5+x2*x6+x2*x8+x2*x10+x2*x12+x2*x13+x2*x17+x2*x18+x2*x19+x2*x22+x2*x24+x2*x25+x3*x4+x3*x5+x3*x6+x3*x7+x3*x10+x3*x17+x3*x19+x3*x21+x3*x22+x3*x25+x4*x5+x4*x6+x4*x8+x4*x10+x4*x11+x4*x14+x4*x17+x4*x18+x4*x20+x4*x23+x4*x24+x4*x25+x5*x6+x5*x7+x5*x9+x5*x10+x5*x11+x5*x12+x5*x13+x5*x15+x5*x22+x5*x23+x5*x25+x6*x7+x6*x8+x6*x11+x6*x12+x6*x16+x6*x19+x6*x22+x6*x23+x7*x8+x7*x10+x7*x13+x7*x16+x7*x17+x7*x18+x7*x24+x8*x9+x8*x14+x8*x22+x8*x24+x8*x25+x9*x12+x9*x13+x9*x16+x9*x20+x9*x22+x9*x24+x10*x11+x10*x14+x10*x15+x10*x16+x10*x21+x10*x22+x10*x24+x11*x14+x11*x22+x11*x24+x12*x13+x12*x15+x12*x17+x12*x19+x12*x21+x12*x22+x12*x23+x12*x24+x12*x25+x13*x14+x13*x15+x13*x16+x13*x20+x13*x21+x13*x22+x13*x24+x14*x15+x14*x17+x14*x19+x14*x20+x14*x21+x14*x22+x15*x16+x15*x18+x15*x20+x15*x21+x15*x25+x16*x17+x16*x18+x16*x20+x16*x21+x16*x24+x17*x19+x17*x22+x17*x24+x18*x22+x18*x23+x19*x21+x19*x23+x20*x21+x20*x23+x20*x25+x21*x23+x21*x24+x22*x23+x22*x24+x22*x25,
x2+x6+x7+x8+x9+x14+x15+x18+x19+x24+x1*x2+x1*x3+x1*x7+x1*x8+x1*x9+x1*x11+x1*x12+x1*x14+x1*x23+x1*x24+x1*x25+x2*x3+x2*x7+x2*x10+x2*x13+x2*x14+x2*x15+x2*x16+x2*x25+x3*x4+x3*x6+x3*x9+x3*x12+x3*x13+x3*x14+x3*x17+x3*x19+x3*x22+x3*x23+x3*x24+x3*x25+x4*x6+x4*x7+x4*x12+x4*x13+x4*x14+x4*x15+x4*x16+x4*x17+x4*x19+x4*x20+x4*x21+x4*x22+x4*x25+x5*x7+x5*x8+x5*x9+x5*x11+x5*x13+x5*x14+x5*x15+x5*x18+x5*x19+x5*x20+x5*x24+x5*x25+x6*x8+x6*x9+x6*x13+x6*x15+x6*x16+x6*x18+x6*x20+x6*x21+x7*x9+x7*x10+x7*x18+x7*x19+x7*x20+x7*x21+x7*x22+x7*x23+x7*x24+x8*x11+x8*x12+x8*x14+x8*x15+x8*x16+x8*x17+x8*x18+x9*x10+x9*x11+x9*x12+x9*x14+x9*x18+x9*x19+x9*x23+x9*x24+x10*x11+x10*x14+x10*x17+x10*x22+x10*x23+x10*x24+x11*x13+x11*x14+x11*x16+x11*x21+x11*x22+x11*x25+x12*x15+x12*x16+x12*x17+x12*x18+x12*x19+x12*x21+x12*x24+x13*x14+x13*x15+x13*x17+x13*x22+x13*x23+x14*x15+x14*x18+x14*x19+x14*x20+x14*x22+x14*x24+x14*x25+x15*x16+x15*x19+x15*x20+x15*x21+x15*x23+x16*x17+x16*x20+x16*x23+x16*x24+x17*x18+x17*x19+x17*x20+x17*x21+x17*x23+x18*x20+x18*x21+x18*x22+x19*x21+x19*x23+x19*x25+x20*x21+x20*x22+x20*x23+x20*x24+x21*x22+x21*x23+x21*x25+x22*x24+x24*x25,
1+x1+x2+x4+x5+x8+x10+x13+x15+x16+x18+x21+x23+x25+x1*x5+x1*x7+x1*x11+x1*x12+x1*x16+x1*x17+x1*x19+x1*x20+x1*x21+x1*x22+x1*x23+x2*x4+x2*x7+x2*x12+x2*x14+x2*x16+x2*x19+x2*x20+x2*x23+x2*x25+x3*x5+x3*x6+x3*x7+x3*x9+x3*x12+x3*x15+x3*x17+x3*x18+x3*x19+x3*x25+x4*x5+x4*x6+x4*x8+x4*x13+x4*x14+x4*x15+x4*x19+x4*x20+x4*x23+x4*x24+x5*x6+x5*x8+x5*x9+x5*x10+x5*x11+x5*x12+x5*x13+x5*x14+x5*x15+x5*x16+x5*x18+x5*x22+x5*x23+x5*x24+x6*x9+x6*x12+x6*x15+x6*x16+x6*x18+x6*x19+x7*x8+x7*x10+x7*x12+x7*x13+x7*x14+x7*x15+x7*x19+x7*x21+x7*x22+x7*x25+x8*x11+x8*x14+x8*x16+x8*x20+x8*x21+x8*x22+x8*x25+x9*x12+x9*x13+x9*x14+x9*x16+x9*x18+x9*x19+x9*x21+x9*x22+x9*x25+x10*x13+x10*x14+x10*x19+x10*x20+x10*x21+x10*x22+x10*x23+x11*x12+x11*x16+x11*x19+x11*x21+x12*x13+x12*x18+x12*x19+x12*x20+x12*x21+x12*x24+x13*x14+x13*x16+x13*x17+x13*x24+x13*x25+x14*x16+x14*x19+x14*x20+x14*x21+x14*x23+x14*x24+x15*x16+x15*x18+x15*x20+x15*x22+x15*x23+x16*x17+x16*x18+x16*x25+x17*x21+x18*x20+x18*x21+x18*x22+x18*x23+x18*x24+x18*x25+x19*x20+x19*x22+x19*x23+x20*x22+x21*x23+x21*x24+x22*x25+x23*x24+x23*x25,
1+x1+x2+x6+x7+x8+x12+x13+x14+x15+x16+x22+x23+x1*x3+x1*x4+x1*x8+x1*x10+x1*x11+x1*x15+x1*x16+x1*x17+x2*x4+x2*x8+x2*x14+x2*x15+x2*x19+x2*x20+x2*x21+x2*x22+x2*x25+x3*x5+x3*x6+x3*x8+x3*x10+x3*x12+x3*x14+x3*x15+x3*x17+x3*x18+x3*x21+x3*x22+x3*x23+x4*x5+x4*x6+x4*x7+x4*x8+x4*x9+x4*x10+x4*x13+x4*x16+x4*x18+x4*x20+x4*x22+x4*x23+x4*x25+x5*x7+x5*x8+x5*x10+x5*x12+x5*x13+x5*x15+x5*x17+x5*x18+x5*x19+x5*x20+x5*x22+x5*x23+x5*x24+x5*x25+x6*x9+x6*x10+x6*x11+x6*x12+x6*x14+x6*x19+x6*x20+x6*x22+x6*x24+x6*x25+x7*x8+x7*x13+x7*x14+x7*x16+x7*x17+x7*x18+x7*x19+x7*x22+x7*x23+x7*x25+x8*x9+x8*x10+x8*x14+x8*x15+x8*x16+x8*x18+x8*x20+x8*x23+x8*x24+x8*x25+x9*x10+x9*x11+x9*x13+x9*x15+x9*x18+x9*x19+x9*x22+x10*x11+x10*x13+x10*x14+x10*x16+x10*x17+x10*x18+x10*x21+x10*x23+x10*x25+x11*x13+x11*x14+x11*x17+x11*x18+x11*x19+x11*x21+x11*x23+x12*x14+x12*x18+x12*x23+x12*x24+x12*x25+x13*x16+x13*x17+x13*x19+x13*x23+x13*x24+x13*x25+x14*x21+x14*x23+x15*x16+x15*x17+x15*x18+x15*x20+x15*x21+x15*x22+x15*x24+x16*x17+x16*x22+x16*x24+x18*x19+x18*x21+x18*x22+x18*x24+x19*x20+x19*x21+x20*x21+x20*x25+x21*x24+x22*x23+x23*x24,
x1+x2+x3+x4+x5+x6+x8+x9+x10+x11+x12+x16+x19+x21+x22+x24+x1*x3+x1*x5+x1*x6+x1*x8+x1*x9+x1*x11+x1*x12+x1*x13+x1*x15+x1*x16+x1*x18+x1*x19+x1*x22+x1*x25+x2*x3+x2*x4+x2*x5+x2*x8+x2*x10+x2*x15+x2*x19+x2*x20+x2*x22+x2*x25+x3*x6+x3*x7+x3*x9+x3*x10+x3*x11+x3*x12+x3*x13+x3*x17+x3*x18+x3*x19+x3*x22+x3*x23+x3*x25+x4*x5+x4*x6+x4*x9+x4*x11+x4*x12+x4*x14+x4*x20+x4*x21+x4*x24+x5*x7+x5*x9+x5*x14+x5*x15+x5*x18+x5*x20+x5*x22+x5*x23+x5*x24+x5*x25+x6*x7+x6*x9+x6*x10+x6*x11+x6*x14+x6*x18+x6*x19+x6*x21+x6*x22+x6*x23+x7*x8+x7*x15+x7*x17+x7*x18+x7*x19+x7*x20+x7*x23+x7*x24+x8*x9+x8*x10+x8*x11+x8*x12+x8*x16+x8*x19+x8*x20+x8*x22+x8*x24+x9*x10+x9*x11+x9*x12+x9*x14+x9*x15+x9*x17+x9*x19+x9*x20+x9*x22+x9*x23+x10*x11+x10*x13+x10*x14+x10*x15+x10*x17+x10*x18+x10*x19+x10*x22+x10*x23+x10*x24+x11*x12+x11*x13+x11*x14+x11*x15+x11*x17+x11*x18+x11*x23+x11*x25+x12*x13+x12*x16+x12*x17+x12*x18+x12*x20+x12*x21+x13*x14+x13*x15+x13*x17+x13*x20+x13*x22+x13*x24+x13*x25+x14*x15+x14*x16+x14*x18+x14*x21+x14*x22+x14*x23+x14*x24+x15*x16+x15*x18+x15*x20+x15*x22+x15*x23+x15*x24+x15*x25+x16*x17+x16*x18+x16*x20+x16*x21+x16*x22+x16*x23+x16*x24+x16*x25+x17*x19+x17*x21+x17*x24+x17*x25+x18*x19+x18*x20+x18*x21+x18*x25+x19*x21+x19*x22+x19*x23+x19*x24+x19*x25+x20*x21+x20*x22+x20*x24+x20*x25+x21*x23+x21*x25+x22*x23+x22*x24+x23*x24+x23*x25+x24*x25,
x1+x3+x5+x6+x9+x11+x12+x15+x16+x17+x21+x22+x23+x25+x1*x2+x1*x4+x1*x8+x1*x10+x1*x12+x1*x13+x1*x16+x1*x17+x1*x19+x1*x20+x1*x22+x1*x24+x1*x25+x2*x4+x2*x6+x2*x7+x2*x10+x2*x14+x2*x19+x2*x20+x2*x21+x2*x22+x2*x23+x2*x24+x2*x25+x3*x11+x3*x12+x3*x13+x3*x17+x3*x18+x3*x19+x3*x23+x4*x6+x4*x8+x4*x10+x4*x11+x4*x12+x4*x13+x4*x15+x4*x22+x5*x6+x5*x7+x5*x9+x5*x10+x5*x11+x5*x12+x5*x13+x5*x14+x5*x15+x5*x17+x5*x18+x5*x23+x6*x7+x6*x8+x6*x10+x6*x11+x6*x12+x6*x15+x6*x16+x6*x17+x6*x21+x6*x24+x7*x9+x7*x11+x7*x12+x7*x17+x7*x18+x7*x19+x7*x22+x7*x23+x7*x24+x8*x10+x8*x13+x8*x15+x8*x16+x8*x19+x8*x20+x8*x24+x8*x25+x9*x10+x9*x11+x9*x13+x9*x14+x9*x15+x9*x16+x9*x17+x9*x18+x9*x24+x9*x25+x10*x12+x10*x13+x10*x17+x10*x19+x10*x22+x10*x24+x10*x25+x11*x13+x11*x14+x11*x20+x11*x23+x11*x24+x11*x25+x12*x14+x12*x15+x12*x17+x12*x18+x12*x19+x12*x20+x12*x24+x13*x17+x13*x21+x14*x15+x14*x19+x14*x22+x14*x24+x14*x25+x15*x17+x15*x18+x15*x20+x15*x23+x16*x19+x16*x21+x16*x22+x16*x25+x17*x18+x17*x20+x17*x21+x17*x23+x17*x25+x18*x21+x18*x22+x18*x25+x19*x20+x19*x22+x20*x21+x20*x23+x20*x24+x20*x25+x21*x22+x21*x23+x21*x24+x21*x25+x22*x23+x22*x24+x23*x25,
x1+x2+x5+x6+x8+x9+x10+x16+x19+x21+x22+x23+x24+x25+x1*x2+x1*x4+x1*x5+x1*x6+x1*x7+x1*x8+x1*x11+x1*x15+x1*x16+x1*x17+x1*x19+x1*x20+x1*x23+x2*x3+x2*x8+x2*x10+x2*x13+x2*x15+x2*x17+x2*x21+x2*x22+x2*x23+x2*x25+x3*x4+x3*x11+x3*x12+x3*x13+x3*x14+x3*x16+x3*x18+x3*x20+x3*x21+x3*x22+x3*x25+x4*x7+x4*x11+x4*x13+x4*x18+x4*x20+x4*x22+x4*x24+x4*x25+x5*x7+x5*x9+x5*x12+x5*x14+x5*x17+x6*x7+x6*x8+x6*x9+x6*x10+x6*x11+x6*x13+x6*x15+x6*x20+x6*x21+x6*x22+x6*x24+x7*x10+x7*x12+x7*x15+x7*x16+x7*x18+x7*x20+x7*x22+x7*x23+x7*x25+x8*x11+x8*x12+x8*x13+x8*x16+x8*x17+x8*x19+x8*x21+x9*x10+x9*x15+x9*x16+x9*x20+x9*x23+x10*x12+x10*x13+x10*x16+x10*x19+x10*x20+x10*x22+x10*x23+x10*x24+x11*x14+x11*x20+x11*x21+x11*x22+x11*x23+x11*x24+x11*x25+x12*x18+x12*x22+x12*x23+x13*x15+x13*x17+x13*x18+x13*x20+x13*x21+x13*x23+x13*x24+x13*x25+x14*x15+x14*x21+x14*x23+x14*x25+x15*x16+x15*x17+x15*x19+x15*x20+x15*x21+x15*x22+x15*x23+x16*x17+x16*x19+x16*x22+x16*x23+x16*x24+x17*x21+x17*x22+x17*x23+x17*x24+x18*x21+x19*x20+x19*x22+x19*x24+x20*x22+x20*x23+x20*x24+x20*x25+x21*x24+x22*x23+x22*x24+x22*x25+x23*x24+x23*x25]




import split

I=[Polynomial(i) for i in IS]
splitted=split.split_equations(I,10,27)
#(r,I)=parse.translate_ideal(IS, ["x"+str(i) for i in xrange(1,25+1)])
print len(I)
I=splitted
print len(I)
#for i in I:
#    print len(i)
I= buchberger_C_based2(I)
#print len
for i in I:
    print nav.support(i)
