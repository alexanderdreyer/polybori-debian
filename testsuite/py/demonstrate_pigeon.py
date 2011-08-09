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
from polybori.PyPolyBoRi import Polynomial
from polybori.gbrefs import load_data, clean_data
from time import time,clock
from polybori.memusage import *
from fpformat import fix
parser = OptionParser()
parser.add_option("-t", "--showtime",
                  action="store_true", dest="showtime", default=False,
                  help="show time")

def main(argv=None):
    (opts,args)= parser.parse_args()
    data=load_data(args[0])
    t=time()
    tc=clock()
    prod=Polynomial(1)
    ideal=[p for p in data.ideal if not p.isZero()]
    def sort_key(l):
        return l.deg()
    ideal.sort(key=sort_key,reverse=False)
    for (i,p) in enumerate(ideal):
        print "status:", fix(i/float(len(ideal))*100,0)+"%", "length:",long(prod.set().sizeDouble())
        prod=(p+1)*prod
    prod=prod+1
    
    print "multiplied, result:", prod

    if opts.showtime:
        print "used time:", t2-t
        print "used clock: (user time modulo)", tc2-tc
        print "virtual memory peak:", memorypeak(), "KB"
        print "resident memory peak:", residentpeak(), "KB"
    return 0


if __name__ == "__main__":
  sys.exit(main())
