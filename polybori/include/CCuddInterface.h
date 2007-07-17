// -*- c++ -*-
//*****************************************************************************
/** @file CCuddInterface.h
 *
 * @author Alexander Dreyer
 * @date 2007-07-05
 *
 * 
 *
 * @par Copyright:
 *   (c) 2007 by
 *   Dep. of Mathematics, Kaiserslautern University of Technology and @n
 *   Fraunhofer Institute for Industrial Mathematics (ITWM)
 *   D-67663 Kaiserslautern, Germany
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.5  2007/07/17 15:56:59  dreyer
 * ADD: header file for CCuddZDD; clean-up
 *
 * Revision 1.4  2007/07/13 15:05:23  dreyer
 * CHANGE: cleaned up once more
 *
 * Revision 1.3  2007/07/12 15:32:31  dreyer
 * CHANGE: cleanup using preprocessor meta-programming
 *
 * Revision 1.2  2007/07/10 14:53:27  dreyer
 * CHANGE: clean-up
 *
 * Revision 1.1  2007/07/06 14:04:21  dreyer
 * ADD: newly written C++_interface for Cudd
 *
 * @endverbatim
**/
//*****************************************************************************


// include basic definitions

#include "CCuddZDD.h"

#ifndef CCuddInterface_h_
#define CCuddInterface_h_

BEGIN_NAMESPACE_PBORI

#define PB_CUDDMGR_READ(count, data, funcname) data funcname() const { \
  return BOOST_PP_CAT(Cudd_, funcname)(getManager()); }

#define PB_CUDDMGR_SWITCH(count, data, funcname) void funcname() { \
    BOOST_PP_CAT(Cudd_, funcname)(getManager()); }

#define PB_CUDDMGR_SET(count, data, funcname)  void funcname(data arg) { \
    BOOST_PP_CAT(Cudd_, funcname)(getManager(), arg); }

class CCuddInterface {
  friend class CCuddDD;
  friend class CCuddZDD;

public:
  typedef CCuddZDD::mgr_ptr mgr_ptr;
  mgr_ptr p;
  typedef CCuddInterface self;
  typedef int idx_type;
  typedef unsigned int size_type;
  typedef CCuddZDD dd_type;

  typedef DdNode* node_type;

  typedef node_type (*unary_int_function)(DdManager *, int);
  typedef node_type (*void_function)(DdManager *);
  typedef self tmp_ref;

  typedef boost::scoped_array<node_type> node_array;

  CCuddInterface(size_type numVars = 0,
                 size_type numVarsZ = 0,
                 size_type numSlots = CUDD_UNIQUE_SLOTS,
                 size_type cacheSize = CUDD_CACHE_SLOTS,
                 unsigned long maxMemory = 0):
    p (new CCuddCore(numVars, numVarsZ, numSlots, cacheSize, maxMemory)) {
  }

  CCuddInterface(const CCuddInterface& x):  p(x.p) {}

  CCuddInterface(mgr_ptr rhs): p(rhs) {};

  ~CCuddInterface() {}

  PFC setHandler(PFC newHandler) {
    PFC oldHandler = p->errorHandler;
    p->errorHandler = newHandler;
    return oldHandler;
  }

  PFC getHandler() const {  return p->errorHandler; }

  DdManager *getManager() const {return p->manager;}
  mgr_ptr managerCore() const {return p;}
  
  void makeVerbose() {p->verbose = 1;}
  void makeTerse() {p->verbose = 0;}
  int isVerbose() const {return p->verbose;}


  void checkReturnValue(const node_type result) const {
    checkReturnValue(result != NULL);
  }
  void checkReturnValue(const int result) const {
    if UNLIKELY(result == 0) {
      typedef handle_error<CUDD_MEMORY_OUT> handle_type;
      if ( !handle_type::found(Cudd_ReadErrorCode(getManager())) )
        defaultError(cudd_error_traits<CUDD_INTERNAL_ERROR>()());
    }
  } 

  CCuddInterface& operator=(const CCuddInterface& right) {
    p = right.p;
    return *this;
  }

  void info() const { checkedResult(Cudd_PrintInfo(getManager(),stdout)); }

  CCuddZDD zddVar(idx_type idx) const { return apply(Cudd_zddIthVar, idx); }
  CCuddZDD zddOne(idx_type iMax) const  { return apply(Cudd_ReadZddOne, iMax); }
  CCuddZDD zddZero() const { return apply(Cudd_ReadZero); }

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_SET, size_type, 
    (SetMinHit)(SetLooseUpTo)(SetMaxCacheHard)(SetMaxLive) )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_SET, int, 
    (SetSiftMaxVar)(SetSiftMaxSwap)(SetRecomb)(SetSymmviolation)
    (SetArcviolation)(SetPopulationSize)(SetNumberXovers)
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_SET, FILE*, (SetStdout)(SetStderr))

  PB_CUDDMGR_SET(BOOST_PP_NIL, Cudd_ReorderingType, AutodynEnableZdd)
  PB_CUDDMGR_SET(BOOST_PP_NIL, unsigned long, SetMaxMemory)
  PB_CUDDMGR_SET(BOOST_PP_NIL, double, SetMaxGrowth)
  PB_CUDDMGR_SET(BOOST_PP_NIL, MtrNode*, SetZddTree)

  int ReorderingStatusZdd(Cudd_ReorderingType * method) const {
    return Cudd_ReorderingStatusZdd(getManager(), method);
  }
  PB_CUDDMGR_READ(BOOST_PP_NIL, int, zddRealignmentEnabled);

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_SWITCH, BOOST_PP_NIL, 
    (zddRealignEnable)(zddRealignDisable)
    (AutodynDisableZdd)(FreeZddTree)
    (EnableGarbageCollection)(DisableGarbageCollection)
    (TurnOnCountDead)(TurnOffCountDead)(ClearErrorCode)  
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, double,
    (ReadCacheUsedSlots)(ReadCacheLookUps)(ReadCacheHits) 
    (ReadSwapSteps)(ReadMaxGrowth)(AverageDistance)
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, size_type,
    (ReadCacheSlots)(ReadMinHit)(ReadLooseUpTo)(ReadMaxCache)
    (ReadMaxCacheHard)(ReadSlots)(ReadKeys)(ReadDead)(ReadMinDead)
    (ReadNextReordering)(ReadMaxLive)
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, int,
    (ReadZddSize)(ReadReorderings)(ReadSiftMaxVar)
    (ReadSiftMaxSwap)(ReadGarbageCollections)(GarbageCollectionEnabled)
    (DeadAreCounted)(ReadRecomb)
    (ReadPopulationSize)(ReadSymmviolation)(ReadArcviolation)
    (ReadNumberXovers)(ReorderingReporting)(ReadErrorCode)
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, long,
    (ReadReorderingTime)(ReadGarbageCollectionTime)
    (ReadPeakNodeCount)(zddReadNodeCount)
  )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, unsigned long, 
    (ReadMemoryInUse)(ReadMaxMemory) )

  BOOST_PP_SEQ_FOR_EACH(PB_CUDDMGR_READ, FILE*, (ReadStdout)(ReadStderr))

  PB_CUDDMGR_READ(BOOST_PP_NIL, MtrNode*, ReadZddTree)

  int ReadPermZdd(int i) const { return Cudd_ReadPermZdd(getManager(), i); }

  int ReadInvPermZdd(int i) const { 
    return Cudd_ReadInvPermZdd(getManager(), i); 
  }

  void AddHook(DD_HFP f, Cudd_HookType where) { 
    checkedResult(Cudd_AddHook(getManager(), f, where));
  }
  void RemoveHook(DD_HFP f, Cudd_HookType where) { 
    checkedResult(Cudd_RemoveHook(getManager(), f, where)); 
  }
  int IsInHook(DD_HFP f, Cudd_HookType where) const { 
    return Cudd_IsInHook(getManager(), f, where); 
  }
  void EnableReorderingReporting() { 
    checkedResult(Cudd_EnableReorderingReporting(getManager())); 
  }
  void DisableReorderingReporting() { 
    checkedResult(Cudd_DisableReorderingReporting(getManager())); 
  }

  void DebugCheck(){ checkedResult(Cudd_DebugCheck(getManager())); }
  void CheckKeys(){ checkedResult(Cudd_CheckKeys(getManager())); }
  void PrintLinear() { checkedResult(Cudd_PrintLinear(getManager())); }

  int ReadLinear(int x, int y) { return Cudd_ReadLinear(getManager(), x, y); }

  size_type Prime(size_type pr) const { return Cudd_Prime(pr); }

  void PrintVersion(FILE * fp) const { cout.flush(); Cudd_PrintVersion(fp); }

  MtrNode* MakeZddTreeNode(size_type low, size_type size, size_type type) {
    return Cudd_MakeZddTreeNode(getManager(), low, size, type);
  }
  void zddPrintSubtable() const{ 
    cout.flush();
    Cudd_zddPrintSubtable(getManager());
  }

  void zddReduceHeap(Cudd_ReorderingType heuristic, int minsize) {
    checkedResult(Cudd_zddReduceHeap(getManager(), heuristic, minsize));
  }
  void zddShuffleHeap(int * permutation) { 
    checkedResult(Cudd_zddShuffleHeap(getManager(), permutation));
  }
  void zddSymmProfile(int lower, int upper) const {
    Cudd_zddSymmProfile(getManager(), lower, upper);
  }

  int SharingSize(dd_type* nodes, int nlen) const {
    node_array nodeArray(new node_type[nlen]);
    std::transform(nodes, nodes + nlen, nodeArray.get(), get_node<dd_type>());
    return checkedResult(Cudd_SharingSize(nodeArray.get(), nlen));
  }

protected:

  dd_type checkedResult(node_type result) const  { 
    checkReturnValue(result);
    return dd_type(managerCore(), result);
  }
  idx_type checkedResult(idx_type result) const  { 
    checkReturnValue(result);
    return result;
  }
  dd_type apply(unary_int_function func, idx_type idx) const  { 
    return checkedResult(func(getManager(), idx) );
  }
  dd_type apply(void_function func) const { 
    return checkedResult(func(getManager()) );
  }
}; // CCuddInterface


#undef PB_CUDDMGR_READ
#undef PB_CUDDMGR_SWITCH
#undef PB_CUDDMGR_SET

END_NAMESPACE_PBORI

#endif


