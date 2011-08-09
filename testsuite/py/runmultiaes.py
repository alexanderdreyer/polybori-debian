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
    sys.path.append("../../PyPolyBoRi")
from ll import ll_encode
from gbrefs import my_import, load_data, clean_data
from nf import symmGB_F2_python
from polybori.PyPolyBoRi import change_ordering, OrderCode,set_variable_name, append_ring_block,ll_red_nf,Monomial,Variable
from itertools import chain
parser = OptionParser()
parser.add_option("-q", "--quiet",
                  action="store_false", dest="prot", default=True,
                  help="protocoll off")
#parser.add_option("-v", "--verbose",
#                  action="store_true", dest="verbose", default=True,
#                  help="verbose output")




def main(argv=None):
     (opts,args)= parser.parse_args()
     data=load_data(args[0])
     change_ordering(OrderCode.lp)
     key_vars=Monomial()
     for k in data.key_schedule:
         key_vars=key_vars*k.vars()
     all_vars=Monomial()
     print 4556
     for k in chain(data.key_schedule,data.encryption,data.plain[0],data.cipher[0]):
        all_vars=all_vars*k.vars()
     instance_vars=all_vars/key_vars
     max_index=max(all_vars)
     instance_width=len(instance_vars)
     number_instances=20
     print 1234
     jsgksjk=Variable(20000)
     print 93898
     key_mappping=[Variable(v)+Variable(max_index+1+number_instances*instance_width+i) for (i,v) in enumerate(key_vars)]
     print 2343
     for j in xrange(len(key_vars)):
         set_variable_name(max_index+1+number_instances*instance_width+j,"key"+str(j))
     ideal=[]
     for instance in xrange(number_instances):
         print instance
         for j in xrange(instance_width):
             print j
             set_variable_name(max_index+1+instance*instance_width+j,"instance"+str(instance)+"_"+str(j))
         rep=[Variable(v)+Variable(max_index+1+instance*instance_width+i) for (i,v) in enumerate(instance_vars)]+key_mappping
         #for r in rep:
         #    print r
         rep=ll_encode(rep)
         instance_system=[ll_red_nf(p,rep) for p in chain(data.encryption,data.cipher[instance],data.plain[instance])]
         #print instance_system
         ideal.extend(instance_system)
     key_system=[ll_red_nf(p,ll_encode(key_mappping)) for p in data.key_schedule]
     ideal.extend(key_system)
     print "IDEAL TOG",len(ideal)
     #print ideal
     change_ordering(OrderCode.block_dp_asc)
     append_ring_block(max_index+instance_width*number_instances+1)
     
     res=symmGB_F2_python(ideal,prot=True,optRedTail=False).minimalizeAndTailReduce()
     for p in res:
         print p
     
     return 0

if __name__ == "__main__":
    sys.exit(main())
