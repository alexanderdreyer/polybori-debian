from sys import stdout
holes = 12
pigeons = holes + 1

def coincidence(p,h):
    return p*holes+ h + 1 


from copy import copy
ideal=[]
holes_indices=range(holes)




clauses=[]

#a pigeon is not in two holes at the same time
for i in xrange(holes):
    for j in xrange(i+1,holes):
        if i==j:
            continue
        for p in xrange(pigeons):
            pass#clauses.append((-coincidence(h=j,p=p), -coincidence(h=i,p=p)))
            #ideal.append((coincidence(h=j,p=p)+1)*(coincidence(h=i,p=p)+1))

#only one pigeon fits in one hole
for h in xrange(holes):
    for i in xrange(pigeons):
        for j in xrange(i+1,pigeons):
            if i==j:
                continue
            
            clauses.append((-coincidence(p=i,h=h), -coincidence(p=j,h=h)))

for i in xrange(pigeons):
    l=[coincidence(p=i,h=h) for h in reversed(xrange(holes))]
    clauses.append(tuple(l))
print "p cnf", pigeons*holes, len(clauses)
for c in clauses:
# Copyright (c) 2005-2007 by The PolyBoRi Team
    print " ".join((str(i) for i in c))+" 0"
