#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by Alexander Dreyer, Michael Brickenstein on 2007-05-11.
Copyright (c) 2007 The PolyBoRi Team. 

          
See LICENSE file.
"""

import sys
from optparse import OptionParser
sys.path.append("../../PyPolyBoRi")
LL_ELIMINATE="lleliminate"

from ll import eliminate
from gbrefs import load_data, clean_data
parser = OptionParser()
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")


def main(argv=None):
    (opts,args)= parser.parse_args()
    data=load_data(args[0])
    #print [len(p) for p in eliminate(data.ideal)]
    from nf import symmGB_F2_python
    print data.ideal
    
   # print ideal
  #  print [len(p) for p in eliminate(ideal)]
    #print  [p for p in ideal]
    ideal = symmGB_F2_python(data.ideal).minimalizeAndTailReduce()
    for p in ideal:
        print p.lead() , p.set().nNodes()

    #    print "hihi"
        #, p.set().nNodes()
    #del p


    clean_data(data)
    #clean_data(ideal)
    del ideal
    del data
    
    #start here

    return 0

if __name__ == "__main__":
  sys.exit(main())
