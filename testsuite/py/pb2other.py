# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
import pathadjuster
from polybori.PyPolyBoRi import *
from polybori.gbrefs import my_import, load_data, clean_data
from optparse import OptionParser
import sys
import resource
from string import Template
from polybori.statistics import used_vars
from datetime import date
parser = OptionParser()

PB="pb"
SING="sing"
MAGMA="magma"
ALL="all"
SLIM="slim"
MATHEMATICA="mathematica"
MAPLE="maple"
FGB="fgb"
SYMBOLIC_DATA="sd"

parser.add_option("-f", "--format",
                  action="store", dest="format", type="choice",
                  choices=[ALL,SYMBOLIC_DATA,MAGMA,SING,PB,SLIM,MAPLE,MATHEMATICA,FGB],default=MAGMA,
                  help="select format from SING/PB")

parser.add_option("-c", "--comment",
                  action="store", dest="comment", type="string",
                  default="",
                  help="comment for the generated files")

parser.add_option("--creator",
                  action="store", dest="creator", type="string",
                  default="",
                  help="creator name")


parser.add_option("-i", "--invert-variable-order",
                  action="store_true", dest="invert", default=False,
                  help="invert variable order")

parser.add_option("-o", "--ordering",
                  action="store", dest="ordering", type="choice",
                  choices=["dp_asc","dlex","lp","block_dlex","block_dp_asc"],
                  default="lp", help="select monomial ordering")

(options, args) = parser.parse_args()



mydata=load_data(args[0])

def with_out_braces(s):
  return sub(r"\(|\)","",s)
def vname(s):
  return with_out_braces(s)
from re import sub

if options.ordering == "dp_asc" :
  options.invert = not(options.invert)

var_names=[vname(str(Variable(v))) for v in used_vars(mydata.ideal)]
if options.invert:
    var_names.reverse()

nvars=len(var_names)

#var_names=[vname(str(Variable(i))) for i in xrange(nvars)]
#vars_string=with_out_braces(",".join(var_names))
vars_string=", ".join(var_names)
polys_string=with_out_braces(",\n".join([str(p) for p in mydata.ideal])+","+",".join([v+"^2+"+v for v in var_names]))
try:
  del p
except:
  pass
singular_out_template=Template("""
  ring MYRINGNAME=2,($vars),$order;
  ideal MYIDEALNAME=$polys;
  timer=1;
  option(redTail);
  $alg(MYIDEALNAME);
  memory(2);
  exit;
  """)
magma_out_template=Template("""MYFIELDNAME:=FiniteField(2);
  MYRINGNAME< $vars >:=PolynomialRing(MYFIELDNAME,$nvars,"$order");
  MYIDEALNAME:=ideal< MYRINGNAME | $polys
  >;
  GroebnerBasis(MYIDEALNAME);
  exit;
  """)
maple_out_template=Template("""
  with(Groebner):
  G:=[$polys]:
  
  Basis(G,$order($vars),characteristic=2);
""")

  #libname:="/home/michael/salsa_linux/FGblib","/home/michael/salsa_linux/Gblib","/home/michael/salsa_linux/RS/share/RSlib","/home/michael/salsa_linux/DVlib","/home/michael/salsa_linux/RAGlib",libname:

fgb_out_template=Template("""

  with(FGb):
  
  eqs:=[$polys]:
  vars:=[$vars]:
  
  print(fgb_gbasis(eqs,2,vars,[])):
""")
#format=SLIMGB
format=options.format
order=options.ordering

if order == "dlex":
  order_sing = "Dp"
  order_magma = "glex"
  order_maple = "grlex"
else:
  if order == "dp_asc":
    order_sing = "dp"
    order_magma = "grevlex"
    order_maple = "tdeg"
  else:
    order_sing = "lp"
    order_magma = "lex"
    order_maple = "plex"

if format==SLIM:
  print singular_out_template.substitute(dict(vars = vars_string,
                                              polys = polys_string,
                                              alg = "symmGB_F2_python",
                                              order = order_sing))

if format==SING:
  print singular_out_template.substitute(dict(vars = vars_string,
                                              polys = polys_string, alg = "std",
                                              order = order_sing))
  
if format==MAGMA:
  print magma_out_template.substitute(dict(vars = vars_string,
                                           polys = polys_string,
                                           nvars = len(var_names),
                                           order = order_magma))

if format==MAPLE:
  print maple_out_template.substitute(dict(vars = vars_string,
                                           polys = polys_string,
                                           nvars = len(var_names),
                                           order = order_maple))

if format==FGB:
  print fgb_out_template.substitute(dict(vars=vars_string,polys=polys_string,nvars=len(var_names)))
if format==SYMBOLIC_DATA:
    comment=options.comment
    from lxml import etree
    today=str(date.today())
    creator=options.creator
    root=etree.Element("INTPS",createdAt=today,createdBy=creator)
    #root.text="<!-- $Id: pb2other.py,v 1.7 2008/07/08 21:41:59 alexanderdreyer Exp $ -->"
    vars_string=vars_string.replace(" ","")
    vars_element=etree.SubElement(root,"vars")
    vars_element.text=vars_string
    basis=etree.SubElement(root,"basis")
    
    polys=[with_out_braces(str(p)) for p in mydata.ideal]+[v+"^2 + " +v for v in var_names]
    for p in polys:
        p_element=etree.SubElement(basis,"poly")
        p_element.text=p
    comment_element=etree.SubElement(root,"Comment")
    comment_element.text=comment
    etree.SubElement(root,"ChangeLog")
    print etree.tostring(root, pretty_print=True)
