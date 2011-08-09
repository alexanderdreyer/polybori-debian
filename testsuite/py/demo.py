#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by Michael Brickenstein on 2007-03-14.
Copyright (c) 2007 The PolyBoRi Team. See LICENSE file.
"""

import sys
from optparse import OptionParser

import pathadjuster
LL_ELIMINATE="lleliminate"
from polybori.PyPolyBoRi import change_ordering,OrderCode,Polynomial, count_double
from polybori.ll import eliminate
from polybori.gbrefs import load_data, clean_data
from time import time,clock
from polybori.memusage import *
parser = OptionParser()
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")

parser.add_option("-t", "--showtime",
                  action="store_true", dest="showtime", default=False,
                  help="show time")

def main(argv=None):
    (opts,args)= parser.parse_args()
    data=load_data(args[0])
    t=time()
    tc=clock()
    from polybori.nf import symmGB_F2_python
    ideal=data.ideal

    prod=Polynomial(1)
    ideal=[p for p in ideal if not p.isZero()]
    def sort_key(l):
        return l.deg()
    ideal.sort(key=sort_key,reverse=False)
    
    for p in ideal:
        
        prod=(p+1)*prod
        print "multiply with:",p+1
        count_len=count_double(prod)
        count_nodes=prod.set().nNodes()
        if count_nodes:
            print "intermediate result size:",(13-len(str(count_len)))*" ",count_len,"terms", (10-len(str(count_nodes)))*" ", count_nodes, "nodes", count_nodes/count_len, "nodes/terms"
    prod=prod+1
    print "multiplied"

    for p in symmGB_F2_python([prod],prot=True,use_noro=False).minimalizeAndTailReduce():
       print p
    del p
    del prod
    t2=time()
    tc2=clock()
    if opts.showtime:
        print "used time:", t2-t
        print "used clock: (user time modulo)", tc2-tc
        print "virtual memory peak:", memorypeak(), "KB"
        print "resident memory peak:", residentpeak(), "KB"
    return 0

if __name__ == "__main__":
  sys.exit(main())
