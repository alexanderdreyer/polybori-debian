# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
import pathadjuster
from optparse import OptionParser
from StringIO import StringIO
import subprocess
import uu, gzip
parser = OptionParser()
from polybori.gbrefs import SINGLE,AUTO,parse_blocks,ordering_suffix
parser.add_option("-p", "--python",
                  action="store", dest="python", default="python",
                  help="choose python interpreter")
parser.add_option("-o", "--ordering",
                  action="store", dest="ordering", type="choice",
                  choices=["dp_asc","dlex","lp","block_dlex","block_dp_asc"],default="lp",
                  help="select monomial ordering")
parser.add_option("--aes",
                  action="store_true", dest="aes", default=False,
                  help="hint, that this is a AES System")

parser.add_option("--blocks",
                  action="store", type="string",dest="blocks", default=AUTO,
                  help="block structure")

sources=["stas1"]+["uf20_0"+str(i) for i in xrange(1,1000)]

from os import system
from re import sub
(options, args)=parser.parse_args()
system("mkdir -p ref")
from os import mkdir, makedirs
#for s in sources:#
import os.path
order_suffix=ordering_suffix(options.ordering,options.blocks)
for a in args:
    name=sub("data/","",a)
    name=sub(r"\.py","",name)
    l=name.split("/")[:-1]
    d="ref/"+"/".join(l)
    if not os.path.isdir(d):
        if os.path.isfile(d):
            raise Exception
        makedirs(d)
    print d,name
    #system(options.python+" rundata.py -qs " + a +" >ref/"+name+".ref")
    if options.aes:
      #print "AES"
      proc=subprocess.Popen([options.python, "rundata.py","-qs", "--auto","--aes","--ordering="+options.ordering,"--blocks="+options.blocks,a], stdout=subprocess.PIPE)
    else:
      proc=subprocess.Popen([options.python, "rundata.py","-qs", "--auto","--ordering="+options.ordering,"--blocks="+options.blocks,a], stdout=subprocess.PIPE)
    ref_out=proc.communicate()[0]
    buf_out=StringIO()
    zipped=gzip.GzipFile(filename=a.split("/")[-1]+".ref", mode="w",fileobj=buf_out)
    zipped.write(ref_out)
    zipped.close()
    buf_out=buf_out.getvalue()
    buf_out=StringIO(buf_out)
    uu.encode(out_file=open("ref/"+name+order_suffix+".ref.gz.uu","w"),in_file=buf_out)
    #print ref_out
    #print options.python+" rundata.py -qs " + a +" >ref/"+name+".ref"
    #system(options.python+" rundata.py -qs data/"+ s+".py >ref/"+s+".ref")
