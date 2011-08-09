# Copyright (c) 2005-2007 by The PolyBoRi Team

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
from polybori.PyPolyBoRi import change_ordering,OrderCode,Polynomial
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
    #print [len(p) for p in eliminate(data.ideal)]
    from polybori.nf import symmGB_F2_python
    (linear,normal_form,ideal)=eliminate(data.ideal,on_the_fly=False)
    print "eliminated"
    #change_ordering(OrderCode.dp_asc)
    #for p in symmGB_F2_python(ideal,prot=True,use_noro=False).minimalizeAndTailReduce():
    #    print p
    prod=Polynomial(1)
    ideal=[p for p in ideal if not p.isZero()]
    def sort_key(l):
        return l.deg()
        #return l.navigation().value()
    ideal.sort(key=sort_key,reverse=False)
    #print "IDEAL",ideal
    for p in ideal:
        print "+"
        prod=(p+1)*prod
    prod=prod+1
    print "multiplied"
    #print prod

    for p in symmGB_F2_python([prod],prot=True,use_noro=False).minimalizeAndTailReduce():
       print p
    del p
    del prod
    t2=time()
    tc2=clock()
    clean_data(data)
    #start here
    if opts.showtime:
        print "used time:", t2-t
        print "used clock: (user time modulo)", tc2-tc
        print "virtual memory peak:", memorypeak(), "KB"
        print "resident memory peak:", residentpeak(), "KB"
    return 0

if __name__ == "__main__":
  sys.exit(main())
