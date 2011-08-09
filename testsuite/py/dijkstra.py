# Copyright (c) 2005-2007 by The PolyBoRi Team


from polybori.PyPolyBoRi import *
from random import Random
import copy
import sys
from nf import *
import parse





def find_ways(nav, path):
    if nav.constant():
        if nav.terminalOne():
            yield path
    else:
        v=nav.value()
        #path=path+(v,)
        for p in find_ways(nav.thenBranch(), path+(v,)):
            yield p
        for p in find_ways(nav.elseBranch(), path):
            yield p
      



def all_vertices(nav,s=None):
    if s==None:
        s=set()
    if nav in s:
        #nav is in, so we assume everything under it also
        return s
    else:
        s.add(nav)
        if nav.constant():
            
            return s
        else:
            s=all_vertices(nav.thenBranch(),s)
            return all_vertices(nav.elseBranch(),s)



infinity=100000000#r.nVars()*2+10

#cheated maybe


def myweight(u,v,i):
    def index(v):
        if v.constant():
            return nVars()
        return v.value()
    return index(u)-index(v)-i

def dijkstra(start, aim, weight_fun, extended=False):
    def extract_min(Q):
        res=None
        weight=infinity
        for q in Q:
            if distances[q]<weight:
                weight=distances[q]
                res=q
        Q.remove(res)
        return res
    
    V=all_vertices(start)
    assert aim in V
    previous={}
    distances=dict(((v,infinity) for v in V))
    distances[start]=0
    S=set()
    Q= V#don't need V later, so I don't copy it
    
    while len(Q)>0:
        u=extract_min(Q)
        d=distances[u]
        S.add(u)
        if not u.constant():
            thenBranch=u.thenBranch()
            elseBranch=u.elseBranch()
            edges=[(thenBranch, weight_fun(u,thenBranch,1)),\
                (elseBranch,weight_fun(u,elseBranch,0))]
            for (e,w) in edges:
                if not extended:
                    if d+w<distances[e]:
                        distances[e]=d+w
                        previous[e]=u
                else:
                    if d+w<distances[e]:
                        distances[e]=d+w
                        previous[e]=set([u])
                    else:
                        if d+w==distances[e]:
                            previous[e].add(u)
                
                
    if extended:
        return previous
    l=[aim]
    while l[-1]!=start:
        l.append(previous[l[-1]])
        
    l.reverse()
    return l



    
# function Dijkstra(G, w, s)
#  2     for each vertex v in V[G]                        // Initializations
#  3           d[v] := infinity
#  4           previous[v] := undefined
#  5     d[s] := 0
#  6     S := empty set
#  7     Q := V[G]
#  8     while Q is not an empty set                      // The algorithm itself
#  9           u := Extract_Min(Q)
# 10           S := S union {u}
# 11           for each edge (u,v) outgoing from u
# 12                  if d[v] > d[u] + w(u,v)             // Relax (u,v)
# 13                        d[v] := d[u] + w(u,v)
# 14                        previous[v] := u
def mydeg(f):
    nav=f.navigation()
    #print one().nNode()
    #print len(one())
    rone=one().navigation()
    l=dijkstra(nav, rone , myweight)

    deg=0
    for i in xrange(len(l)):
        v=l[i]
        if v!=rone and v.thenBranch()==l[i+1]:
            #print "VAR: ",v.value()
            deg=deg+1
    #print "DEG: ", deg
    return deg
    
if __name__=='__main__':
    (r,p)=parse.translate_ideal(\
        "u*x+v*w+v*x+x*y+w*x+x*y*z+w*x*y+u*x*z;",\
        ["u", "v","w","x","y","z"])
    p=p[0]
    
    p.plot("tree.dot")
    nav=p.navigation()
    
    rone=one().navigation()
    l=dijkstra(nav, rone, myweight)
    deg=0
    for i in xrange(len(l)):
        v=l[i]
        if v!=rone and v.thenBranch()==l[i+1]:
            print "VAR: ",v.value()
            deg=deg+1
    print "DEG: ", deg
    mydeg(p)
        
    previous=dijkstra(nav, rone, myweight,True)
    cur=rone
    while cur in previous:
        p=previous[cur]
        cur_v=infinity
        bak=cur
        for c in p:
            if c.value()<cur_v:
                cur_v=c.value()
                cur=c
        if cur!=rone and cur.thenBranch()==bak:
            print "LEADVAR: ", cur.value()
