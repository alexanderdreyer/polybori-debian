# Copyright (c) 2005-2007 by The PolyBoRi Team

#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by Michael Brickenstein on 2007-02-20.
Copyright (c) 2007 The PolyBoRi Team. See LICENSE file.
"""

import sys
from optparse import OptionParser

sys.path.append("../../PyPolyBoRi")
import gbrefs
from polybori.PyPolyBoRi import Monomial, Polynomial
parser = OptionParser()
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")


def main(argv=None):
     (opts,args)= parser.parse_args()
     data=gbrefs.load_data(args[0])
     v=Monomial()
     lm=dict()
     for p in data.ideal:
       p=Polynomial(p)
       if p.isZero():
         continue
       v=v*p.vars()
       l=p.lead()
       if l.deg()>1:
         print "wrong ldeg", l
       else:
         lm[l]=p
     print "non assigned vars:", v.deg()-len(lm)
       
     return 0

if __name__ == "__main__":
    sys.exit(main())
