# Copyright (c) 2005-2007 by The PolyBoRi Team


from sys import path
path.append("../../PyPolyBoRi")
from polybori.PyPolyBoRi import *
from gbrefs import my_import, load_data, clean_data
from optparse import OptionParser
import nf
import sys
from nf import symmGB_F2_python, GPS_with_suggestions
from string import Template
parser=OptionParser()
parser.add_option("-p", "--prot",
                  action="store_true", dest="prot", default=True,
                  help="protocoll on")

parser.add_option("-q", "--quiet",
                  action="store_false", dest="prot", default=True,
                  help="protocoll off")


parser.add_option("--over-deg",
                  action="store", type="int",dest="over_deg", default=200,
                  help="pairs over deg bound")

                            

parser.add_option("--add-sample",
                  action="store_true", dest="use_samples", default=False,
                  help="guess some variable samples")

parser.add_option("--sample-deg",
                  action="store", type="int",dest="sample_deg", default=6,
                  help="deg of a variable portion")
parser.add_option("--linear-lead-redsb",
                  action="store_true", dest="linear_lead_redsb", default=False,
                  help="calculate redsb for linear leads in elim stage")


parser.add_option("-R", "--no-redtail",
                  action="store_false", dest="red_tail", default=True,
                  help="no tail reductions")
parser.add_option("--aes",
            action="store_true", dest="aes", default=False,
            help="hint, that this is a AES System")

parser.add_option("-l", "--lazy",
                  action="store_true", dest="lazy", default=True,
                  help="trigger opt lazy option")
parser.add_option("-L", "--no-lazy",
                      action="store_false", dest="lazy", default=True,
                      help="trigger opt lazy option")

parser.add_option("-o", "--ordering",
                  action="store", dest="ordering", type="choice",
                  choices=["dp_asc","dlex","lp"],default="lp",
                  help="select monomial ordering")

parser.add_option("--alg",
                  action="store", dest="alg", type="choice",
                  choices=["symmGB_F2_python-sampled","slimgb","GPS","drawing","magma","fgb","other", "mult"],default="slimgb",
                  help="select algorithm")
(opts,args)=parser.parse_args()
challenge=args[0]
data=load_data(challenge)
import aes
if opts.aes:
  data.ideal=aes.preprocess(data.ideal)
def ctc_eliminate(ideal):
  ideal=[Polynomial(p) for p in ideal]
  lm2p={}
  for p in ideal:
    m=p.lead()
    if m in lm2p:
      lm2p[m].append(p)
    else:
      lm2p[m]=[p]
  linear_lead=[]
  others=set()
  for lm in lm2p:
    found=None
    if lm.deg()==1:
    
      for p in lm2p[lm]:
        if found is None:
          found=p
        else:
          if found.deg()>p.deg():
            found=p
    s=set(lm2p[lm])
    if not found is None:
      #print s
      s.remove(found)
      
      linear_lead.append(found)
    others.update(s)
  #print "calculated linear polynomials with lin leads"
  
  def lead(p):
    return p.lead()
  strat=GroebnerStrategy()
  if opts.linear_lead_redsb:
    linear_lead=sorted(linear_lead,key=lead)
    for p in linear_lead:
      print "lead",p.lead()
      print "orig_len",len(p)
      p=red_tail(strat,p)
      strat.addGenerator(p)
      print "reduced_len", len(p)
      #print p
    #linear_lead=symmGB_F2_python(linear_lead,optLazy=False)
    #linear_lead=linear_lead.minimalizeAndTailReduce()
  else:
    for p in linear_lead:
      strat.addGenerator(p)
  print "REDUCED"
  print others
  #for o in others:
  #  print o
  #  print o.lead()
  #  print nf3(strat,o,o.lead())  
  others=[nf3(strat,p,p.lead()) for p in others]
  others=[o for o in others if o!=Polynomial(0)]
  print "ELIMINATED"
  #print ",\n".join((str(p) for p in others))
  #print "]"
  #return
  return (others,linear_lead)
if not "ctc_ideals" in dir(data):
  (key_equations,rest_equations)=ctc_eliminate(data.ideal)
  print "REST"
  for p in rest_equations:
    print p.lead()
  print "KEY"
  for p in key_equations:
    print p.lead()
else:
  key_equations=[]
  for ideal in data.ctc_ideals:
     (key_equations_id,rest_equations_id)=ctc_eliminate(ideal)
     key_equations.extend(key_equations_id)
     print "."
change_ordering(getattr(OrderCode,opts.ordering))
#print key_equations
#print key_equations
magma_out_template=Template("""MYFIELDNAME:=FiniteField(2);
  MYRINGNAME< $vars >:=PolynomialRing(MYFIELDNAME,$nvars,"lex");
  MYIDEALNAME:=ideal< MYRINGNAME | $polys
  >;
  GroebnerBasis(MYIDEALNAME);
  exit;
  """)
fgb_out_template=Template("""
    libname:="/home/michael/salsa_linux/FGblib","/home/michael/salsa_linux/Gblib","/home/michael/salsa_linux/RS/share/RSlib","/home/michael/salsa_linux/DVlib","/home/michael/salsa_linux/RAGlib",libname:

    with(FGb):

    eqs:=[$polys]:
    vars:=[$vars]:

    print(fgb_gbasis(eqs,2,vars,[])):
  """)
import ctc_mult
def prob_factor(n):
  return 1-1.0/(2**n)
from random import Random
def calc_samples(sample_deg,vars):
  vars=list(vars)
  def to_mon(vars):
    res=Monomial()
    for v in vars:
      res=Monomial(Variable(v))*res
    return Polynomial(res)
  
  prob=1
  n=0
  f=prob_factor(sample_deg)
  while (prob*f)>0.5:
    prob=prob*f
    n=n+1
  assert n>sample_deg
  r=Random()
  return [to_mon(r.sample(vars,sample_deg)) for i in xrange(n)]

p_vars=[p.vars() for p in key_equations]
vars=Monomial()
sample_deg=opts.sample_deg
  
for m in p_vars:
  vars=vars*m
if opts.use_samples:
  samples=calc_samples(sample_deg,vars)
  print "using sample with", len(samples)
  print samples
  key_equations=key_equations+samples
if opts.alg=="symmGB_F2_python" or opts.alg=="slimgb-sampled":
  
  strat=symmGB_F2_python(key_equations,prot=opts.prot,optAllowRecursion=False,optLazy=opts.lazy,optRedTail=opts.red_tail)

else:
  if opts.alg=="GPS":
    max_deg=max((p.deg() for p in key_equations))
    over_deg=opts.over_deg
    strat=GPS_with_suggestions(key_equations,max_deg,over_deg_bound=over_deg, optLazy=opts.lazy,optRedTail=opts.red_tail,initial_bb=False)
  else:
    if opts.alg=="magma" or opts.alg=="fgb":
      vars=Monomial()
      for p in key_equations:
        vars=vars*p.vars()
      vars_string=", ".join([str(Variable(i)) for i in vars])
      
      nvars=vars.deg()
      polys=", ".join([str(p) for p in key_equations])
      polys_string=", "+ ", ".join([str(Variable(i))+"^2"+str(Variable(i)) for i in vars])
      if opts.alg=="magma":
        out_str=magma_out_template.substitute(dict(vars=vars_string,polys=polys,nvars=nvars))
      else:
        out_str=fgb_out_template.substitute(dict(vars=vars_string,polys=polys,nvars=nvars))
      out=open("eliminated."+opts.alg,"w")
      out.write(out_str)
      out.close()
      sys.exit(0);
    else:
      if opts.alg=="drawing":
        nf.print_matrices=True
        strat=symmGB_F2_python(key_equations,prot=opts.prot,optAllowRecursion=False,optLazy=opts.lazy,optRedTail=opts.red_tail)
      else:
        if opts.alg=="mult":
          print ctc_mult.mult_fast_sim_lex_smallest([p+Polynomial(1) for p in key_equations])
        else:
          #r=Random()
          #print "all:", len(key_equations)
          #for times in xrange(100):
          #  equations=key_equations
          #  for i in vars:
          #    val=r.choice((0,1))
          #    if val==1:
          #      equations=[Polynomial(p.set().subset0(i))+Polynomial(p.set().subset1(i)) for p in equations]
          #    else:
          #      assert val==0
          #      equations=[Polynomial(p.set().subset0(i)) for p in equations]
          #  print len([e for e in equations if e.isZero()])
          key_equations=[p for p in key_equations if p!=Polynomial(0)]
          lens=[(p.deg(),len(p)) for p in key_equations]
          min_len=min(lens)
          max_len=max(lens)
          print "KEY_Min", min_len
          print "KEY_Max", max_len
          comb_lens=[]
          for p in key_equations:
            for q in key_equations:
              if p!=q:
                pq=p+q
                pql=len(pq)
                pqd=p.deg()
                comb_lens.append((pqd,pql))
                print pql
          comb_lens=[l for l in comb_lens if l!=0]
          print "COMB_Min", min(comb_lens)
          print "COMB_Max", max(comb_lens)
       #p1=key_equations[0]
       #print p1.lead(),len(p1),p1.deg()
       #p2=key_equations[1]
       #print p2.lead(),len(p2),p2.deg()
       #q1=p1*p2
       #print q1.lead(),len(q1),q1.deg()
       #p3=key_equations[2]
       #print p3.lead(),len(p3),p3.deg()
       #p4=key_equations[3]
       #print p4.lead(),len(p4),p4.deg()
       #q2=p3*p4
       #print q2.lead(),len(q2),q2.deg()
       #o1=q1*q2
       #print o1.lead(),len(o1),o1.deg()
       #strat=GroebnerStrategy()
       #strat.enabledLog=True
       #strat.addGenerator(Variable(1)*Variable(2)+1)
       #strat.implications(0)
       #vars=Monomial()
       #for p in key_equations:
       #  vars=vars*p.vars()
       #width=4
       #assumption=Polynomial(0)
       #vars=list(vars)
       #for i in xrange(len(vars)):
       #  if i%width==0:
       #    prod=Monomial()
       #  prod=prod*Variable(vars[i])
       #  if i+1%width==0:
       #    assumption=(assumption+1)*(prod+1)+1
       #for i in xrange(len(key_equations)):
       #  for j in xrange(len(key_equations)):
       #    if i==j:
       #      continue
       #     p=(assumption+1)*(key_equations[i]+1)*(key_equations[j]+1)+1
       #     strat=GroebnerStrategy()
       #    strat.enabledLog=True
       #    strat.addGenerator(p)
       #    strat.implications(0)
         
for p in strat.minimalizeAndTailReduce():
  print p
#print "REST"
#for p in rest_equations:
#  print p
#print "KEY"
#for p in key_equations:
#  print p

del p
del strat
del key_equations
try:
  del rest_equations
  del m
  del one
except NameError:
  pass

clean_data(data)
