# Copyright (c) 2005-2007 by The PolyBoRi Team
import unittest
from fpformat import fix
from sys import path
if __name__=="__main__":
    import pathadjuster
import nf
from ll import llredsb_Cudd_style,ll_encode
nf.PROT=False
from nf import *
nf.PROT=False
from polybori.PyPolyBoRi import *
from polybori.check_claims import proofll,to_if_then
from time import clock, time
import StringIO
import sys
import gbrefs
from re import match
from gbrefs import my_import,load_data, clean_data, SINGLE
times={}
import aes as aes_mod
def redsb_suffix(redsb):
    if redsb:
        return "redsb"
    else:
        return "noredsb"
def add_test_case(data_file_name,name=None,redsb=True):
    test_class=HighLevelTestCase
    def test_method(self):
        
        
        mydata=load_data(data_file_name)
        t=time()
        if redsb:
            reductors=BooleSet(llredsb_Cudd_style(mydata.ideal).set())
        else:
            reductors=ll_encode(mydata.ideal)
        #print reductors
        
        for c in mydata.claims:
           c=to_if_then(c)
           self.assertEquals(proofll(c,reductors,redsb=redsb,prot=False),c.supposedToBeValid)
           
        t2=time()
 
        sys.stderr.write(str(round(t2-t,2))+"s\n")
        times[data_file_name+"-"+redsb_suffix(redsb)]=t2-t


    if not name:
        name=data_file_name.split(".")[-1]+"_"+redsb_suffix(redsb)
    else:
        name=name+"_"+redsb_suffix(redsb)

    test_method.__name__="test_"+name
    setattr(test_class,"test_"+name, test_method)

class HighLevelTestCase(unittest.TestCase):
    pass


for redsb in (True,False):
    add_test_case("highlevel.adderpluslogic",redsb=redsb)
    add_test_case("highlevel.macros",redsb=redsb)
    add_test_case("highlevel.commutative",redsb=redsb)
    add_test_case("highlevel.xor",redsb=redsb)
    #add_test_case("highlevel.ite",redsb=redsb)
    #add_test_case("highlevel.iteneu",redsb=redsb)
class mymain(unittest.main):
  def runTests(self):
          if self.testRunner is None:
              self.testRunner = unittest.TextTestRunner(verbosity=self.verbosity)
          result = self.testRunner.run(self.test)
          for f in sorted(times):
              print f, max(25-len(f),0)*" ", ":", fix(times[f],2)
 
          sys.exit(not result.wasSuccessful())
  
if __name__=='__main__':
    
    mymain()
    #for f in times:

    #    print f, (25-len(f))*" ", ":", times[f]
