# Copyright (c) 2005-2007 by The PolyBoRi Team
from sys import path
path.append("../../PyPolyBoRi")
import gbrefs
hole=gbrefs.load_data("data.aes.aes_6_1_1_8")
import aes
ideal=aes.preprocess(hole.ideal)
from nf import *

x=hole.x
proof_path=[]
#for i in xrange(7):
#    m=Monomial()
#    for j in xrange(2):
#        print m, m.__class__
#        m=x(6*i+j+1)*m
#    m=Polynomial(m)
#    m.toStdOut()
#    proof_path.append(m)

from random import Random
generator=Random()
nvars=128
nvars=68
#variable_indices=range(1,nvars+1)
linear_leads=set()
for p in ideal:
    if not p.isZero():
        l=p.lead()
        if l.deg()==1:
            for i in l:
                linear_leads.add(i)
                break
variable_indices=Monomial()
for p in ideal:
    variable_indices=variable_indices*p.vars()
variable_indices=[i for i in variable_indices if not i in linear_leads]

print "VI", len(variable_indices), variable_indices
m=Monomial()
var_indices_bak=list(variable_indices)

def gen_size_n_blocks(vi,n):
    m=Monomial()
    for i in vi:
        m=m*Variable(i)
        if m.deg()==n:
            yield m
            m=Monomial()
generator.shuffle(variable_indices)
proof_path=list(gen_size_n_blocks(variable_indices,5))
generator.shuffle(variable_indices)
proof_path.extend(list(gen_size_n_blocks(variable_indices,4)))
generator.shuffle(variable_indices)
proof_path.extend(list(gen_size_n_blocks(variable_indices,3)))
generator.shuffle(variable_indices)
proof_path.extend(list(gen_size_n_blocks(variable_indices,2)))
generator.shuffle(variable_indices)
proof_path.extend(list(gen_size_n_blocks(variable_indices,1)))
#while len(variable_indices)>0:
#    i=generator.randrange(len(variable_indices))
#    v=variable_indices[-1]
#    m=m*x(v)
#    del variable_indices[-1]
#    if m.deg()==2:
#        proof_path.append(Polynomial(m))
#        m=Monomial()
#proof_path.reverse()
I=GPS_with_proof_path(ideal,[Polynomial(p) for p in proof_path], deg_bound=5,over_deg_bound=2000)

#I=buchberger_C_based2(hole6.ideal)
