# Copyright (c) 2005-2007 by The PolyBoRi Team

from sys import path
path.append("../../PyPolyBoRi")
from data import hole6
from nf import *
I=buchberger_C_based2(hole6.ideal)
