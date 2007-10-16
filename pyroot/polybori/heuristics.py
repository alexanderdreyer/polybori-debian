from polybori.PyPolyBoRi import Polynomial
from nf import slimgb
def dense_system(I):
    I=(Polynomial(p) for p in I)
    I=(p for p in I if not p.isZero())
    for p in I:
        d=p.deg()
        if p.deg()==1:
            continue
        else:
            if len(p)>2**d+5:
                return True
    return False
def gauss_on_linear(I):
    I=(Polynomial(p) for p in I)
    linear=[]
    non_linear=[]
    for p in I:
        if p.isZero():
            continue
        if p.deg()<=1:
            linear.append(p)
        else:
            non_linear.append(p)
    if len(linear)==0:
        return non_linear
    linear=list(slimgb(linear).minimalizeAndTailReduce())
    return linear+non_linear