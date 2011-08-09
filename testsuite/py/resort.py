# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
path.append("../../PyPolyBoRi")
from gbrefs import my_import, load_data, clean_data
from optparse import OptionParser
import sys
import resource
from polybori.PyPolyBoRi import *
parser = OptionParser()
def non_linear_part(p):
  """including constants"""
  p=Polynomial(p)
  used_vars=set()
  for m in p:
    if m.deg()>1:
      for v in m:
        used_vars.add(v)
  return used_vars
def linear_part(p):
  p=Polynomial(p)
  return set([iter(m).next() for m in p if m.deg()==1]).difference(non_linear_part(p))
class LinearLeadCondition(object):
  """The LinearLeadCondition class."""
  def __init__(self, p):
    #self.p = Polynomial(p)
    self.lp=linear_part(p)
    self.hp=set(Polynomial(p).vars()).difference(self.lp)
  def fullfilled(self, order):
    if len(self.lp)==0:
      print "warning: trivial conditition"
      return True
    else:
      for v in self.lp:
        finished=True
        for v2 in self.hp:
          assert v!=v2
          assert order[v2]!=order[v]
          #print order[v2], order[v]
          if order[v2]<order[v]:
            finished=False
            break
        #print self.lp,self.hp
        if finished:
          return True
      return False

def used_vars_ideal(data):
  used_vars=set()
  for p in data.ideal:
    for v in Polynomial(p).vars():
      used_vars.add(v)
  return used_vars
def check(data):
  used_vars=used_vars_ideal(data)
  order=dict([(v,(v,)) for v in used_vars])
  conditions=[LinearLeadCondition(p) for p in data.ideal]
  del p
  positive=0
  negative=0
  for c in conditions:
    if c.fullfilled(order):
      positive=positive+1
    else:
      negative=negative+1
      print c.lp,c.hp

  print "ok:",positive,"failed:", negative

def calc_new_order(data):
  """this alg is not garantied to terminate"""
  
  def find_unfullfilled(conditions,order):
    for c in conditions:
      if not c.fullfilled(order):
        return c
    return False
  used_vars=used_vars_ideal(data)
  order=dict([(v,(v,)) for v in used_vars])
  conditions=[LinearLeadCondition(p) for p in data.ideal]
  while(find_unfullfilled(conditions,order)):
    c=find_unfullfilled(conditions,order)
    
if __name__ == '__main__':
  (options, args) = parser.parse_args()
  input_file=args[0]
  data=load_data(input_file)
  check(data)
  #order=calc_new_order(data)
