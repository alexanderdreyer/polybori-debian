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
    for p in symmGB_F2_python(eliminate(data.ideal)).minimalizeAndTailReduce():
        print p
    clean_data(data)
    #start here
    return 0

if __name__ == "__main__":
  sys.exit(main())
