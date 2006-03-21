#$Id$
opts = Options('custom.py')



USER_CPPPATH=ARGUMENTS.get("CPPPATH","").split(":")
USER_LIBPATH=ARGUMENTS.get("LIBPATH","").split(":")
try:
    import custom
    if "LIBPATH" in dir(custom):
        USER_LIBPATH=custom.LIBPATH+USER_LIBPATH
    if "CPPPATH" in dir(custom):
        USER_CPPPATH=custom.CPPPATH+USER_CPPPATH
except:
    pass


try:
	import SCons.Tool.applelink as applelink
except:
	pass
import os
env=Environment(options=opts)
if (env['PLATFORM']=="darwin"):
    applelink.generate(env)


cudd_libs=Split("obj cudd dddmp mtr st util epd")



HAVE_PYTHON_EXTENSION=1

class PythonConfig(object):
    def __init__(self, version="2.4", prefix="/usr", libdir=None, incdir=None, libname=None):
        self.version=version
        if libdir:
            self.libdir=libdir
        else:
            self.libdir=prefix+"/lib"
        self.prefix=prefix
        if libname:
            self.libname=libname
        else:
            self.libname="python"+self.version
        if incdir:
            self.incdir=incdir
        else:
            self.incdir=self.prefix+"/include/python"+self.version

PYTHONSEARCH=[\
    PythonConfig(version="2.4", prefix="/sw"),\
    PythonConfig(version="2.4"),\
    PythonConfig(version="2.3"),]

conf = Configure(env)
env.Append(CPPPATH=USER_CPPPATH)
env.Append(LIBPATH=USER_LIBPATH)
env.Append(CPPPATH=["./polybori/include"])
env.Append(CPPPATH=["./Cudd/include"])
env.Append(LIBPATH=["polybori"])
env['ENV']['HOME']=os.environ["HOME"]
if env['PLATFORM']=="darwin":
        env.Append(LIBPATH="/sw/lib")
        env.Append(CPPPATH="/sw/include")
#workaround for linux
#env.Append(LIBPATH=".")

env.Append(LIBS=["m"])

env.Append(CCFLAGS=Split("-O3 -ftemplate-depth-100 -ansi"))


for l in cudd_libs:
    env.Append(LIBPATH=["./Cudd/"+l])
    env.Append(LIBS=[l])
    

HAVE_PYTHON_EXTENSION=0
for c in PYTHONSEARCH:
    if conf.CheckCHeader(c.incdir+"/Python.h"):
        PYTHON_CONFIG=c
        print "Python.h found in " + c.incdir
        env.Append(CPPPATH=[c.incdir])
        break

if not conf.CheckCXXHeader('boost/python.hpp'):
    print 'Warning Boost/python must be installed for python support'
else:
    HAVE_PYTHON_EXTENSION=1
    

env = conf.Finish()


pb_src=Split("BoolePolyRing.cc BoolePolynomial.cc BooleVariable.cc CErrorInfo.cc PBoRiError.cc")
pb_src=["./polybori/src/"+ source for source in pb_src]
l=env.StaticLibrary("polybori/polybori", pb_src)
print "l:", l, dir(l)
#sometimes l seems to be boxed by a list
if isinstance(l,list):
    l=l[0]
Default(l)

tests=["errorcodes","testring", "boolevars", "boolepoly"]

for t in tests:
    Default(env.Program("testsuite/"+t, ["testsuite/src/" + t +".cc"] +[l]))

if HAVE_PYTHON_EXTENSION:
 
    
    if env['PLATFORM']=="darwin":
        env.LoadableModule('PyPolyBori/PyPolyBoRi', ["PyPolyBoRi/main_wrapper.cc"], LINKFLAGS="-bundle_loader /sw/bin/python", LIBS=env['LIBS']+['boost_python',l],LDMODULESUFFIX=".so")
    else:
        print "l:", l
        env.SharedLibrary('PyPolyBoRi/PyPolyBoRi', ["PyPolyBoRi/main_wrapper.cc"], LDMODULESUFFIX=".so",SHLIBPREFIX="", LIBS=env['LIBS']+['boost_python',"polybori"])
            #LIBS=env['LIBS']+['boost_python',l])#,LDMODULESUFFIX=".so",\
            #SHLIBPREFIX="")
     
