#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by Michael Brickenstein on 2007-06-19.
Copyright (c) 2007 The PolyBoRi Team. See LICENSE file.
"""

import sys
sys.path.append("../../PyPolyBoRi")
from polybori.PyPolyBoRi import *
from optparse import OptionParser
from gbrefs import load_data

parser = OptionParser()
from re import match
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")

def ideal_to_system(i,r):
    i=str(i).replace(", ",",\n")
    r=str(r)
    i=i.replace("Y","Y"+r+"_")
    i=i.replace("Z","Z"+r+"_")
    i=i.replace("K","K"+r+"_")
    i=i.replace("X","X"+r+"_")
    i=i.replace("K"+r+"_000","K000")
    return i

def main(argv=None):
     (opts,args)= parser.parse_args()
     data_file=args[0]
     mydata=load_data(data_file)
     vars_normal=[]
     vars_key=[]
     i=0
     while str(Variable(i))!="K000000":
         var_str=str(Variable(i))
         if match("K000",var_str):
             vars_key.append(var_str)
         else:
             vars_normal.append(var_str)
         i=i+1
     vars_key.append("K000000")
     i=0
     ideals=[]
     while hasattr(mydata,"ideal"+str(i)):
         attr="ideal"+str(i)
         ideals.append(ideal_to_system(getattr(mydata,attr),i))
         
         #print ideal_to_round(getattr(mydata,attr),i)
         i=i+1
     systems=i
     vars_res=[s[0]+str(r)+"_"+s[1:] for r in xrange(0,systems) for s in vars_normal]+vars_key
     

     giant_ideal="["+",\n".join([ideal.replace("]","").replace("[","") for ideal in ideals])+"]"
     print "declare_ring("+str(vars_res)+")"
     print "block_start_hints=["+str(len(vars_res)-len(vars_key))+"]"
     print "ideal=\\"
     print giant_ideal
     #print giant_ideal
     
     return 0

if __name__ == "__main__":
    sys.exit(main())
