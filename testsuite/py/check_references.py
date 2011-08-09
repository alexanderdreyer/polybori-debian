# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
path.append("../../PyPolyBoRi")
from optparse import OptionParser
from gbrefs import my_import, load_data, clean_data,number_of_declared_vars
import gbrefs
parser = OptionParser()
parser.add_option("-o", "--ordering",
                  action="store", dest="ordering", type="choice",
                  choices=["dp_asc","dlex","lp","block_dlex"],default="lp",
                  help="select monomial ordering")
parser.add_option("--blocks",
                  action="store", type="string",dest="blocks", default=gbrefs.SINGLE,
                  help="block structure")


#from data import stas1
from nf import *
from re import *
from time import clock
from string import Template
from polybori.PyPolyBoRi import *
(options, args) = parser.parse_args()
import StringIO
import subprocess
def check(a):
    in_file=a
    in_file=sub(r"\.py","",in_file)
    in_file=sub(r"/",".", in_file)
    #mydata=__import__(in_file)
    
    mydata=load_data(in_file)
    nvars=number_of_declared_vars(mydata)
    var_names=[str(Variable(i)) for i in xrange(nvars)]
    var_str_fwd="("+",".join(var_names)+")"
    var_str_bwd="("+",".join(reversed(var_names))+")"
    #mydata.r.nVars()
    template=Template("""ring r=2,$varstr,$ordstr;
    option(redTail);
    option(redSB);
    ideal fe;
    int i;
    for(i=1;i<=nvars(r);i++){
        fe=fe,var(i)^2+var(i);
    }
    ideal eq=$ideal;
    eq=eq,fe;
    ideal ref=$ref;
    ref=ref,fe;
    ref=simplify(ref,32);
    attrib(ref,"isSB",1);
    //reduce(eq,ref);
    ideal sing_ref=std(eq);
    simplify(reduce(ref,sing_ref),2);
    simplify(reduce(sing_ref,ref),2);
    exit;
    """)
    
    def x(i):
        return Variable(i)
    ps=[]
    
    myattr=sub(r"data\.","",in_file)
    #myattr=sub(r"\.","/", myattr)
    #mydata=getattr(mydata,myattr)
    print myattr
    reference=gbrefs.load_ref(in_file, ordering=options.ordering,blocks=options.blocks)
    for l in reference.split("\n"):#open("ref/"+myattr+".ref"):
        #print l
        if len(l)>0:
            p=eval(l, {"x":x})
            ps.append(p)
    ref_str=",\n".join([str(p) for p in ps])
    ideal_str=sub(r"\[","",sub(r"\]","",str(mydata.ideal)))
    if options.ordering=="lp":
        ordstr="lp"
        varstr=var_str_fwd#"x(0.."+str(nvars-1)+")"
    else:
        if options.ordering=="dlex":
            ordstr="(a("+",".join(nvars*["1"])+"),lp)"
            varstr=var_str_fwd#"x(0.."+str(nvars-1)+")"
        else:
            if options.ordering=="dp_asc":
                ordstr="dp"
                #varstr=[x(nvars-1-i) for i in range(0,nvars)]
                #varstr="("+",".join([str(x) for x in varstr])+")"
                varstr=var_str_bwd
            else:
                
                if options.ordering=="block_dlex":
                    varstr=var_str_fwd#"x(0.."+str(nvars-1)+")"
                    ordstr="("
                    last=0
                    for s in gbrefs.parse_blocks(options.blocks,mydata)+[nvars]:
                        ordstr=ordstr+"Dp("+str(s-last)+")"
                        if s!=nvars:
                            ordstr=ordstr+","
                        last=s
                    ordstr=ordstr+")"
                else:
                    #not implemented    
                    raise Exception
         
    sing_inp=template.substitute({"nvars":nvars-1,"ideal": ideal_str,
        "ordstr":ordstr,"varstr":varstr,"ref":ref_str})
    
    proc=subprocess.Popen(["Singular","-tq"], stdin=subprocess.PIPE)
    proc.communicate(input=sing_inp)
    
    #del mydata.ideal
    del ps
    del p
    clean_data(mydata)
    del mydata
    
    
#print in_file
for a in args:
    check(a)

    


