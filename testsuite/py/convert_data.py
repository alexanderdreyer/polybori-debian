# Copyright (c) 2005-2007 by The PolyBoRi Team

import sys
ord="dlex"
data=eval(open("gb_dict4"+ord).read())
data[0]=[]
line_length=7
print """// The content of this file is intellectual property of Michael Brickenstein
// Note, that choosing GPL3+ we made a clear statement against software
// patents.
// The method using this tables is actually described in 
// http://arxiv.org/abs/0801.1177 """

print "#include \""+ord+"4data.h"+"\""
print "BEGIN_NAMESPACE_PBORIGB"
max_index=max(data)
for k in data:
    dk=data[k]
    assert len(dk)<=6
    data[k]=dk+(line_length-len(dk))*[0]
print "const unsigned short "+ord+"4var_data[]["+ str(line_length)+"]={"
for k in xrange(max_index+1):
    sys.stdout.write("    {")
    sys.stdout.write(", ".join([str(i) for i in data[k]]))
    sys.stdout.write("},\n")
print "\n};"
print "END_NAMESPACE_PBORIGB"
