# Copyright (c) 2005-2007 by The PolyBoRi Team
#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by Michael Brickenstein on 2007-06-15.
Copyright (c) 2007 The PolyBoRi Team. See LICENSE file.
"""
import sys
from optparse import OptionParser
from time import time,clock
if __name__=='__main__':

    import pathadjuster
    from polybori.gbrefs import my_import, load_data, clean_data
    from polybori.nf import symmGB_F2_python
    from polybori.PyPolyBoRi import change_ordering, OrderCode

parser = OptionParser()
parser.add_option("-q", "--quiet",
                  action="store_false", dest="prot", default=True,
                  help="protocoll off")
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")


def main(argv=None):
     (opts,args)= parser.parse_args()
     mydata=load_data(args[0])
     change_ordering(OrderCode.dp_asc)
     t=time()
     tc=clock()
     I=symmGB_F2_python(mydata.ideal,optAllowRecursion=False,use_faugere=True,prot=opts.prot,ll=True,selection_size=500000,implications=False,optRedTail=False)
     I=I.minimalizeAndTailReduce()
     t2=time()
     tc2=clock()
     print "used time:", t2-t
     print "used clock: (user time modulo)", tc2-tc
     for p in I:
         print p
     del p
     del I
     clean_data(mydata)
     return 0

if __name__ == "__main__":

    sys.exit(main())
