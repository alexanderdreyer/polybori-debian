# Copyright (c) 2005-2007 by The PolyBoRi Team

from polybori.PyPolyBoRi import *
from nf import *
import parse
import nav




(r,I)=parse.translate_ideal("u*x+v*w+v*x+x*y+w*x+x*y*z, x*y+w,z*v+x,x*y+z;", ["u", "v","w","x","y","z"])

print I
print len(I)
for i in I:
    print len(i)
I= buchberger2(I)
#print len
for i in I:
    print nav.support(i)
