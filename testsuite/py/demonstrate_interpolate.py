# Copyright (c) 2005-2007 by The PolyBoRi Team
import sys
import pathadjuster
from polybori.PyPolyBoRi import *
from polybori.randompoly import gen_random_poly
from random import Random
from time import clock

from polybori.interpolate import *
if __name__=='__main__':
    nvariables=100
    r=Ring(nvariables)
    for number_of_points in (100,500,1000,2000,3000,4000,5000,10000):
        print "----------"
        print "number_of_points:",number_of_points
        print "generate points"
        points=gen_random_poly(number_of_points,nvariables,range(nvariables))
        print "points generated"
        bench_interpolate(nvariables,nvariables,points)
        vars_mon=Monomial()
        for i in reversed(range(nvariables)):
            vars_mon=vars_mon*Variable(i)
        print len(variety_lex_leading_terms(points,vars_mon)), "elements in groebner basis"
