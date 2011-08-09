import pathadjuster
from polybori.blocks import declare_ring,Block
declare_ring([Block("x",1000)],globals())
p1=x(1)*x(2)+x(3)*x(4)+x(1)+x(2)*x(3)+1+x(5)*x(3)+x(6)+x(7)+x(3)*x(6)*x(7)+x(7)*\
  x(4)+x(1)*x(8)+x(8)+x(6)+x(6)*x(7)*x(8)*x(9)+x(1)*x(2)*x(3)
q1=x(1)*x(2)*x(3)*x(5)*x(6)+x(1)*x(9)*x(3)*x(8)*x(7)+x(3)*x(4)*x(5)*x(6)*x(7)+x(4)*x(3)*x(8)*x(9)+1
import interpolate
from polybori.gbcore import groebner_basis
from polybori.PyPolyBoRi import mapping,Monomial,Variable
from time import clock
p2=p1+x(1)*x(2)*x(3)*x(9)
p3=p1+1
p4=p1+sum([x(i) for i in xrange(1,10)])

q2=q1+x(1)*x(2)*x(3)*x(9)
q3=q1+1
q4=q1+sum([x(i) for i in xrange(1,10)])
q5=p1+q1
o1=sum([t for t in p1*q1 if not 1 in list(t)])+x(1)
o2=o1+x(1)*x(2)
o3=o1+x(1)*x(3)*x(4)*x(5)*x(6)*x(7)*x(8)*x(9)
o4=o1+x(1)*x(9)
o5=o1+x(1)*x(5)
from_mon_ind=reversed(range(1,10))
to_mon_ind=reversed(range(8,17))
from_mon=Monomial()
to_mon=Monomial()
for i in from_mon_ind:
    from_mon=Variable(i)*from_mon
for i in to_mon_ind:
    to_mon=to_mon*Variable(i)
t1=mapping(p1,from_mon,to_mon)
t2=mapping(q1,from_mon,to_mon)
t3=mapping(o1,from_mon,to_mon)
polys=[p1,p2,p3,p4,q1,q2,q3,q4,q5,o1,o2,o3,o4,o5,p1+t1,p1+t2,p1+t3,q1+t2,q2+t2,q3+t2,q4+t2,q5+t2,o1+t1]
for p in polys:
    print "-----"
    print "p:",p
    t1=clock()
    interpolate.lex_groebner_basis_for_polynomial_via_variety(p)
    t2=clock()
    print "interpolate gb",t2-t1
    t1=clock()
    groebner_basis([p])
    t2=clock()
    print "usual gb",t2-t1
