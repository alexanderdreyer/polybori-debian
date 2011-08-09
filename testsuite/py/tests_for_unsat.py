# Copyright (c) 2005-2007 by The PolyBoRi Team

import unittest
from fpformat import fix
from sys import path
import pathadjuster
import polybori.nf as nf
nf.PROT=False
from polybori.nf import *
nf.PROT=False
from polybori.PyPolyBoRi import *
from time import clock, time
import StringIO
import sys
from polybori import gbrefs
from re import match
from polybori.gbrefs import my_import,load_data, clean_data, SINGLE,AUTO
times={}
import polybori.aes as aes_mod

from polybori.gbcore import groebner_basis, owns_one_constant

def add_unsat_test_case_intern(test_class, data_file_name, ordering="lp",name=None,blocks=AUTO,options=dict()):
    if not name:
           name=data_file_name.split(".")[-1]+"_"+ordering
           if match("block",ordering):
               name=name+"_"+gbrefs.reencode_blocks(blocks)
    else:
           name=name+"_"+ordering
           if match("block",ordering):
               name=name+"_"+gbrefs.reencode_blocks(blocks)
    def test_method(self):
        t=time()

        mydata=load_data(data_file_name)
        change_ordering(getattr(OrderCode, ordering))
        if match("block",ordering):
            for s in gbrefs.parse_blocks(blocks,mydata):
                append_ring_block(s)

        I=groebner_basis(mydata.ideal,**options)

        contains_one = owns_one_constant(I)
        

        del I
        clean_data(mydata)
        del mydata
 
        t2=time()
 
        sys.stderr.write(str(round(t2-t,2))+"s\n")

        times[name]=t2-t

        self.assert_(contains_one,"GB is not One, although ideal whole ring")

   
    test_method.__name__="test_"+name
    setattr(test_class,"test_"+name, test_method)

  

def add_sat_test_case_intern(test_class, data_file_name, ordering="lp",name=None,aes=False,blocks=AUTO,options=dict()):
    if not name:
        name=data_file_name.split(".")[-1]+"_"+ordering
        if match("block",ordering):
            name=name+"_"+gbrefs.reencode_blocks(blocks)
    else:
        name=name+"_"+ordering
        if match("block",ordering):
            name=name+"_"+gbrefs.reencode_blocks(blocks)
    def test_method(self):
        t=time()

        mydata=load_data(data_file_name)
        change_ordering(getattr(OrderCode, ordering))
        if match("block",ordering):
            for s in gbrefs.parse_blocks(blocks,mydata):
                append_ring_block(s)
        I=mydata.ideal

        options.update(dict(aes = aes, redsb = True))
        I=groebner_basis(I,**options)

        contains_one = owns_one_constant(I)

        t2=time()

        sys.stderr.write(str(round(t2-t,2))+"s\n")
        #times[data_file_name+"-"+ordering]=t2-t
        times[name]=t2-t
        #if match("block",ordering):
        #    
        #else:
        #    times[data_file_name+"-"+ordering]=t2-t
        stream_out=StringIO.StringIO()
        
        for p in I:
            stream_out.write(p)
            stream_out.write("\n")
        
        res_new=stream_out.getvalue()

        res_ref=gbrefs.load_ref(data_file_name,ordering,blocks)

        try:
          del p
        except:
          pass
        del I

        clean_data(mydata)
        del mydata
        self.assert_(not contains_one,"GB is One, although ideal not whole ring")
        res_new=res_new.replace(" ","")
        self.assertEqual(res_new,res_ref)


        
    test_method.__name__="test_"+name
    setattr(test_class,"test_"+name, test_method)

# Adding test with fixed options and heuristic to respective test suites
def add_test_case(add_test_func, test_class, data_file_name,
                  options = dict(), **opts):

    heuristic_test_class = globals()["Heuristic" + test_class.__name__]
    add_test_func(heuristic_test_class, data_file_name,
                  options = dict(heuristic = True), **opts)

    options.update(dict(heuristic = False))
    add_test_func(test_class, data_file_name, options = options, **opts)
    

def add_sat_test_case(test_class, data_file_name, **opts):

    add_test_case(add_sat_test_case_intern, test_class, data_file_name, **opts)

def add_unsat_test_case(test_class, data_file_name, **opts):

    add_test_case(add_unsat_test_case_intern, test_class,data_file_name,**opts)


class SatTestCase(unittest.TestCase):
    pass
class UnSatTestCase(unittest.TestCase):
    pass
class SatTestCaseWeekend(unittest.TestCase):
    pass
class UnSatTestCaseWeekend(unittest.TestCase):
    pass

class SymbolicModelCheckingTestCase(unittest.TestCase):
    pass
class HeuristicSymbolicModelCheckingTestCase(unittest.TestCase):
    pass
class CryptoTestCase(unittest.TestCase):
    pass

class CryptoTestCaseWeekend(unittest.TestCase):
    pass

class QuickTestCase(unittest.TestCase):
    pass


# Heuristic variants
class HeuristicSatTestCase(unittest.TestCase):
    pass
class HeuristicUnSatTestCase(unittest.TestCase):
    pass
class HeuristicSatTestCaseWeekend(unittest.TestCase):
    pass
class HeuristicUnSatTestCaseWeekend(unittest.TestCase):
    pass


class HeuristicCryptoTestCase(unittest.TestCase):
    pass

class HeuristicCryptoTestCaseWeekend(unittest.TestCase):
    pass

class HeuristicQuickTestCase(unittest.TestCase):
    pass

for i in xrange(1,30):
    add_sat_test_case(SatTestCase,"uf20.uf20_"+str(i))
    add_sat_test_case(SatTestCase,"uf20.uf20_"+str(i), ordering="dlex")
    add_sat_test_case(SatTestCase,"uf20.uf20_"+str(i),ordering="dp_asc")
add_sat_test_case(QuickTestCase,"uf20.uf20_1", ordering="block_dlex",blocks="5,10,15")
for i in xrange(1,11):
    add_sat_test_case(QuickTestCase,"uf20.uf20_"+str(i))
    add_sat_test_case(QuickTestCase,"uf20.uf20_"+str(i), ordering="dlex")
    add_sat_test_case(QuickTestCase,"uf20.uf20_"+str(i),ordering="dp_asc")
add_sat_test_case(QuickTestCase,"bug1")

add_sat_test_case(SatTestCase,"bug1")
for i in xrange(1,15):
    add_unsat_test_case(UnSatTestCase,"uuf50.uuf50_"+str(i))
    add_unsat_test_case(UnSatTestCase,"uuf50.uuf50_"+str(i),ordering="dlex")
    add_unsat_test_case(UnSatTestCase,"uuf50.uuf50_"+str(i),ordering="dp_asc")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2", ordering="dp_asc")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2", ordering="dlex")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2",ordering="block_dp_asc",blocks="25")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2",ordering="block_dp_asc",blocks="10,20,30,40")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2",ordering="block_dlex",blocks="25")
add_unsat_test_case(QuickTestCase,"uuf50.uuf50_2",ordering="block_dlex",blocks="10,20,30,40")

add_sat_test_case(QuickTestCase,"flat30_60.flat30_77")
add_sat_test_case(QuickTestCase,"flat30_60.flat30_43")
add_sat_test_case(QuickTestCase,"flat30_60.flat30_83")

def life(i):
    return "life.life" +str(i)

lifeopts = dict(interpolation_gb=True)
for i in xrange(10,12):
    add_sat_test_case(QuickTestCase,life(i), ordering="dp_asc")
    add_sat_test_case(QuickTestCase,life(i), options = lifeopts)
for i in xrange(10,16):
    add_sat_test_case(SatTestCase,life(i), ordering="dp_asc")
for i in xrange(10,16):
    add_sat_test_case(SatTestCase,life(i), options = lifeopts)


def eco(i):
    return "eco.eco"+str(i)
for i in xrange(20,46):
    add_sat_test_case(SatTestCase,eco(i), ordering="dp_asc")
for i in xrange(20,42):
    add_sat_test_case(SatTestCase,eco(i))
for i in xrange(20,51):
    add_sat_test_case(SatTestCaseWeekend,eco(i), ordering="dp_asc")
for i in xrange(20,46):
    add_sat_test_case(SatTestCaseWeekend,eco(i))
add_sat_test_case(SatTestCaseWeekend,life(16), options = lifeopts)
add_sat_test_case(SatTestCaseWeekend,life(16), ordering="dp_asc")
add_sat_test_case(QuickTestCase,"blocksworld.anomaly", name="bw_anomaly")
add_sat_test_case(QuickTestCase,"blocksworld.medium", name="bw_medium")
add_sat_test_case(SatTestCase,"blocksworld.bw_large_a")
for i in xrange(1,1001):
    #name="uf20_"+str(i)
    #add_sat_test_case(SatTestCaseWeekend,"uf20_0"+str(i))
    add_sat_test_case(SatTestCaseWeekend,"uf20.uf20_"+str(i))
    add_sat_test_case(SatTestCaseWeekend,"uf20.uf20_"+str(i),ordering="dp_asc")
    add_sat_test_case(SatTestCaseWeekend,"uf20.uf20_"+str(i), ordering="dlex")
    #add_sat_test_case(SatTestCaseWeekend,"uf20.uf20_"+str(i), ordering="block_dlex",block="5,10")
    #add_sat_test_case(SatTestCaseWeekend,"uf20.uf20_"+str(i), ordering="block_dp_asc",blocks="5,10")
for i in xrange(1,101):
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf50.uuf50_"+str(i))
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf50.uuf50_"+str(i), ordering="dp_asc")
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf50.uuf50_"+str(i),ordering="dlex")
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf50.uuf50_"+str(i),ordering="block_dlex",blocks="20,40")
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf50.uuf50_"+str(i),ordering="block_dp_asc",blocks="20,40")
for i in range(1,6)+[8]:
    add_unsat_test_case(UnSatTestCaseWeekend,"uuf75.uuf75_"+str(i))

add_unsat_test_case(UnSatTestCaseWeekend,"uuf75.uuf75_8", ordering="dlex")
add_unsat_test_case(UnSatTestCaseWeekend,"uuf75.uuf75_8",ordering="dp_asc")
add_unsat_test_case(UnSatTestCaseWeekend,"uuf75.uuf75_8", ordering="block_dlex",blocks="25,50")
add_unsat_test_case(UnSatTestCaseWeekend,"uuf75.uuf75_8",ordering="block_dp_asc",blocks="25,50")

for i in [57]+range(59,60)+range(77,80):
    add_sat_test_case(SatTestCase,"flat30_60.flat30_"+str(i))
for i in range(18,26)+range(77,80)+range(57,60):
    add_sat_test_case(SatTestCaseWeekend,"flat30_60.flat30_"+str(i))

for i in range(3,8)+[10]:
    add_sat_test_case(CryptoTestCaseWeekend,"aes.aes_"+str(i)+"_1_2_4",aes=True)
    add_sat_test_case(CryptoTestCase,"aes.aes_"+str(i)+"_1_2_4",aes=True)
add_sat_test_case(CryptoTestCase,"aes.aes_10_1_2_4_pp")
add_sat_test_case(CryptoTestCaseWeekend,"aes.aes_10_1_2_4_pp")
for i in [4,6,10]:
    add_sat_test_case(CryptoTestCaseWeekend,"aes.aes_"+str(i)+"_1_1_4",aes=True)
    add_sat_test_case(CryptoTestCase,"aes.aes_"+str(i)+"_1_1_4",aes=True)
    add_sat_test_case(CryptoTestCaseWeekend,"aes.aes_"+str(i)+"_1_1_4",aes=True,ordering="dp_asc")
    add_sat_test_case(CryptoTestCase,"aes.aes_"+str(i)+"_1_1_4",aes=True,ordering="dp_asc")
for i in [2]:
    add_sat_test_case(CryptoTestCaseWeekend,"aes.aes_"+str(i)+"_1_1_8",aes=True)
    add_sat_test_case(CryptoTestCase,"aes.aes_"+str(i)+"_1_1_8",aes=True)
faugere_options=dict(faugere=True,red_tail=False,ll=True,selection_size=100000)

for i in [10,15]:

    add_sat_test_case(CryptoTestCaseWeekend,"hfe"+str(i))
    add_sat_test_case(CryptoTestCase,"hfe"+str(i))
    add_sat_test_case(CryptoTestCaseWeekend,"hfe"+str(i), ordering="dp_asc")
    add_sat_test_case(CryptoTestCase,"hfe"+str(i), ordering="dp_asc")
    la_name="hfe"+str(i)+"_la"
    add_sat_test_case(CryptoTestCaseWeekend,"hfe"+str(i),name=la_name,options=faugere_options)
    add_sat_test_case(CryptoTestCase,"hfe"+str(i),name=la_name,options=faugere_options)
    add_sat_test_case(CryptoTestCaseWeekend,"hfe"+str(i), ordering="dp_asc",name=la_name,options=faugere_options)
    add_sat_test_case(CryptoTestCase,"hfe"+str(i), ordering="dp_asc",name=la_name,options=faugere_options)

for i in ["25_96","30_96"]:
    la_name="hfe"+str(i)+"_la"
    add_sat_test_case(CryptoTestCaseWeekend,"hfe.hfe"+str(i), ordering="dp_asc",name=la_name,options=faugere_options)
    add_sat_test_case(CryptoTestCase,"hfe.hfe"+str(i), ordering="dp_asc",name=la_name,options=faugere_options)
for i in ["35_96"]:
    la_name="hfe"+str(i)+"_la"
    add_sat_test_case(CryptoTestCaseWeekend,"hfe.hfe"+str(i), ordering="dp_asc",name=la_name,options=faugere_options)
for i in range(1,4):
    mod=str(i)+"_"+str(i)
    add_sat_test_case(CryptoTestCaseWeekend,"ctc.ctc_"+mod,aes=True)
    add_sat_test_case(CryptoTestCase,"ctc.ctc_"+mod,aes=True)
    add_sat_test_case(CryptoTestCaseWeekend,"ctc.ctc_"+mod, aes=True,ordering="dp_asc")
    add_sat_test_case(CryptoTestCase,"ctc.ctc_"+mod, aes=True,ordering="dp_asc")

for i in [4]:
    mod=str(i)+"_"+str(i)
    add_sat_test_case(CryptoTestCaseWeekend,"ctc.ctc_"+mod,aes=True)
for i in [5,6,7]:
    i=str(i)
    add_sat_test_case(CryptoTestCase,"ctcmultiples3.ctc_Nr3_B"+i+"_n20joined", ordering="block_dlex",options=dict(ll=True))
    add_sat_test_case(CryptoTestCase,"ctcmultiples3.ctc_Nr3_B"+i+"_n20joined", ordering="block_dp_asc")
    #add_sat_test_case(CryptoTestCase,"ctcmultiples3.ctc_Nr3_B"+i+"_n20joined", ordering="dlex",options=dict(ll=True))
    add_sat_test_case(CryptoTestCase,"ctcmultiples3.ctc_Nr3_B"+i+"_n20joined", ordering="dp_asc",options=dict(linear_algebra_in_last_block=False))
#for i in [5]:
    #i=str(i)
    #add_sat_test_case(CryptoTestCase,"ctcmultiples3.tc_Nr3_B"+i+"_n20joined", ordering="dlex",options=faugere_options)
add_sat_test_case(CryptoTestCase,"ctcmultiples3.ctc_Nr3_B"+i+"_n20joined",     
    ordering="dp_asc",name="ctc_3_"+i+"_20joined_la",options=faugere_options)
for i in [5,8,10,15]:
  mod=str(i)+"_3"
  add_sat_test_case(CryptoTestCaseWeekend,"ctc.ctc_"+mod,aes=True)
  add_sat_test_case(CryptoTestCase,"ctc.ctc_"+mod,aes=True)
 
for i in [5,6,8]:
      name="et.easytop.mult"+str(i)+"x"+str(i)+"mit"
      add_unsat_test_case(QuickTestCase,name)
      add_unsat_test_case(UnSatTestCase,name)



for i in [10]:
      name="et.easytop.mult"+str(i)+"x"+str(i)+"mit"
      add_unsat_test_case(UnSatTestCase,name)


symbolics=[
'S1196backward',
'S1196forward',
'S1238forward',
'S13207forward',
'S13207forward2',
'S13207resetforward',
'S13207zforward',
'S13207zrforward',
'S1423forward',
'S1488forward',
'S1494forward',
'S15850forward',
'S208forward',
'S208mforward',
'S27forward',
'S298forward',
'S298mforward',
'S298p10forward',
'S298p10rforward',
'S298p1forward',
'S298p4forward',
'S298p4rforward',
'S3420mforward',
'S344forward',
'S349forward',
'S35932forward',
'S382forward',
'S38417forward',
'S38584forward',
'S386forward',
'S420forward',
'S444forward',
'S510forward',
'S526forward',
'S526nforward',
'S5378forward',
'S641forward',
'S713forward',
'S820forward',
'S832forward',
'S838forward',
'S9234forward',
'S9234rforward',
'S953forward',
]
for s in symbolics:
    add_sat_test_case(SymbolicModelCheckingTestCase,"et.symbolic."+s)

#for i in [12]:
#      name="et.easytop.mult"+str(i)+"x"+str(i)+"mit"
#      add_unsat_test_case(UnSatTestCaseWeekend,name)
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
