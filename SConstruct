# Emacs edit mode for this file is -*- python -*-

# Backward compatibility
if not 'Variables' in globals():
    Variables = Options
    BoolVariable = BoolOption

# Some hard-coded settings
pboriname = 'PolyBoRi'
try:
    versionnumber = open('versionnumber', 'r').read().rstrip() + "-0"
    (pboriversion, pborirelease) = versionnumber.split('-')[:2]
except:
    pboriversion = "0.0"
    pborirelease = "0"


debname = "polybori-" + pboriversion + '.' + pborirelease

import tarfile

import sys
from os import sep, path
from glob import glob

m4ri=Split("""grayflex.c permutation.c packedmatrix.c strassen.c
misc.c brilliantrussian.c trsm.c mmc.c echelonform.c pls.c pls_mmpf.c""")
m4ri=[path.join("M4RI/m4ri", m) for m in m4ri]

m4ri_inc = 'M4RI'


def pathsplit(p, rest=[]):
    (h,t) = os.path.split(p)
    if len(h) < 1: return [t]+rest
    if len(t) < 1: return [h]+rest
    return pathsplit(h,[t]+rest)

def commonpath(l1, l2, common=[]):
    if len(l1) < 1: return (common, l1, l2)
    if len(l2) < 1: return (common, l1, l2)
    if l1[0] != l2[0]: return (common, l1, l2)
    return commonpath(l1[1:], l2[1:], common+[l1[0]])

def relpath(p1, p2):
    (common,l1,l2) = commonpath(pathsplit(p1), pathsplit(p2))
    p = []
    if len(l1) > 0:
        p = [ ('..' + sep) * len(l1) ]
    p = p + l2

    if len(p) == 0:
        return ''
    return os.path.join( *p )

def env_relpath(env, path, versus):
    return relpath(env.subst(path), env.subst(versus))

Environment.relpath = env_relpath

def preprocessed_substitute(target, source, env):
    def preprocess_at(page):
        import re
        p = re.compile('@([^@\n]*) @', re.VERBOSE)
        return p.sub(r'$\1', page)
        
    substitute_install(target, source, env, preprocess=preprocess_at)
    

# Fix some paths and names
class PathJoiner(object):
    """Generates a valid path from lists of strings, with custom prefix (set at
    initialization). It also changes '/' to correct path separator.""" 
    def __init__(self, *parent):
        self.parent = path.join(*self.validpath(*parent))
    def __call__(self, *args):
        return path.join(self.parent, *self.validpath(*args))
    def validpath(self, *args):
        return [str(elt).replace('/', sep) for elt in args]

[TestsPath, PyPBPath, CuddPath, GBPath, PBPath, DocPath, BuildPath] = \
    [ PathJoiner(fdir)
      for fdir in Split("""testsuite PyPolyBoRi Cudd groebner libpolybori doc
 build""") ]

M4RIPath = PathJoiner('M4RI')
M4RIInc = PathJoiner(M4RIPath('m4ri'))

DataPath = PathJoiner(TestsPath('py/data'))

DebPath = PathJoiner('pkgs/debian')
DebInstPath = PathJoiner('debian')

RPMPath = PathJoiner('pkgs/rpm')
SpecsPath = PathJoiner(RPMPath('SPECS'))

   
# Split lists separated by colons and whitespaces
def SplitColonSep(arg):
    result = []
    for element in Split(arg):
        result += element.split(':')
    return result

def shell_output(*args):
    from subprocess import Popen, PIPE, STDOUT
    process = Popen(args, stdin=None, stdout=PIPE, stderr=STDOUT, env=os.environ)
    
    return process.communicate()[0].rstrip()



pyroot="pyroot/"
ipbroot = 'ipbori'
guiroot = 'gui'
cudd_name = 'pboriCudd'

[PyRootPath, IPBPath, GUIPath] = [PathJoiner(fdir) for fdir in [pyroot, ipbroot,
                                                                guiroot] ]
try:
	import SCons.Tool.applelink as applelink
except:
	pass
import os

def FinalizePermissions(targets, perm=None):
    def isdll(path):
        return 'dll' in os.path.basename(path).split(os.path.extsep)[1:]
    
    for src in targets:
        path = str(src)
        if not os.path.islink(path):
            if perm is None:
                if os.path.isdir(path):
                    perm = 040755
                else:
                    if os.access(path, os.X_OK) or isdll(path):
                        perm = 0755
                    else:
                        perm = 0644
            env.AddPostAction(src, Chmod(path, perm))
    return targets

def FinalizeExecs(targets):
    return FinalizePermissions(targets, 0755)

def FinalizeNonExecs(targets):
    return FinalizePermissions(targets, 0644)


distribute = 'distribute' in COMMAND_LINE_TARGETS

prepare_deb = 'prepare-debian' in COMMAND_LINE_TARGETS
generate_deb = 'deb' in COMMAND_LINE_TARGETS
deb_generation = prepare_deb or generate_deb
generate_rpm = 'rpm' in COMMAND_LINE_TARGETS
generate_srpm = 'srpm' in COMMAND_LINE_TARGETS
prepare_rpm = 'prepare-rpm' in COMMAND_LINE_TARGETS
rpm_generation = generate_rpm or generate_srpm or prepare_rpm


# Undocumented switches (for debugging foreign platforms)
defaultopts = Variables() # Works only from command line
defaultopts.Add('PLATFORM', "Manually set another platform (unusual)")
defaultopts.Add('TOOLS', "Manually set toolchain (unusual)", converter = Split)   

defaultenv = Environment(ENV = os.environ, options=defaultopts)

# See also: http://trac.sagemath.org/sage_trac/ticket/9872 and #6437
def detect_linker(env):
    import re
    args = env.subst('$CC').split() + ['-Wl,-v']
    if re.search("Binutils|GNU",  shell_output(*args)):
        return "gnu"

    # Non-gnu linker or linux (could be Sun or Intel linker) will return 'posix'.
    return env['PLATFORM']

def detect_compiler(env):
    import re
    args = env.subst('$CC').split() + ['-v']
    if re.search("gcc version",  shell_output(*args)):
        return "gnu"

    # Non-gnu linker or linux (could be Sun or Intel linker) will return 'posix'.
    return env['PLATFORM']

# for gentoo-prefix on OS X
def _fix_dynlib_flags(env):

    if env['PLATFORM']=="darwin":
        return "-Wl,-flat_namespace"
    return ''


def _sonameprefix(env):
    linker = detect_linker(env)
    #print linker, "linker detected!"
    if env['PLATFORM']=="darwin":
        return "-install_name @loader_path/"

    elif (env['PLATFORM'] == "sunos") and (linker == 'sunos'):
        return '-Wl,-h'

    else:
        return '-Wl,-soname,'

# dynamic module flags
def _dynmodule_flags(env):
    """Creates special flags for dynamic libraries, in particular on darwin."""
    if env['PLATFORM'] == "darwin":
        return "-Wl,-undefined -Wl,dynamic_lookup"
    else:
        return ""

def _moduleflags(env):
    if env['PLATFORM']=="darwin":
        python_absolute = shell_output("which", env["PYTHON"])
        return ["-fvisibility=hidden", "-bundle_loader", python_absolute]

    return []

def _relative_rpath(target, env):
    if not target or env['PLATFORM'] in ["darwin", "cygwin"]:
        return ''

    targetdir = os.path.dirname(env.subst(str(target)))
    libdir = BuildPath(env['DEVEL_LIB_PREFIX'].lstrip(sep))
    relative_path = '\\$$ORIGIN/' + env.relpath(targetdir, libdir)
    return [env['RPATHPREFIX'] + relative_path + env['RPATHSUFFIX'],
            '-z', 'origin']

def scons_version():
    import SCons
    return SCons.__version__.split('.')

def oldstyle_flags():
    return scons_version() < ['0','97','0']


class ExtendedVariables:
    def __init__(self, vars, defaults):
        from weakref import proxy
        vars.AddWithDefaults = self
        self.vars = proxy(vars)
        self.defaults = defaults
    def __call__(self, varname, *args, **kwds):   
        self.vars.Add(varname, *args, **kwds)
        self.vars.Add('DEFAULT_' + varname, 
                      "defaults appended to " + repr(varname),
                      self.defaults[varname])

pbori_cache_macros=["PBORI_UNIQUE_SLOTS","PBORI_CACHE_SLOTS","PBORI_MAX_MEMORY"]

def setup_env(defaultenv):

    opts = Variables('custom.py')

    ExtendedVariables(opts, defaultenv)
    
    # Define option handle, may be changed from command line or custom.py
    opts.Add('CXX', 'C++ Compiler (inherited from SCons)',
             defaultenv['CXX'])
    opts.Add('CC', 'C Compiler (inherited from SCons)',
             defaultenv['CC'])

    opts.Add('SHCXX', 
             'C++ Compiler (preparing shared libraries; inherited from SCons)',
             defaultenv['SHCXX'])
    opts.Add('SHCC', 
             'C Compiler (preparing shared libraries; inherited from SCons)',
             defaultenv['SHCC'])

    opts.Add('PYTHON', 'Python executable', "python$PROGSUFFIX")

    opts.Add('LIBPATH', 'list of library paths (colon or whitespace separated)',
             defaultenv.get('LIBPATH', []), converter = SplitColonSep)
    opts.Add('CPPPATH', 'list of include paths (colon or whitespace separated)',
             defaultenv.get('CPPPATH', []), converter = SplitColonSep)

    opts.Add('TEST_CPPPATH', 'list of include paths for tests (colon or whitespace separated)',
             None, converter = SplitColonSep)

    opts.Add('CPPDEFINES', 'list of preprocessor defines (whitespace separated)',
             defaultenv.get('CPPDEFINES',[]) + ['PBORI_NDEBUG'], converter = Split)


    if oldstyle_flags() :
        defaultenv.Append(CCFLAGS=["-std=c99", "$M4RI_CFLAGS"])
        defaultenv.Append(CXXFLAGS=["-std=c++98", "$M4RI_CFLAGS", 
                                    "-ftemplate-depth-100"])
        for (var, help, default) in [('CCFLAGS', "C compiler flags", ["-O3"]),
                                     ('CXXFLAGS', "C++ compiler flags", ["-O3"])]:
            opts.AddWithDefaults(var, help, default, converter=Split)

    else:
        defaultenv.Append(CCFLAGS=["$M4RI_CFLAGS"])
        defaultenv.Append(CFLAGS=["-std=c99"])
        defaultenv.Append(CXXFLAGS=["-std=c++98", "-ftemplate-depth-100"])

        for (var, help, default) in [('CCFLAGS', "C/C++ compiler flags", ["-O3"]),
                                     ('CFLAGS', "C compiler flags", []),
                                     ('CXXFLAGS', "C++ compiler flags", [])]:
            opts.AddWithDefaults(var, help, default, converter=Split)


    opts.Add('M4RI_CFLAGS', "C compiler flags for M4RI", converter = Split) 


    defaultenv.Append(LINKFLAGS=['${_fix_dynlib_flags(__env__)}', 
                                 '${_relative_rpath(TARGET, __env__)}'])
    defaultenv.Append(SHLINKFLAGS=['$SONAMEFLAGS'])
    defaultenv.Append(LDMODULEFLAGS=['${_moduleflags(__env__)}'])
    defaultenv.Append(LIBS=[])

    opts.AddWithDefaults('LINKFLAGS', 
                         "Custom linker flags (e.g. '-s' for stripping)", [],
                         converter=Split)

    opts.AddWithDefaults('SHLINKFLAGS', 'Shared libraries link flags.', [],
                         converter=Split)

    opts.AddWithDefaults('LDMODULEFLAGS',
                         'Dynamic module compile flags', [], converter=Split)

    for flag in Split("""SHCCFLAGS SHCFLAGS SHCXXFLAGS FRAMEWORKS"""):
        if defaultenv.has_key(flag):
            opts.AddWithDefaults(flag, "flags inherited from SCons",
                                 [], converter=Split)
        else:
            print "Flags", flag, "not in default environment!"


    opts.AddWithDefaults('LIBS', 'custom libraries needed for build', [],
                         converter = Split)
    opts.Add('GD_LIBS', 'Library gb and its dependencies (if needed)', 
             ["gd"], converter = Split)

    opts.Add('PREFIX', 'installation prefix directory', '/usr/local')
    opts.Add('EPREFIX','executables installation prefix directory', '$PREFIX/bin')

    opts.Add('INSTALLDIR', 'end user installation directory',
             '$PREFIX/share/polybori')
    opts.Add('DOCDIR', 'documentation installation directory',
             '$INSTALLDIR/doc')
    opts.Add('MANDIR', 'Man-pages installation directory',
             '$PREFIX/man')
    opts.Add('PYINSTALLPREFIX',
             'python modules directory (default is built-in site)', '$PYTHONSITE')

    opts.Add('DEVEL_PREFIX',
             'development version installation directory','$PREFIX' )
    opts.Add('DEVEL_INCLUDE_PREFIX',
             'development version header installation directory',
             '$DEVEL_PREFIX/include' )
    opts.Add('DEVEL_LIB_PREFIX',
             'development version library installation directory',
             '$DEVEL_PREFIX/lib' )

    opts.Add(BoolVariable('M4RI_RPM',
                          'Assume rpm knows about M4RI', False))   

    opts.Add(BoolVariable('HAVE_DOXYGEN',
                        'Generate doxygen-based documentation, if available', True))
    opts.Add(BoolVariable('HAVE_PYTHON_EXTENSION',
                        'Build python extension, if possible', True))

    opts.Add('BOOST_PYTHON',
             'Name of Boost-python library to link with', 'boost_python')

    opts.Add('BOOST_TEST',
             'Name of Boost unit test framework library to link with',
             'boost_unit_test_framework')


    opts.Add(BoolVariable('RELATIVE_SYMLINK',
                          'Use relative symbolic links on install', True))

    opts.Add(BoolVariable('HAVE_L2H', 'Switch latex2html on/off (deprecated)', 
                          False))
    opts.Add(BoolVariable('HAVE_HEVEA', 'Switch hevea on/off (deprecated)', False))
    opts.Add(BoolVariable('HAVE_TEX4HT', 'Switch tex4ht on/off', True))


    opts.Add(BoolVariable('HAVE_PYDOC', 'Switch python doc generation on/off',
                          True))
    opts.Add(BoolVariable('EXTERNAL_PYTHON_EXTENSION', 'External python interface',
                          False))

    opts.Add(BoolVariable('USE_TIMESTAMP', 'Use timestamp on distribution', True))
    opts.Add(BoolVariable('SHLIBVERSIONING',
                          'Use libtool-style versionated shared library', True))

    opts.Add('SONAMEPREFIX', 'Prefix for compiler soname command.', 
             '${_sonameprefix(__env__)}')
    opts.Add('SONAMESUFFIX','Suffix for compiler soname command.', '')

    opts.Add('SONAMEFLAGS',
             'Shared libraries link flags.',
             ['${_sonamecmd(SONAMEPREFIX, TARGET, SONAMESUFFIX, __env__)}'])


    opts.Add('INSTALL_NAME_DIR',
             'Path to be used for dylib install_name (darwin only)',
             '@loader_path')

    opts.Add('SHLIBVERSIONSUFFIX',
             'Shared libraries suffix for library versioning.',
             '-' + pboriversion +'.' + pborirelease +
             defaultenv['SHLIBSUFFIX'] + '.$LIBRARY_VERSION')



    opts.Add(BoolVariable('FORCE_HASH_MAP', "Force the use of gcc's deprecated " +
    "hash_map extension, even if unordered_map is available (avoiding of buggy " +
    "unordered_map)", False))

    opts.Add('RPATH', "rpath setting",  converter = SplitColonSep)


    for m in pbori_cache_macros:
        opts.Add(m, 'PolyBoRi Cache macro value: '+m, None)


    for var in Split("""CCCOM CXXCOM SHCCCOM SHCXXCOM SHLINKCOM LINKCOM LINK SHLINK
    SHLIBPREFIX LIBPREFIX SHLIBSUFFIX LIBSUFFIX"""):
        if defaultenv.has_key(var):
            opts.Add(var, 
                     "inherited from SCons", defaultenv[var])
    else:
            if var != "LIBSUFFIX":
                print "Variable", var, "not in default environment!"

    opts.Add('LIBRARY_VERSION', "libtool-style library version", '0.0.0')

    opts.Add('CONFFILE', "Dump settings to file, if given", '')

    opts.Add('PLATFORM', "Manually set another platform (unusual)",
             defaultenv['PLATFORM'])

    tools =  defaultenv['TOOLS'] + ["disttar", "doxygen"]


    # Get paths and related things from current environment os.environ
    # note: We cannot avoid those due to non-standard system setups,
    #       also we do not know which variables are used in general

    return (Environment(ENV = os.environ, options = opts, tools = tools, 
                        toolpath = '.'), opts, tools)


(env, opts, tools) = setup_env(defaultenv)

if defaultenv['PLATFORM'] == "sunos":  # forcing gcc, keeping linker
    def is_gnu():
        compilerenv = Environment(ENV = os.environ, options = opts)
        return (detect_compiler(compilerenv)  == 'gnu',
                detect_linker(compilerenv)  == 'gnu')

    (is_gcc, is_gnulink) = is_gnu()

    tools = [tool for tool in defaultenv['TOOLS']]

    if is_gcc:
        for arg in ['default', 'suncc', 'sunc++', 'sunar']:
            if arg in tools:
                tools.remove(arg)
        tools +=  [ 'gcc', 'g++', 'ar']

    if is_gnulink:
        if 'sunlink' in tools:
            tools.remove('sunlink')
        tools +=  ['gnulink']
    else:
        if 'gnulink' in tools:
            tools.remove('gnulink')
        tools +=  ['sunlink']
    if tools != defaultenv['TOOLS']:    

        platform_opts = Variables(args={'PLATFORM': defaultenv['PLATFORM']})
        defaultenv = Environment(ENV=os.environ, tools=tools,
                                 options=platform_opts)

        (env, opts, tools) = setup_env(defaultenv)


# Monkey patching Install/InstallAs to fix permissions on install
_env_install = env.Install
_env_installas = env.InstallAs

def _env_install_final(env, *args):
    return FinalizePermissions(_env_install(env, *args))

def _env_installas_final(env, *args):
    return FinalizePermissions(_env_installas(env, *args))

_env_install_final.__doc__ = env.Install.__doc__
_env_installas_final.__doc__ = env.InstallAs.__doc__

env.Install = _env_install_final
env.InstallAs = _env_installas_final


# Another monkey patch: Ensure that necessary flags are appended 
# (explicitely set DEFAULT_<flags>="" if defaults should be removed)
for key in env.Dictionary().keys():
    if key.startswith('DEFAULT_'):
        env.AppendUnique(**{key.replace('DEFAULT_',''): ['$' + key]})

# Extract some option values
HAVE_DOXYGEN = env['HAVE_DOXYGEN'] and ("doxygen" in tools)
HAVE_PYTHON_EXTENSION = env['HAVE_PYTHON_EXTENSION']

USERLIBS = list(env.get('LIBS', []))

# Skipping doxygen-based docu, if no doxygen is found.
if HAVE_DOXYGEN:
    HAVE_DOXYGEN = env.Detect('doxygen')
    if not HAVE_DOXYGEN:
        print "Doxygen not found, skipping C++-documentation generation!"

    

# soname related stuff
def _sonamecmd(prefix, target, suffix, env = env):
    """Creates soname."""

    target = str(env.subst(target))
    import re
    soPattern = re.compile('(.*)\.[0-9]*\.[0-9]*$', re.I|re.S)
    soname = soPattern.findall(path.basename(target))
    if len(soname) > 0:
        return prefix + soname[0] + suffix    
    else:
        if env['PLATFORM']=="darwin":
            return prefix + path.basename(target) + suffix

        return ''
    


env['_sonamecmd'] = _sonamecmd
env['_sonameprefix'] = _sonameprefix
env['_fix_dynlib_flags'] = _fix_dynlib_flags
env['_moduleflags'] = _moduleflags
env['_relative_rpath'] = _relative_rpath  
env['_dynmodule_flags'] = _dynmodule_flags


# config.h generator
def config_h_build(target, source, env):
    """ config_h building..."""
    def define_line(name, value):
        return """#ifndef %(name)s
#define %(name)s %(value)s
#endif
""" % dict(name=name, value=value)
    
    from string import join
    macros = [elt.split('=') + [''] for elt in env['CPPDEFINES'] ]
    for macro in pbori_cache_macros:
        if env.get(macro, None): macros += [ (macro,  env[macro]) ]
    
    config_defs =  join([define_line(elt[0], elt[1]) for elt in macros], '')
    config_h_in = """/* File: %(target)s
 * Automatically generated by PolyBoRi %(version)s */
#ifndef polybori_config_h_
#define polybori_config_h_

%(defs)s
#endif /* polybori_config_h_ */
"""
    config_ver = pboriversion + '.' + pborirelease

    for a_target, a_source in zip(target, source):
        config_h = file(str(a_target), "w")
        conf_repl = dict(target=a_target, version=config_ver, defs=config_defs)
        config_h.write(config_h_in % conf_repl)
        config_h.close()

def config_h_message(*args):
    return "writing config.h..."

config_h = env.Command(PBPath('include/polybori/config.h'),
                       'SConstruct',
                       action = env.Action(config_h_build, 
                                           config_h_message))
env.AlwaysBuild(config_h)

class PythonConfig(object):
    def __init__(self, python_executable):
        def querycmd(arg):
            from subprocess import Popen, PIPE, STDOUT
            process = Popen([self.python], stdin=PIPE, stdout=PIPE, stderr=STDOUT,
                           env=os.environ)
            return process.communicate("from distutils.sysconfig import *\n" +
                                       "print " + arg + "\n")[0].strip()


        self.python = python_executable
        self.version = querycmd("get_python_version()")
        self.sitedir = querycmd("get_python_lib()")
        self.libdir = querycmd("get_config_vars()['LIBDIR']")
        self.incdir = querycmd("get_python_inc()")
        self.staticlibdir = querycmd("get_config_vars()['LIBPL']")
        self.libs = querycmd("get_config_vars()['LIBS']")
        self.module_suffix = querycmd("get_config_vars()['SO']")

        self.libs = self.libs.split()
        if env['PLATFORM']=="darwin":
            #workaround for -framework, CoreFoundation entries...
            self.libs=[l for l in self.libs if l.startswith('-l')]
        
        self.libs=[l.replace('-l','') for l in self.libs]
        self.libname = 'python' + str(self.version)

pyconf = PythonConfig(env.subst("$PYTHON"))

env.AppendUnique(PYTHONSITE = pyconf.sitedir)

have_l2h = have_t4h = False
external_m4ri = False
GD_LIBS = []
BOOST_TEST = env['BOOST_TEST']
dylibs = []
stlibs = []

if not env.GetOption('clean'):
    def CheckSizeOfTypes(context):
        context.Message('Detecting type sizes... ')
        test_src_sizeof =  """
        #include <stdio.h>
        int main(int argc, char **argv) {
          printf("SIZEOF_VOID_P=%u SIZEOF_INT=%u SIZEOF_LONG=%u",
            (unsigned)sizeof(void*), (unsigned)sizeof(int), (unsigned)sizeof(long));
          return 0;
        }
        """
        (result, values) = context.TryRun(test_src_sizeof, '.c')
        result = (result == 1)
        if result:
            context.Display('got ' + values + '...')
            env.Append(CPPDEFINES=Split(values))
        context.Result(result)
        return result

    def CheckLongLong(context):
        context.Message('Checking whether C++ knows about long long... ')
        test_src_longlong =  """
        int main(int argc, char **argv) {
          long long val = 0LL;
          return (int)val;
        }
        """
        (result, values) = context.TryRun(test_src_longlong, '.cc')
        result = (result == 1)
        context.Result(result)
        return result

    def GuessM4RIFlags(context, external):
        context.Message('Guessing m4ri compile flags... ')
        if not external:
            if not os.path.exists(M4RIInc('config.h')):
                context.Message("Abusing m4ri's configure to get headers... ")
                Execute("cd M4RI; ./configure --prefix=$PREFIX; cd -")
        
        test_src =  """
        #include <m4ri/%s>
        #include <stdio.h>
        int main(int argc, char **argv) {
        #ifdef __M4RI_SIMD_CFLAGS
          /* get relevant compile flags of M4RI */
          printf(__M4RI_SIMD_CFLAGS);
          printf(" ");
        #elif defined(__M4RI_CFLAGS)
          /* fall back: get compile flags of M4RI */
          printf(__M4RI_CFLAGS);
          printf(" ");
        #else
          /* fall back: test for possible current and future configurations */
          %s
        #endif
          return 0;
        }
        """  %  \
        ("%s", ''.join(["""
        #if (defined(__M4RI_HAVE_%(macro)s) && (__M4RI_HAVE_%(macro)s)) || \
          defined(HAVE_%(macro)s)
          printf("-m%(option)s ");
        #endif""" % \
        dict(macro=opt.replace('.','_').upper(), option=opt) for opt in \
            Split("sse sse2 sse3 sse4 sse4.1 sse4.2 sse4a ssse3 mmx 3dnow") ]) )
        (result, values) = context.TryRun(test_src % "m4ri_config.h", '.c')
	if result != 1:
            (result, values) = context.TryRun(test_src % "config.h", '.c')

        result = (result == 1)
        if result:
            context.Display(values)
            env.Append(M4RI_CFLAGS=Split(values))

        context.Result(result)
        return result

    conf = Configure(env, 
                     custom_tests = {'CheckSizeOfTypes': CheckSizeOfTypes,
                                     'CheckLongLong': CheckLongLong,
                                     'GuessM4RIFlags': GuessM4RIFlags})

    if not conf.CheckSizeOfTypes():
        print "Could not detect type sizes (maybe compile/link flags " + \
            "trouble)! Exiting."
        Exit(1)

    if conf.CheckLongLong():
        env.Append(CPPDefines='PBORI_HAVE_LONG_LONG')

    if env['FORCE_HASH_MAP']:
        if conf.CheckCXXHeader('ext/hash_map'):
            env.Append(CPPDEFINES=["PBORI_HAVE_HASH_MAP"])  
    else:
        if conf.CheckCXXHeader('unordered_map'):
            env.Append(CPPDEFINES=["PBORI_HAVE_UNORDERED_MAP"])
        elif conf.CheckCXXHeader('tr1/unordered_map'):
            env.Append(CPPDEFINES=["PBORI_HAVE_TR1_UNORDERED_MAP"])
        elif conf.CheckCXXHeader('ext/hash_map'):
            env.Append(CPPDEFINES=["PBORI_HAVE_HASH_MAP"])  
        
    extern_python_ext = env['EXTERNAL_PYTHON_EXTENSION']
    if HAVE_PYTHON_EXTENSION or extern_python_ext:
        env.Append(CPPPATH=[pyconf.incdir])
        env.Append(LIBPATH=[pyconf.libdir, pyconf.staticlibdir])

    env.Prepend(CPPPATH=[PBPath('include'), GBPath('include')])
    env.Append(CPPDEFINES=["PBORI_HAVE_M4RI"])


    if HAVE_PYTHON_EXTENSION:
        if not (conf.CheckLib(pyconf.libname, autoadd=0)):
            print "Python library not available (needed for python extension)!"
            HAVE_PYTHON_EXTENSION = False

    if HAVE_PYTHON_EXTENSION:
        if not (conf.CheckCXXHeader(path.join('boost', 'python.hpp'))):
            print "Developer's version of boost/python not available ",
            print "(needed for python extension)!"
            HAVE_PYTHON_EXTENSION = False

    if HAVE_PYTHON_EXTENSION:
        store_libs =[elt for elt in env["LIBS"]]
        env.Append(LIBS=pyconf.libname)
        if not ( conf.CheckLibWithHeader([env['BOOST_PYTHON'], pyconf.libname ],
                 path.join('boost', 'python.hpp'), 'c++', autoadd=0) ):

            print "Warning Boost/Python library (", env['BOOST_PYTHON'],
            print ") not available (needed for python extension)!"
            HAVE_PYTHON_EXTENSION = False
        env["LIBS"] = store_libs

    if not conf.CheckLib(BOOST_TEST, autoadd=0):
         print "Warning Boost/unit test framework library (",
         print BOOST_TEST, ") not available. Skipping tests."
         BOOST_TEST = None

    have_l2h = env['HAVE_L2H'] and env.Detect('latex2html')

    tex_to_ht = 'hevea'

    if not have_l2h:
        have_t4h = env['HAVE_HEVEA'] and env.Detect('hevea')
        t4h_opts = ''
        if not have_t4h:
            have_t4h = env['HAVE_TEX4HT'] and env.Detect('htlatex')
            tex_to_ht = 'htlatex'

            if not have_t4h:
                print "Warning: No LaTeX to html converter found,",
                print "Tutorial will not be installed"
    external_m4ri = conf.CheckLib('m4ri', autoadd=0)
    m4ri_png = False
    if external_m4ri:
       env.Append(LIBS='m4ri')
       if conf.CheckFunc('testing_m4ri_PNGs', """
                   #include <m4ri/io.h>
                   #define testing_m4ri_PNGs() mzd_to_png(NULL,"",0,"",0)"""):
           m4ri_png = True
           env.Append(CPPDEFINES=["PBORI_HAVE_M4RI_PNG"])
           for suffix in ['', '12', '13', '10', '11']:
               if conf.CheckLib('png' + suffix, autoadd=0):
                   GD_LIBS = ['png' + suffix]
                   break
    else:
       env['CPPPATH'] = [m4ri_inc] + env['CPPPATH']
       
    conf.GuessM4RIFlags(external_m4ri)

    if not m4ri_png:
        gdlibs = env["GD_LIBS"]
        if gdlibs and conf.CheckCHeader("gd.h"):
            store_libs = [elt for elt in env["LIBS"]]
            env.Append(LIBS=gdlibs[1:])

            if conf.CheckLib(gdlibs[0], autoadd=0):
                env["LIBS"] = store_libs
                env.Append(LIBS=gdlibs)
                if conf.CheckFunc("testing_PNGs",
                                  "#include<gd.h>\n#define testing_PNGs() gdImagePng(NULL,NULL) "):
                    env.Append(CPPDEFINES=["PBORI_HAVE_GD"])
                    GD_LIBS = gdlibs
                else:
                    print "libgd is available, but could not generate png file -",\
                      "dependencies in GD_LIBS missing? -", \
                      "Skipping gd-based optional features."
            env["LIBS"] = store_libs


    env = conf.Finish()

else: # when cleaning
    # Work around bug in older SCons (didn't remove symlinks to files)
    if scons_version() < ['1','3','0']:
        for elt in glob('*' + env['SHLIBSUFFIX'] + "*") + \
                [PyRootPath('polybori/dynamic')]:
            if os.path.islink(elt):
                os.remove(elt)

    # things not handled by builders
    for elt in [PyRootPath('polybori/dynamic')]:
        if os.path.exists(elt) and os.path.islink(elt):
            os.remove(elt)
 
# end of not cleaning

env.Clean('.',  glob("config.log") + glob(".scon*") + \
          glob(PBPath('*' + env['LIBSUFFIX'])) + \
          glob(GBPath('*' + env['LIBSUFFIX'])) + \
          glob('*' + env['SHLIBSUFFIX'] + "*") + glob('*.pyc')  )


have_pydoc = env['HAVE_PYDOC']

env['PBVERSION'] = pboriversion
env['PBRELEASE'] = pborirelease

if env['M4RI_RPM']:
    env['PB_M4RI_RPM'] = "1"
else:
    env['PB_M4RI_RPM'] = "0"

# Resoruces for including anything into the PyPolyBoRi shared library
shared_resources = []

# Builder for symlinks
def build_symlink(target, source, env):

    target = target[0]
    targetdir = target.dir.abspath
    targetpath = target.abspath
    target = target.path
    source = source[0].abspath

    if env['RELATIVE_SYMLINK'] :
        source = env.relpath(targetdir, source)
    if not source:
        source = '.'

    print "Symlinking from", source, "to", target
   
    if path.exists(targetpath):
        os.remove(targetpath)
    os.symlink(source, targetpath)

    return None

symlinkbld = Builder(action = build_symlink)

env.Append(BUILDERS={'SymLink' : symlinkbld})

def shared_object(o, **kwds):
    return env.SharedObject(o, **kwds)

######################################################################
# Paths
######################################################################

InstPyPath = PathJoiner(env['PYINSTALLPREFIX'])

DevelInstPath = PathJoiner(env['DEVEL_PREFIX'])
PBInclPath = PathJoiner(PBPath('include/polybori'))
DevelInstInclPath = PathJoiner(env['DEVEL_INCLUDE_PREFIX'], 'polybori')
DevelInstLibPath = PathJoiner(env['DEVEL_LIB_PREFIX'])

BuildLibPath = PathJoiner(BuildPath(DevelInstLibPath().lstrip(sep)))
BuildPyPBPath = PathJoiner(BuildPath(InstPyPath('polybori/dynamic').lstrip(sep)))


######################################################################
# Stuff for building Cudd library
######################################################################

#env.Append(CPPDEFINES=["PBORI_HAVE_IEEE_754"])


cudd_headers = [ CuddPath('cudd/' + fname + '.h') for fname in Split("""
cuddInt cudd util""") ] + [PBInclPath('cudd/prefix' + fname + '.h')
                      for fname in ['', '_internal'] ]
    
cudd_resources = [CuddPath('cudd/cudd' + elt) for elt in Split("""
API.c Cache.c Init.c LCache.c Ref.c Table.c ZddFuncs.c ZddSetop.c""") ]

cudd_shared = shared_object(cudd_resources, CPPPATH = env['CPPPATH'] + [CuddPath()])

#libCudd = env.StaticLibrary(CuddPath(cudd_name), cudd_resources)

shared_resources += cudd_shared

###################
# End of Cudd stuff
###################


def SymlinkReadableLibname(files):
    """ Generate symbolik link with more readable library name."""
    
    suffix = env.subst('$SHLIBVERSIONSUFFIX')
    simplesuffix = env.subst('$SHLIBSUFFIX')
    result = []
    import re
    soPattern = re.compile('(.*)\.[0-9]*\.[0-9]*$', re.I|re.S)
    sonameversion = soPattern.findall(path.basename(env.subst('$LIBRARY_VERSION')))[0]
    
    for fname in files:
        fname = str(fname)
        soname = soPattern.sub(r'\1', fname)
        versionname = fname.replace('.' + env.subst('$LIBRARY_VERSION'), '')
        simple = fname.replace(suffix, simplesuffix)

        for (dest, src) in [(soname, fname), (versionname, soname),
        (simple, versionname)]:
            if (dest != src):
                result += env.SymLink(dest, src)
    return result

def VersionatedSharedLibrary(*args, **kwds):

    kwds['SHLIBSUFFIX'] = env.subst('$SHLIBVERSIONSUFFIX')

    sharedlib = env.SharedLibrary
    return sharedlib(*args, **kwds)

slib = env.SharedLibrary
if env['SHLIBVERSIONING']:
    slib = VersionatedSharedLibrary


######################################################################
# Stuff for building PolyBoRi's C++ part
######################################################################

pb_src=Split("""BoolePolyRing.cc BooleEnv.cc BoolePolynomial.cc BooleVariable.cc
    CCheckedIdx.cc CErrorInfo.cc PBoRiError.cc CCuddFirstIter.cc
    BooleMonomial.cc BooleSet.cc LexOrder.cc CCuddLastIter.cc 
    BooleExponent.cc DegLexOrder.cc DegRevLexAscOrder.cc
    pbori_routines.cc BlockDegLexOrder.cc BlockDegRevLexAscOrder.cc""")

pb_src=[PBPath('src', source) for source in pb_src]

libpb_name = 'polybori'
libpb_name_static = libpb_name

libpb=env.StaticLibrary(PBPath(libpb_name_static), pb_src + cudd_resources)

if isinstance(libpb,list):
    libpb=libpb[0]


pb_shared = shared_object(pb_src)
shared_resources += pb_shared

libpbShared = slib(BuildLibPath(libpb_name), list(shared_resources))
pb_symlinks = SymlinkReadableLibname(libpbShared)

env.Clean([libpb] + pb_shared, config_h)

######################################################################
# Stuff for building Groebner library
######################################################################

gb_src=Split("""groebner.cc LiteralFactorization.cc
LiteralFactorizationIterator.cc randomset.cc pairs.cc
groebner_alg.cc FGLMStrategy.cc polynomial_properties.cc LexBucket.cc
dlex4data.cc dp_asc4data.cc lp4data.cc nf.cc interpolate.cc GroebnerStrategy.cc
PairManager.cc PolyEntry.cc ReductionStrategy.cc MatrixMonomialOrderTables.cc""")
gb_src = [GBPath('src', source) for source in gb_src]

if not(external_m4ri):
   gb_src += m4ri
   env.Clean(M4RIPath(), [M4RIPath(elt) for elt in Split(""".deps Makefile
   config.status libtool m4ri.pc m4ri/config.h m4ri/m4ri_config.h m4ri/stamp-h1
   testsuite/Makefile""")])
   
libgb_name = libpb_name + '_groebner'
libgb_name_static = libgb_name

gb=env.StaticLibrary(GBPath(libgb_name_static), gb_src)

#print "gb:", gb, dir(gb)
#sometimes l seems to be boxed by a list
if isinstance(gb,list):
    gb=gb[0]

gb_shared = shared_object(gb_src)#env.SharedObject(gb_src)
shared_resources += gb_shared

libgbShared = slib(BuildLibPath(libgb_name), list(gb_shared),
                   LIBS = libpbShared + env['LIBS'] + GD_LIBS)


gb_symlinks = SymlinkReadableLibname(libgbShared)

CPPPATH=env['CPPPATH']+[GBPath('include')]
#print env['CCFLAGS']
#print env['CXXFLAGS']


######################################################################
# Doxygen-based docu
######################################################################

docutarget = [DocPath('c++', elt) for elt in Split("html latex")]
if HAVE_DOXYGEN:
    cxxdocu = env.Doxygen(source=[DocPath('doxygen.conf')], target=docutarget)
 
env.Clean(DocPath('c++'), docutarget)

######################################################################
# Boost-test based tests
######################################################################

testclasses = Split("""GroebnerStrategy spoly term_accumulate CStringLiteral BooleEnv BooleSet BooleConstant BoolePolyRing BooleExponent BooleVariable BooleMonomial BoolePolynomial PBoRiError CCuddDDFacade DegRevLexAscOrder DegLexOrder
BlockDegRevLexAscOrder BlockDegLexOrder  LexOrder 
CFactoryBase MonomialFactory PolynomialFactory VariableFactory SetFactory
weak_pointers FGLMStrategy PseudoLongProduct""")

# Note: use custom TEST_CPPPATH settings for testing header installation, if any
try:
    testCPPPATH = env['TEST_CPPPATH']
except:
    testCPPPATH = None
if not testCPPPATH:
    testCPPPATH = CPPPATH


if BOOST_TEST:
    testfiles = env.Object([TestsPath('src', src + "Test.cc") for src in
                           testclasses], CPPPATH=testCPPPATH)
    testmain = env.Object([TestsPath('src', "unittests.cc")],
                          CPPPATH=testCPPPATH,
                          CPPDEFINES = ["BOOST_TEST_DYN_LINK"])

    def test_building(target, sources, env):
        env.Program(target, sources + testmain, 
                    CPPPATH=testCPPPATH,
                    LIBS = env['LIBS'] + \
                        [BOOST_TEST] + libpbShared + libgbShared  + GD_LIBS,
                    CPPDEFINES = ["BOOST_TEST_DYN_LINK"] )

    test_building(TestsPath("unittests"), testfiles, env)

    for testfile in testfiles:
        test_building(path.splitext(testfile.path)[0] + '.bin', [testfile], env)


######################################################################
# python extension
######################################################################
LIBS = env['LIBS']+[env['BOOST_PYTHON']]+USERLIBS


documentable_python_modules = [PyRootPath('polybori', f)
                               for f in Split("""ll.py check_claims.py nf.py
                               gbrefs.py statistics.py randompoly.py blocks.py 
                               specialsets.py memusage.py
                               heuristics.py gbcore.py interpolate.py
                               interred.py ncf.py partial.py simplebb.py
                               PyPolyBoRi.py __init__.py dynamic/__init__.py""")
                               ] 


# Currently all python modules are at place
installable_python_modules = []

pydocu = []
dynamic_modules = []
pypb_symlinks = []


if HAVE_PYTHON_EXTENSION:
    wrapper_files=[ PyPBPath(f) for f in Split("""pypb_module.cc
    main_wrapper.cc test_util.cc fglm_wrapper.cc
    Poly_wrapper.cc navigator_wrap.cc variable_block.cc
    monomial_wrapper.cc misc_wrapper.cc strategy_wrapper.cc set_wrapper.cc
    slimgb_wrapper.cc""") ] 
    

    pypb=env.LoadableModule(BuildPyPBPath('PyPolyBoRi'),
                            wrapper_files,
                            LIBS = pyconf.libs + LIBS + \
                                GD_LIBS + libpbShared + libgbShared,
                            LDMODULESUFFIX = pyconf.module_suffix,
                            LDMODULEPREFIX = "",
                            )

    env.Depends(pypb, pb_symlinks + gb_symlinks)
    
    if env['PLATFORM']=="darwin":
            def fix_install_name(target, source, env):
                names = ' '.join([str(elt) for elt in dylibs])
                names = Split(shell_output('otool', '-D', names))[1::2]
                for name in names:
                    newname = "@loader_path/" + \
                        env.relpath(InstPyPath("polybori/dynamic"),
                                    DevelInstLibPath(os.path.basename(name)))
                    env.Execute("install_name_tool -change %s %s %s"%(name, newname, target[0]))

            env.AddPostAction(pypb, fix_install_name)

# __init__.py generator
    def init_build(target, source, env):
        """__init__.py building..."""

        init_py_in = """# File: %(target)s
# Automatically generated by PolyBoRi
# This file is just for developing, it should not be installed.
import imp
imp.load_dynamic("polybori.dynamic.PyPolyBoRi", "%(source)s")
"""

        init_py = file(target[0].path, "w")
        init_py.write(init_py_in  % dict(target = target[0].path, 
                                   source = source[0].abspath))
        init_py.close()
        
    def init_message(target, *args):
        return target[0].path + " building..."
        
    dynamic_init_py = env.Command(PyRootPath('polybori/dynamic/__init__.py'), 
                                  pypb, 
                                  action = env.Action(init_build, init_message))

    env.Alias(BuildPath(), dynamic_init_py) # Developers also need this

    pypb_init_py = env.Command(BuildPyPBPath('__init__.py'), pypb, 
                               [Touch("$TARGET")])


    # Define the dynamic python modules in pyroot
    documentable_python_modules += dynamic_modules
   
    
    polybori_modules = PyRootPath("polybori")
    #DefaultBuild(env.Install(polybori_modules, pypb))
    for (f,n) in installable_python_modules:
        env.Install(polybori_modules, f)

    
    to_append_for_profile = [libpb, gb]
    #to_append_for_profile=File('/lib/libutil.a')
    env.Program(PyPBPath('profiled'), wrapper_files+to_append_for_profile,
            LIBS = LIBS + ["python" + str(pyconf.version)] + USERLIBS + pyconf.libs + GD_LIBS,
            CPPDEFINES=env["CPPDEFINES"]+["PB_STATIC_PROFILING_VERSION"])


  

else:
    print "no python extension"

if HAVE_PYTHON_EXTENSION or extern_python_ext:
    # Generating python documentation
    def pypb_emitter(target,source,env):

        TargetPath = PathJoiner(target[0].dir)
        for filename in source:
            (fname, fext) = path.splitext(str(filename).replace(pyroot,''))

            if not fname.split(sep)[-1] == "__init__" :
                if fext in ['.so', '.py'] :
                    fname = TargetPath(fname.replace(sep,'.') + '.html')
                    target.append(env.File(fname))

        return (target, source)

    bld = Builder(action = "$PYTHON doc/python/genpythondoc.py " + pyroot,
                  emitter = pypb_emitter)

    # Add the new Builder to the list of builders
    env['BUILDERS']['PYTHONDOC'] = bld

    # Generate foo.vds from foo.txt using mk_vds
    #for f in Split("ll.py nf.py gbrefs.py blocks.py PyPolyBoRi.so specialsets.py"):
    if have_pydoc:
        pydocu = env.PYTHONDOC(target=[DocPath('python/polybori.html'),
                                       DocPath('python/polybori.dynamic.html')],
                               source = documentable_python_modules)

        env.Clean(pydocu, glob(PyRootPath('polybori/*.pyc')) +
                  glob(PyRootPath('polybori/dynamic/*.pyc')))
#        env.Ignore(pydocu, dynamic_modules)
    #bld=Builder("cd")

    

# Source distribution archive generation
env.Append(DISTTAR_EXCLUDEEXTS = Split(""".o .os .so .a .dll .cache .pyc
           .cvsignore .dblite .log .sconsign .depend .out .graphViz_temp .exe
           .kprof.html .rpm .spec .so.0 .so.0.0.0 .0 .gcda .orig .rej .bin"""),
           DISTTAR_EXCLUDEDIRS = Split("""CVS .svn .sconf_temp SOURCES BUILD
           auxiliary .deps"""),
           DISTTAR_EXCLUDEPATTERN = Split(""".#* #*# *~ profiled cacheopts.h
           *config.h coding.py unittests Makefile config.status libtool
           m4ri.pc stamp-h1"""))

   
if distribute or rpm_generation or deb_generation:
    allsrcs = Split("""SConstruct README LICENSE ChangeLog versionnumber
disttar.py doxygen.py""")
    for dirname in Split("""groebner ipbori M4RI libpolybori 
    PyPolyBoRi pyroot pkgs gui testsuite"""):
        allsrcs.append(env.Dir(dirname))

    # Cudd is not distributed completely (unused and unfree things removed)
    allsrcs += [CuddPath(src) for src in Split("""LICENSE README
    RELEASE.NOTES""") ]
    allsrcs += [env.Dir(CuddPath(src)) for src in Split("""cudd""") ]

    # doc is not distributed completely
    allsrcs += [ DocPath(dsrc) for dsrc in Split("""doxygen.conf index.html.in
    tutorial/tutorial.tex tutorial/tutorial_content.tex tutorial/PolyGui.png
    tutorial/PolyGui-Options.png tutorial/versionnumber.in python/genpythondoc.py
    man/ipbori.1 man/PolyGUI.1 """) ]
    allsrcs.append(env.Dir(DocPath('images')))
    

if distribute:
    presrcdistri = env.DistTar(debname, allsrcs)
    (srcdistrname, srcdistrext1) = path.splitext(str(presrcdistri[0]))
    (srcdistrname, srcdistrext) = path.splitext(srcdistrname)
    srcdistrext += srcdistrext1
    pborisuffix = ''

    #if str(pborirelease) != "0" :
    #    pborisuffix += "-" + str(pborirelease)

    if env['USE_TIMESTAMP']:
        from datetime import date
        pborisuffix += "-" + str(date.today())

    if pborisuffix :
        srcdistri = env.Command(srcdistrname + pborisuffix + srcdistrext,
                                presrcdistri,                            
                                Move("$TARGET", "$SOURCE"))
    else :
        srcdistri = presrcdistri
                
    env.AlwaysBuild(srcdistri)
    env.Alias('distribute', srcdistri)
    
dylibs += libpbShared + libgbShared 
stlibs += [libpb, gb]

readabledevellibs = pb_symlinks + gb_symlinks + pypb_symlinks

dylibs_inst  = env.Install(DevelInstLibPath(), dylibs)
stlibs_inst  = env.Install(DevelInstLibPath(), stlibs)
dylibs_readable_inst = SymlinkReadableLibname(dylibs_inst)

devellibs_inst = dylibs_readable_inst + dylibs_inst + stlibs_inst


# Installation for development purposes
if 'devel-install' in COMMAND_LINE_TARGETS:

    for elt in ['..', '.'] + [path.basename(elt)
                              for elt in glob(PBInclPath('*'))
                              if path.isdir(elt) and path.basename(elt) != 'cudd' ]:
        env.Install(DevelInstInclPath(elt), glob(PBInclPath(elt, '*.h')))

    env.Install(DevelInstInclPath('groebner'),
                glob(GBPath('include/polybori/groebner/*.h')))

    # Install our own copy the cudd header to ensure correct (patched) version 
    env.Install(DevelInstInclPath('cudd'), cudd_headers)

    if not(external_m4ri):
        env.Install(DevelInstInclPath('m4ri'), glob('M4RI/m4ri/*.h'))
        
    env.Alias('devel-install', DevelInstPath())
    env.Alias('devel-install', DevelInstInclPath())
    env.Alias('devel-install', DevelInstLibPath())
    
env.Append(COPYALL_PATTERNS = ['*'])

# Copy glob('*') from one directory to the other
def cp_all(target, source, env):
    source = source[0].path
    target = target[0].path

    if not path.exists(target):
        try:
            env.Execute(Mkdir(target))
        except:
            # Maybe just a race condition occured, because two processes trixy
            # to generate the directory at the same time. (This I could ignore.)
            if not path.exists(target):
                print "Could not mkdir " + target
                Exit(1)

    for patt in env['COPYALL_PATTERNS']:
        for filename in glob(path.join(source, patt)):
            if not path.isdir(filename):
                result = str(path.join(target, path.basename(filename)))
                env.Execute([Copy(result, filename), Chmod(result, 0644)])

    return None

def CopyAll(targetdir, sourcedir, env):
    targets = []
    for patt in env['COPYALL_PATTERNS']:
        for filename in glob(path.join(sourcedir, patt)):
            if not path.isdir(filename):
                result = str(path.join(targetdir, path.basename(filename)))
                targets += env.Install(targetdir, filename)

    return FinalizeNonExecs(targets)            

# Copy python docu from one directory to the other and correct paths to modules
def cp_pydoc(target, source, env):

    source = source[0].path
    target = target[0].path
    import re
    patt = re.compile('(file:|)/[^\" ]*' + pyroot, re.VERBOSE)

    if not path.exists(target):
        env.Execute(Mkdir(target))
    showpath = env.relpath(env.Dir(target).abspath,
                           env.Dir(env['PYINSTALLPREFIX']).abspath)

    if showpath != '' and showpath[-1] != '/':
         showpath += '/'
    for filename in glob(path.join(source, '*.html')):
        if not path.isdir(filename):
            fcontent = open(filename).read()
            fcontent = patt.sub(r''+showpath, fcontent)

            result = str(path.join(target, path.basename(filename)))
            open(result, "w").write(fcontent)

    return None


cp_recbld = Builder(action = cp_all)
cp_pydocbld = Builder(action = cp_pydoc)


# Note: target[0] needs to be the path resulting from latex2html
# todo: More generic by moving actual result to given path?
def l2h_emitter(target, source, env):
    target = [env.File(path.join(str(target[0]), 'index.html'))]
    env.Clean(target, target[0].dir)
    return (target, source)

l2h = Builder(action = 'cd `dirname $SOURCE`; latex2html -html_version 4.0,unicode,utf-8 $SOURCE',
              emitter = l2h_emitter)

def t4h_emitter(target, source, env):
    target = [env.File(path.join(str(target[0]), 
                      path.splitext(path.basename(source[0].name))[0] + '.html'))]
    env.Clean(target, target[0].dir)
    return (target, source)


if have_t4h :
    t4h_str =  tex_to_ht + ' ' + path.join(env.Dir('').abspath, "$SOURCE") + t4h_opts
    os.environ['TEXINPUTS'] = env.Dir('doc/tutorial').abspath

    def t4h_action(source, target, env, for_signature):
        subdir = path.splitext(target[0].name)[0]
        if tex_to_ht == 'htlatex':
            t4h_opts = ' "html,2,charset=utf-8" " -cunihtf -utf8" "-d%s/"' % subdir
   
        return ('cd %s;' + tex_to_ht + ' %s ' +  t4h_opts) % (source[0].dir, source[0].abspath)

    tex_to_ht_bld = Builder(generator = t4h_action, emitter = t4h_emitter)
    env.Append(BUILDERS={'TeXToHt' : tex_to_ht_bld})


# substition function 
def substitute_install(target, source, env,
                       preprocess = None, postprocess = None):
        from string import Template
        page = open(str(source[0]), 'r').read()

        if preprocess:
            page = preprocess(page) 
        page = Template(page).safe_substitute(env)
        if postprocess:
            page = postprocess(page)     
        open(str(target[0]), 'w').write(page)
        return None

substinstbld  = Builder(action = substitute_install)


def docu_master(target, source, env):
    import os, re

    basefiles = ['index.html', 'polybori.html', 'tutorial.html']
    basesfound = []
    
    for item in source:
        if os.path.isdir(str(item)):
            for root, dirs, files in os.walk(str(item)):
                for filename in files:
                    if filename in basefiles:
                        basesfound.append(os.path.join(root, filename))

    if str(target[0]) in basesfound:
        basesfound.remove(str(target[0]))

    linkPattern = re.compile('<title.*?>(.*?)</title>', re.I|re.S) 
    links = ''
    for src in basesfound:
        fhandle = open(src, 'r')
        fcontent = fhandle.read()
        fhandle.close()
        ftitle = linkPattern.search(fcontent).group(1)
        relsrc = relpath(str(target[0].dir), src)
        links +=  '<P><A href="' + relsrc + '">' + ftitle +'</A>\n'


    env['PBDOCLINKS'] = links
    substitute_install(target, source, env)

    return None

def docu_emitter(target, source, env):
    if source[0].dir != target[0].dir :
        import re
        linkPattern = re.compile('<img src *?= *?"([^>]*?)".*?>', re.I|re.S) 
        fhandle = open(str(source[0]), 'r')
        relsrcs = linkPattern.findall(fhandle.read())
        SrcPath = PathJoiner(source[0].dir)
        TargetPath = PathJoiner(target[0].dir)

        for src in relsrcs:
            FinalizeNonExecs(env.InstallAs(env.File(TargetPath(src)),
                                           SrcPath(src)))
        fhandle.close()
        
        
    return (target, source)

    
masterdocubld  = Builder(action = docu_master, emitter = docu_emitter)

env.Append(BUILDERS={'CopyAll': cp_recbld, 'L2H': l2h,
                     'SubstInstallAs': substinstbld,
                     'CopyPyDoc':cp_pydocbld})
env.Append(BUILDERS={'DocuMaster': masterdocubld})



def spec_builder(target, source, env):

    substitute_install(target, source, env)
    return None

specbld = Builder(action = spec_builder)

def rpmemitter(target, source, env):
    rpm_arch =  shell_output("rpm", "-E", "%_arch")
    target = [RPMPath('RPMS', rpm_arch, target[0].name + '.' + rpm_arch + '.rpm')]
    return (target, source)

def srpmemitter(target, source, env):
    target = [RPMPath('SRPMS', target[0].name + '.src.rpm')]
    return (target, source)   
    
def generate_rpmbuilder(rpmopts, emitt = rpmemitter):
    return Builder(action = "rpmbuild " + rpmopts + " --define='_topdir " +
                   Dir(RPMPath()).abspath +  "' $SOURCE", emitter = emitt)

srpmbld  = generate_rpmbuilder('-bs', srpmemitter)
rpmbld  = generate_rpmbuilder('--define="jobs ' + str(GetOption('num_jobs')) +
                              '" -bb', rpmemitter)

# debbuilder is very experimental, we ignore dependencies currently (-d)
debbld = Builder(action = "dpkg-buildpackage -d -rfakeroot")
    
env.Append(BUILDERS={'SpecBuilder': specbld,
                     'RPMBuilder': rpmbld, 'SRPMBuilder': srpmbld,
                     'DebBuilder': debbld})


version4tex = env.Command([DocPath('tutorial/versionnumber')],
                          DocPath('tutorial/versionnumber.in'),
                          preprocessed_substitute)

tutorial_srcs = [DocPath('tutorial/tutorial.tex')] + version4tex + glob(DocPath('tutorial/*.tex'))
if have_l2h:
    tutorial = env.L2H(env.Dir(DocPath('tutorial/tutorial')), tutorial_srcs)
else:
    if have_t4h :
        tutorial = env.TeXToHt(env.Dir(DocPath('tutorial/tutorial')),
                               tutorial_srcs)
    
# Clean, even, if L2H/TexToHt are not available anymore
env.Clean(DocPath('tutorial'), DocPath('tutorial/tutorial'))

documastersubdirs = "tutorial/tutorial python"
if HAVE_DOXYGEN:
    documastersubdirs += " c++"

env.DocuMaster(DocPath('index.html'), [DocPath('index.html.in')] + [
    env.Dir(DocPath(srcs)) for srcs in Split(documastersubdirs) ] + [
    env.Dir('Cudd/cudd/doc')])  

pbrpmname = pboriname + '-' + pboriversion + "." + pborirelease 

if rpm_generation:
    # Some file servers use invalid group-ids, so change to current gid
    def correctgid(target, source, env):
        os.chown(target[0].path, -1, os.getgid())

    rpmsrcs = FinalizeNonExecs(env.DistTar(RPMPath('SOURCES',
                                                   pbrpmname),
                                           allsrcs, DISTTAR_FORMAT = 'bz2'))
    env.AddPostAction(rpmsrcs, correctgid)
    
    pbspec = FinalizeNonExecs(env.SpecBuilder(SpecsPath(pboriname +'.spec'),
                                              RPMPath('PolyBoRi.spec.in')))

        
    env.AddPostAction(pbspec, correctgid)

    env.AlwaysBuild(pbspec)
    env.Alias('prepare-rpm', pbspec)
    env.Alias('prepare-rpm', rpmsrcs)
    
    pbsrpm = env.SRPMBuilder(RPMPath('SRPMS', pbrpmname),
                             pbspec + rpmsrcs)
    env.AlwaysBuild(pbsrpm)
    pbrpm = env.RPMBuilder(RPMPath('RPMS', pbrpmname ),
                           pbspec + rpmsrcs)

    def provide_builddir(target, source, env):
        if not path.exists(RPMPath('BUILD')):
            env.Execute(Mkdir(RPMPath('BUILD')))
    
    env.AddPreAction(pbrpm, provide_builddir)
    env.AlwaysBuild(pbrpm)
    env.Alias('srpm', pbsrpm)
    env.Alias('rpm', pbrpm)



if prepare_deb or generate_deb:
    debsrc = env.SubstInstallAs(DebInstPath('changelog'),
                                DebPath('changelog.in'))


    debsrc += FinalizeNonExecs(env.SubstInstallAs(DebInstPath('control.in'),
                                                  DebPath('control.in')))
    env['cdbs'] = 'cdbs (>= 0.4.23-1.1), debhelper (>= 5), quilt, patchutils (>= 0.2.25), cdbs (>= 0.4.27-1)'


    debsrc += FinalizeNonExecs(env.Command([DebInstPath('control')],
                                           DebPath('control.in'),
                                           preprocessed_substitute))
        
    for src in ['rules', 'compat', 'copyright', 
                'libpolybori-dev.install',  'python-polybori.install'] :
        debsrc += env.Install(DebInstPath(), DebPath(src))
        
    debsrc += env.InstallAs(DebInstPath('libpolybori-' + pboriversion +
                                        '.' + pborirelease   +'-0.install'),
                            DebPath('libpolybori0.install'))
        
    env.Alias('prepare-debian', DebInstPath())
    env.Clean(DebInstPath(), DebInstPath())
    deb_arch =  shell_output("dpkg-architecture", "-qDEB_HOST_GNU_CPU")
    pbdeb = env.DebBuilder(path.join('..', debname + '-' + pborirelease +
                                     '.' + deb_arch + '.deb'), debsrc)
    
    env.AlwaysBuild(env.Alias('deb', pbdeb))    
    

def GeneratePyc(sources):
    results = []
    for src in sources:
        (fbase, fext) = path.splitext(src.name)
        if (fext == '.py') :
            cmdline = """$PYTHON -c "import py_compile; """
            cmdline +=  """py_compile.compile('""" + str(src) + """')" """ 
            results += env.Command(str(src) +'c', file, cmdline)

        env.Depends(results, sources)
    return results


       
# Installation precedure for end users
if 'install' in COMMAND_LINE_TARGETS:
    # Setting umask for newly generated directories
    try:
        umask = os.umask(022)
        print 'setting umask to 022 (was 0%o)' % umask
    except OSError:     # ignore on systems that don't support umask
        pass
    
    InstPath = PathJoiner(env['INSTALLDIR'])
    InstExecPath = PathJoiner(env['EPREFIX'])
    InstDocPath = PathJoiner(env['DOCDIR'])
    InstManPath = PathJoiner(env['MANDIR'])
    
    for inst_path in [InstPath(), InstExecPath(), InstDocPath(), InstPyPath(),
                      InstManPath()]:
        env.Alias('install', inst_path)
    env.Install(InstManPath('man1'), DocPath('man/ipbori.1'))
    env.Install(InstManPath('man1'), DocPath('man/PolyGUI.1'))
    
    # Executables and shared libraries to be installed
    so_pyfiles = []

    if env['PLATFORM']=="darwin":

        if env['INSTALL_NAME_DIR'] is not None:
            name = os.path.join(env['INSTALL_NAME_DIR'], 
                                "${TARGET.name}")
            for elt in dylibs_inst:
                env.AddPostAction(elt, 
                                  "install_name_tool -id " + name + " $TARGET")

    if HAVE_PYTHON_EXTENSION:
        pypb_inst = env.Install(InstPyPath("polybori/dynamic"), pypb)
        env.Depends(pypb_inst, dylibs_inst + dylibs_readable_inst)
        so_pyfiles += pypb_inst

    pyfiles = []
    env['GUIPYPREFIX'] = env.relpath(InstPath(GUIPath()),
                                     '$PYINSTALLPREFIX')
    
    for instfile in [ IPBPath('ipbori') ]:
        FinalizeExecs(env.SubstInstallAs(InstPath(instfile), instfile))

    for instfile in [ GUIPath('PolyGUI') ]:
        FinalizeExecs(env.SubstInstallAs(InstPath(instfile), instfile))
        
    for instfile in [GUIPath('cnf2ideal.py')]:
        pyfiles += env.InstallAs(InstPath(instfile), instfile)
        
    for instfile in [ GUIPath('polybori.png') ]:
        env.InstallAs(InstPath(instfile), instfile)
    
    # Copy c++ documentation
    if HAVE_DOXYGEN:
        cxxdocinst = CopyAll(InstDocPath('c++'),
                             DocPath('c++/html'), env) 
        env.Depends(cxxdocinst, cxxdocu)
        env.Clean(cxxdocinst, cxxdocinst)

    htmlpatterns = Split("*.html *.css *.png *gif *.jpg")

    # Copy python documentation
    pydocuinst = env.CopyPyDoc(env.Dir(InstDocPath('python')),
                               env.Dir(DocPath('python')))

    env.Depends(pydocuinst, pydocu)
    env.Clean(pydocuinst, pydocuinst)

    # Copy Cudd documentation
    CopyAll(InstDocPath('cudd'), 'Cudd/cudd/doc', env) 
    CopyAll(InstDocPath('cudd/icons'), 'Cudd/cudd/doc/icons', env)

    # Copy Tutorial
    if have_l2h or have_t4h :
        env.CopyAll(env.Dir(InstDocPath('tutorial')),
                    env.Dir(DocPath('tutorial/tutorial')),
                    COPYALL_PATTERNS = htmlpatterns)

    # Generate html master
    FinalizeNonExecs(env.DocuMaster(InstDocPath('index.html'),
                                    [DocPath('index.html.in')] + [ 
        env.Dir(InstDocPath(srcs)) for srcs in Split("""tutorial python
        c++ cudd""") ] ))

    # Non-executables to be installed
    pyfile_srcs = glob(PyRootPath('polybori/*.py'))

    if (float(pyconf.version) < 2.5): # removing advanced functionality
        pyfile_srcs.remove(PyRootPath('polybori/context.py'))
                       
    for instfile in pyfile_srcs :
        targetfile = InstPyPath(env.relpath(PyRootPath(), instfile))
        pyfiles += env.InstallAs(targetfile, instfile)

    if HAVE_PYTHON_EXTENSION:
        pyfiles +=  env.Install(InstPyPath("polybori/dynamic"), pypb_init_py)

    if HAVE_PYTHON_EXTENSION or extern_python_ext:
        cmdline = """$PYTHON -c "import compileall; compileall.compile_dir('"""
        cmdline += InstPyPath('polybori') + """', ddir = ''); """ 
        cmdline += """compileall.compile_dir('"""+ InstPath(GUIPath())
        cmdline += """', ddir='')" """
        FinalizeNonExecs(env.Command([file1.path + 'c' for file1 in pyfiles],
                                     pyfiles, cmdline))

    env['PYINSTALLPREFIX'] = env.subst('$PYINSTALLPREFIX')
    env['RELATIVEPYPREFIX'] = env.relpath(InstPath(IPBPath()),
                                          '$PYINSTALLPREFIX')       

    # Symlink from executable into bin directory
    ipboribin = env.SymLink(InstExecPath('ipbori'),
                            InstPath(IPBPath('ipbori')))


    guibin = env.SymLink(InstExecPath('PolyGUI'),
                         InstPath(GUIPath('PolyGUI')))
    
    env.AlwaysBuild(ipboribin)   
    env.Alias('install', ipboribin)
    env.AlwaysBuild(guibin)   
    env.Alias('install', guibin)

    # we dump the flags for reuse by other developers
    conffilename = env['CONFFILE']
    if conffilename:
        def build_conffile(target, source, env):
            opts.Save(target[0].path, env)
            return None

        conffile = env.Command(conffilename, 'SConstruct', build_conffile)
        env.AlwaysBuild(conffile)
        env.Alias('install', conffile)
    

env.Alias('prepare-devel', dylibs + stlibs + readabledevellibs)
env.Alias('prepare-install', [pyroot, DocPath()])


Default(BuildPath())

# Generate usage for scons -h here
# (PYTHONSITE is already evaluated, but not python-specific paths)
Help(opts.GenerateHelpText(env))

if 'dump_default' in COMMAND_LINE_TARGETS:
  print defaultenv.Dump()

if 'dump' in COMMAND_LINE_TARGETS:
  print env.Dump()

env.Alias('dump', 'SConstruct')
env.Alias('dump_default', 'SConstruct')

