# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
path.append("../../PyPolyBoRi")
from data import hole6 as hole
from nf import *

x=hole.x
splits=3
pig=6
r=pig/splits
proof_path=[]
for i in xrange(7):
    curr=[]
    
    for c in xrange(splits):
        m=Monomial()
        
        for j in xrange(r):
            index=6*i+j+1+r*c
            print m
            m=x(index)*m
        m=Polynomial(m)
        m.toStdOut()
        curr.append(m)
    curr=[[p+1 for p in curr[:j]] +[curr[j]] for j in xrange(splits)]
    proof_path.append(curr)
#proof_path.reverse()
I=GPS_with_non_binary_proof_path(hole.ideal,proof_path[:], deg_bound=4,over_deg_bound=10)
#I=buchberger_C_based2(hole6.ideal)
