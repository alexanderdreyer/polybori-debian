# Copyright (c) 2005-2007 by The PolyBoRi Team
from optparse import OptionParser
parser = OptionParser()
#parser.add_option("-s", "--show",
#                  action="store_true", dest="show", default=False,
#                  help="show result")
parser.add_option("-q", "--quiet",
                  action="store_false", dest="prot", default=True,
                  help="protocoll off")
parser.add_option("--aes",
                  action="store_true", dest="aes", default=False,
                  help="hint, that this is a AES System")
parser.add_option("-p", "--prot",
                  action="store_true", dest="prot", default=True,
                  help="protocoll on")
#parser.add_option("--full-prot",
#                  action="store_true", dest="full_prot", default=False,
#                  help="full protocoll on")
#parser.add_option("-c", "--cleanup",
#                  action="store_true", dest="cleanup", default=False,
#                  help="clean up")
parser.add_option("-t", "--showtime",
                  action="store_true", dest="showtime", default=False,
                  help="show time / is implied by not quiet")
parser.add_option("-l", "--lazy",
                  action="store_true", dest="lazy", default=True,
                  help="trigger opt lazy option")
parser.add_option("-L", "--no-lazy",
                  action="store_false", dest="lazy", default=False,
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
parser.add_option("--no-recursion",
                  action="store_false", dest="recursion", default=False,
                  help="trigger opt recursion option")


parser.add_option("-R", "--no-redtail",
                  action="store_false", dest="red_tail", default=True,
                  help="no tail reductions")
parser.add_option("-g", "--max-growth",
                  action="store", type="float",dest="max_growth", default=2.0,
                  help="maximal growth during reduction before delaying")

parser.add_option("--deg-bound",
                  action="store", type="int",dest="deg_bound", default=5,
                  help="deg bound")                  
parser.add_option("--over-deg",
                  action="store", type="int",dest="over_deg", default=200,
                  help="pairs over deg bound")                            
                  

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
                  choices=["dp_asc","dlex","lp"],default="lp",
                  help="select monomial ordering")
#parser.add_option("--implementation",
#                  action="store", dest="implementation", type="choice",
#                  choices=["C","Python"],default="Python",
#                  help="select implemtation")
from sys import path
import pathadjuster
#xpath.append("../../PyPolyBoRi")
#from data import stas1
from polybori.nf import *
from re import *
(options, args) = parser.parse_args()
in_file=args[0]
in_file=sub(r"\.py","",in_file)
in_file=sub(r"/",".", in_file)
print in_file
from polybori.gbrefs import load_data
mydata=load_data(args[0])
import polybori.aes as aes
change_ordering(getattr(OrderCode, options.ordering))
I=mydata.ideal
if options.aes:
    I=aes.preprocess(I)
I=GPS_with_suggestions(I,deg_bound=options.deg_bound,over_deg_bound=options.over_deg,optLazy=options.lazy,optRedTail=options.red_tail)
#hard coded here

#if options.show:

#    I.toStdOut()
