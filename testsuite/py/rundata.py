# Copyright (c) 2005-2007 by The PolyBoRi Team
import pathadjuster
from polybori.gbrefs import my_import, load_file, clean_data
from optparse import OptionParser
import sys
import resource
from polybori.memusage import *
from polybori.gbrefs import SINGLE,AUTO,parse_blocks

parser = OptionParser()

parser.add_option("--blocks",
                  action="store", type="string",dest="blocks", default=AUTO,
                  help="block structure")
parser.add_option("--deg-bound",
                  action="store", type="int",dest="deg_bound", default=1000000000000,
                  help="deg bound")
parser.add_option("-s", "--show",
                  action="store_true", dest="show", default=False,
                  help="show result")
parser.add_option("--invert",
                  action="store_true", dest="invert", default=False,
                  help="invert")

parser.add_option("--auto",
                  action="store_true", dest="auto", default=False,
                  help="override all options and use pure builtin heuristic")
parser.add_option("--preprocess-only",
                  action="store_true", dest="preprocess_only", default=False,
                  help="only preprocess")

parser.add_option("--aes",
                  action="store_true", dest="aes", default=False,
                  help="hint, that this is a AES System")



parser.add_option("--full-prot",
                  action="store_true", dest="full_prot", default=False,
                  help="full protocoll on")
parser.add_option("-c", "--cleanup",
                  action="store_true", dest="cleanup", default=False,
                  help="clean up")
parser.add_option("-t", "--showtime",
                  action="store_true", dest="showtime", default=False,
                  help="show time / is implied by not quiet")


parser.add_option("--show-redSB",
                  action="store_true", dest="redsb", default=True,
                  help="toggle redSB output")
parser.add_option("--no-show-redSB",
                  action="store_false", dest="redsb", default=True,
                  help="toggle redSB output")
parser.add_option("-l", "--lazy",
                  action="store_true", dest="lazy", default=True,
                  help="trigger opt lazy option")
parser.add_option("-L", "--no-lazy",
                  action="store_false", dest="lazy", default=True,
                  help="trigger opt lazy option")
parser.add_option("-e", "--exchange",
                  action="store_true", dest="exchange", default=True,
                  help="trigger opt exchange option")
parser.add_option("-E", "--no-exchange",
                  action="store_false", dest="exchange", default=True,
                  help="trigger opt exchange option")

parser.add_option("--recursion",
                  action="store_true", dest="recursion", default=False,
                  help="trigger opt recursion option")

parser.add_option("--lex-eliminate-first",
                  action="store_true", dest="llfirst", default=False,
                  help="first eliminate all variables, which have a lex. leading term in the initial system")


parser.add_option("--lex-eliminate-on-the-fly-first",
                  action="store_true", dest="llfirstonthefly", default=False,
                  help="first eliminate all variables, which have a lex. leading term in the initial system")

parser.add_option("--noro",
                  action="store_true", dest="noro", default=False,
                  help="use noro F4")

parser.add_option("--faugere",
                  action="store_true", dest="faugere", default=False,
                  help="use F4")
parser.add_option("--ll",
                  action="store_true", dest="ll", default=False,
                  help="use linear lead reductions")

parser.add_option("--no-recursion",
                  action="store_false", dest="recursion", default=False,
                  help="trigger opt recursion option")


parser.add_option("-R", "--no-redtail",
                  action="store_false", dest="red_tail", default=True,
                  help="no tail reductions")
parser.add_option("-g", "--max-growth",
                  action="store", type="float",dest="max_growth", default=2.0,
                  help="maximal growth during reduction before delaying")
parser.add_option("--selection-size",
                  action="store", type="int",dest="selection_size", default=1000,
                  help="choose selection size (increase parallelism)")
parser.add_option("--step-factor",
                  action="store", type="float",dest="step_factor", default=1,
                  help="maximal growth during reduction before delaying")
parser.add_option("-I", "--no-implications",
                  action="store_false", dest="implications", default=False,
                  help="no implications")
parser.add_option("-i", "--implications",
                  action="store_true", dest="implications", default=False,
                  help="implications")                  
parser.add_option("-m", "--draw-matrices",
                  action="store_true", dest="draw_matrices", default=False,
                  help="save matrices as png")
parser.add_option("--matrix-prefix",
                  action="store", dest="matrix_prefix", type="string", default="matrix",
                  help="prefix for saved matrices")
parser.add_option("-o", "--ordering",
                  action="store", dest="ordering", type="choice",
                  choices=["dp_asc","dlex","lp","block_dlex","block_dp_asc"],default="lp",
                  help="select monomial ordering")
parser.add_option("--implementation",
                  action="store", dest="implementation", type="choice",
                  choices=["C","Python"],default="Python",
                  help="select implemtation")


parser.add_option("--heuristic",
                  action="store_true", dest="heuristic", default=True,
                  help="enable use of heuristic")
parser.add_option("--no-heuristic",
                  action="store_false", dest="heuristic", default=True,
                  help="disable use of heuristic")


# For those options, which occur in gbcore default argument is ignored in the
# following , and the one from gbopts is used.
from polybori.gbcore import *
parser.set_defaults(**groebner_basis.options)

parser.add_option("-q", "--quiet",
                  action="store_false", dest="prot", default=True,
                  help="protocoll off")

parser.add_option("-p", "--prot",
                  action="store_true", dest="prot", default=True,
                  help="protocoll on")

from polybori.nf import *
import polybori.aes as aes

from re import *
from time import time,clock
from polybori.PyPolyBoRi import *
from polybori.statistics import used_vars
(options, args) = parser.parse_args()

mydata=load_file(args[0])
I=mydata.ideal
t=time()
tc=clock()

change_ordering(getattr(OrderCode, options.ordering))
if match("block",options.ordering):
    block_starts=parse_blocks(options.blocks,mydata)
    block_starts.sort()
    for s in block_starts:
        append_ring_block(s)
if not options.auto:
    I = groebner_basis(I, **dict([(k,getattr(options,k)) for k in dir(options) if k in groebner_basis.options]))
else:
    I= groebner_basis(I,prot=options.prot)

if options.show:
    if options.redsb and options.deg_bound>10000:
      for p in I:
          print p

    else:
        if options.deg_bound>10000:
          for p in I:
            print p
        else:
          for i in xrange(len(I)):
            print I[i]
t2=time()
tc2=clock()
from copy import copy

clean_data(mydata)
if options.prot or options.showtime:
    print "used time:", t2-t
    print "used clock: (user time modulo)", tc2-tc
    print "virtual memory peak:", memorypeak(), "KB"
    print "resident memory peak:", residentpeak(), "KB"






