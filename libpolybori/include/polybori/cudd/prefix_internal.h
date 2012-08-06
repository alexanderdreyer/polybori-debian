// -*- c++ -*-
//*****************************************************************************
/** @file prefix_internal.h 
 *
 * @author Alexander Dreyer
 * @date 2012-02-15
 *
 * This file includes some macro definitions
 *
 * @note It is intended to be included by the @c .c files of the CUDD fork
 * coming with PolyBoRi only. It prefixes CUDD's symbols with @c pbori_ to avoid
 * name clashing and errorous linking of third party code to @c libpolybori 
 * (instead of @c libcudd).
 *
 * @par Copyright:
 *   (c) 2012 by The PolyBoRi Team
 *
**/
//*****************************************************************************

#ifndef polybori_cudd_prefix_internal_h_
#define polybori_cudd_prefix_internal_h_

#ifndef PBORI_USE_ORIGINAL_CUDD
#define Cudd_IsNonConstant pbori_Cudd_IsNonConstant
#define Cudd_ReadStartTime pbori_Cudd_ReadStartTime
#define Cudd_SetStartTime pbori_Cudd_SetStartTime
#define Cudd_ReadTimeLimit pbori_Cudd_ReadTimeLimit
#define Cudd_SetTimeLimit pbori_Cudd_SetTimeLimit
#define Cudd_IncreaseTimeLimit pbori_Cudd_IncreaseTimeLimit
#define Cudd_UnsetTimeLimit pbori_Cudd_UnsetTimeLimit
#define Cudd_TimeLimited pbori_Cudd_TimeLimited
#define Cudd_AutodynDisable pbori_Cudd_AutodynDisable
#define Cudd_ReorderingStatus pbori_Cudd_ReorderingStatus
#define Cudd_AutodynEnableZdd pbori_Cudd_AutodynEnableZdd
#define Cudd_AutodynDisableZdd pbori_Cudd_AutodynDisableZdd
#define Cudd_ReorderingStatusZdd pbori_Cudd_ReorderingStatusZdd
#define Cudd_zddRealignmentEnabled pbori_Cudd_zddRealignmentEnabled
#define Cudd_zddRealignEnable pbori_Cudd_zddRealignEnable
#define Cudd_zddRealignDisable pbori_Cudd_zddRealignDisable
#define Cudd_bddRealignmentEnabled pbori_Cudd_bddRealignmentEnabled
#define Cudd_bddRealignEnable pbori_Cudd_bddRealignEnable
#define Cudd_bddRealignDisable pbori_Cudd_bddRealignDisable
#define Cudd_ReadOne pbori_Cudd_ReadOne
#define Cudd_ReadZddOne pbori_Cudd_ReadZddOne
#define Cudd_ReadZero pbori_Cudd_ReadZero
#define Cudd_ReadLogicZero pbori_Cudd_ReadLogicZero
#define Cudd_ReadPlusInfinity pbori_Cudd_ReadPlusInfinity
#define Cudd_ReadMinusInfinity pbori_Cudd_ReadMinusInfinity
#define Cudd_ReadBackground pbori_Cudd_ReadBackground
#define Cudd_SetBackground pbori_Cudd_SetBackground
#define Cudd_ReadCacheSlots pbori_Cudd_ReadCacheSlots
#define Cudd_ReadCacheUsedSlots pbori_Cudd_ReadCacheUsedSlots
#define Cudd_ReadCacheLookUps pbori_Cudd_ReadCacheLookUps
#define Cudd_ReadCacheHits pbori_Cudd_ReadCacheHits
#define Cudd_ReadRecursiveCalls pbori_Cudd_ReadRecursiveCalls
#define Cudd_ReadMinHit pbori_Cudd_ReadMinHit
#define Cudd_SetMinHit pbori_Cudd_SetMinHit
#define Cudd_ReadLooseUpTo pbori_Cudd_ReadLooseUpTo
#define Cudd_SetLooseUpTo pbori_Cudd_SetLooseUpTo
#define Cudd_ReadMaxCache pbori_Cudd_ReadMaxCache
#define Cudd_ReadMaxCacheHard pbori_Cudd_ReadMaxCacheHard
#define Cudd_SetMaxCacheHard pbori_Cudd_SetMaxCacheHard
#define Cudd_ReadSize pbori_Cudd_ReadSize
#define Cudd_ReadZddSize pbori_Cudd_ReadZddSize
#define Cudd_ReadSlots pbori_Cudd_ReadSlots
#define Cudd_ReadUsedSlots pbori_Cudd_ReadUsedSlots
#define Cudd_ReadKeys pbori_Cudd_ReadKeys
#define Cudd_ReadDead pbori_Cudd_ReadDead
#define Cudd_ReadMinDead pbori_Cudd_ReadMinDead
#define Cudd_ReadReorderings pbori_Cudd_ReadReorderings
#define Cudd_ReadMaxReorderings pbori_Cudd_ReadMaxReorderings
#define Cudd_SetMaxReorderings pbori_Cudd_SetMaxReorderings
#define Cudd_ReadReorderingTime pbori_Cudd_ReadReorderingTime
#define Cudd_ReadGarbageCollections pbori_Cudd_ReadGarbageCollections
#define Cudd_ReadGarbageCollectionTime pbori_Cudd_ReadGarbageCollectionTime
#define Cudd_ReadNodesFreed pbori_Cudd_ReadNodesFreed
#define Cudd_ReadNodesDropped pbori_Cudd_ReadNodesDropped
#define Cudd_ReadUniqueLookUps pbori_Cudd_ReadUniqueLookUps
#define Cudd_ReadUniqueLinks pbori_Cudd_ReadUniqueLinks
#define Cudd_ReadSiftMaxVar pbori_Cudd_ReadSiftMaxVar
#define Cudd_SetSiftMaxVar pbori_Cudd_SetSiftMaxVar
#define Cudd_ReadSiftMaxSwap pbori_Cudd_ReadSiftMaxSwap
#define Cudd_SetSiftMaxSwap pbori_Cudd_SetSiftMaxSwap
#define Cudd_ReadMaxGrowth pbori_Cudd_ReadMaxGrowth
#define Cudd_SetMaxGrowth pbori_Cudd_SetMaxGrowth
#define Cudd_ReadMaxGrowthAlternate pbori_Cudd_ReadMaxGrowthAlternate
#define Cudd_SetMaxGrowthAlternate pbori_Cudd_SetMaxGrowthAlternate
#define Cudd_ReadReorderingCycle pbori_Cudd_ReadReorderingCycle
#define Cudd_SetReorderingCycle pbori_Cudd_SetReorderingCycle
#define Cudd_NodeReadIndex pbori_Cudd_NodeReadIndex
#define Cudd_ReadPerm pbori_Cudd_ReadPerm
#define Cudd_ReadPermZdd pbori_Cudd_ReadPermZdd
#define Cudd_ReadInvPerm pbori_Cudd_ReadInvPerm
#define Cudd_ReadInvPermZdd pbori_Cudd_ReadInvPermZdd
#define Cudd_ReadVars pbori_Cudd_ReadVars
#define Cudd_ReadEpsilon pbori_Cudd_ReadEpsilon
#define Cudd_SetEpsilon pbori_Cudd_SetEpsilon
#define Cudd_ReadGroupcheck pbori_Cudd_ReadGroupcheck
#define Cudd_SetGroupcheck pbori_Cudd_SetGroupcheck
#define Cudd_GarbageCollectionEnabled pbori_Cudd_GarbageCollectionEnabled
#define Cudd_EnableGarbageCollection pbori_Cudd_EnableGarbageCollection
#define Cudd_DisableGarbageCollection pbori_Cudd_DisableGarbageCollection
#define Cudd_DeadAreCounted pbori_Cudd_DeadAreCounted
#define Cudd_TurnOnCountDead pbori_Cudd_TurnOnCountDead
#define Cudd_TurnOffCountDead pbori_Cudd_TurnOffCountDead
#define Cudd_ReadRecomb pbori_Cudd_ReadRecomb
#define Cudd_SetRecomb pbori_Cudd_SetRecomb
#define Cudd_ReadSymmviolation pbori_Cudd_ReadSymmviolation
#define Cudd_SetSymmviolation pbori_Cudd_SetSymmviolation
#define Cudd_ReadArcviolation pbori_Cudd_ReadArcviolation
#define Cudd_SetArcviolation pbori_Cudd_SetArcviolation
#define Cudd_ReadPopulationSize pbori_Cudd_ReadPopulationSize
#define Cudd_SetPopulationSize pbori_Cudd_SetPopulationSize
#define Cudd_ReadNumberXovers pbori_Cudd_ReadNumberXovers
#define Cudd_SetNumberXovers pbori_Cudd_SetNumberXovers
#define Cudd_ReadOrderRandomization pbori_Cudd_ReadOrderRandomization
#define Cudd_SetOrderRandomization pbori_Cudd_SetOrderRandomization
#define Cudd_ReadMemoryInUse pbori_Cudd_ReadMemoryInUse
#define Cudd_ReadPeakNodeCount pbori_Cudd_ReadPeakNodeCount
#define Cudd_ReadPeakLiveNodeCount pbori_Cudd_ReadPeakLiveNodeCount
#define Cudd_zddReadNodeCount pbori_Cudd_zddReadNodeCount
#define Cudd_IsInHook pbori_Cudd_IsInHook
#define Cudd_ReorderingReporting pbori_Cudd_ReorderingReporting
#define Cudd_StdPreReordHook pbori_Cudd_StdPreReordHook
#define Cudd_ReadErrorCode pbori_Cudd_ReadErrorCode
#define Cudd_ClearErrorCode pbori_Cudd_ClearErrorCode
#define Cudd_ReadStdout pbori_Cudd_ReadStdout
#define Cudd_SetStdout pbori_Cudd_SetStdout
#define Cudd_ReadStderr pbori_Cudd_ReadStderr
#define Cudd_SetStderr pbori_Cudd_SetStderr
#define Cudd_ReadNextReordering pbori_Cudd_ReadNextReordering
#define Cudd_SetNextReordering pbori_Cudd_SetNextReordering
#define Cudd_ReadSwapSteps pbori_Cudd_ReadSwapSteps
#define Cudd_ReadMaxLive pbori_Cudd_ReadMaxLive
#define Cudd_SetMaxLive pbori_Cudd_SetMaxLive
#define Cudd_ReadMaxMemory pbori_Cudd_ReadMaxMemory
#define Cudd_SetMaxMemory pbori_Cudd_SetMaxMemory
#define Cudd_UpdateTimeLimit pbori_Cudd_UpdateTimeLimit
#define Cudd_RemoveHook pbori_Cudd_RemoveHook
#define Cudd_DisableReorderingReporting pbori_Cudd_DisableReorderingReporting
#define Cudd_StdPostReordHook pbori_Cudd_StdPostReordHook
#define Cudd_ReadNodeCount pbori_Cudd_ReadNodeCount
#define Cudd_ExpectedUsedSlots pbori_Cudd_ExpectedUsedSlots
#define Cudd_PrintInfo pbori_Cudd_PrintInfo
#define Cudd_AutodynEnable pbori_Cudd_AutodynEnable
#define Cudd_addConst pbori_Cudd_addConst
#define Cudd_zddIthVar pbori_Cudd_zddIthVar
#define Cudd_RecursiveDerefZdd pbori_Cudd_RecursiveDerefZdd
#define Cudd_ResetStartTime pbori_Cudd_ResetStartTime
#define Cudd_ReadElapsedTime pbori_Cudd_ReadElapsedTime
#define Cudd_AddHook pbori_Cudd_AddHook
#define Cudd_EnableReorderingReporting pbori_Cudd_EnableReorderingReporting
#define Cudd_Quit pbori_Cudd_Quit
#define Cudd_Init pbori_Cudd_Init
#define Cudd_RecursiveDeref pbori_Cudd_RecursiveDeref
#define Cudd_Ref pbori_Cudd_Ref
#define Cudd_IterDerefBdd pbori_Cudd_IterDerefBdd
#define Cudd_DelayedDerefBdd pbori_Cudd_DelayedDerefBdd
#define Cudd_Deref pbori_Cudd_Deref
#define Cudd_CheckZeroRef pbori_Cudd_CheckZeroRef
#define Cudd_Prime pbori_Cudd_Prime
#define Cudd_zddDivideF pbori_Cudd_zddDivideF
#define Cudd_zddDivide pbori_Cudd_zddDivide
#define Cudd_zddWeakDiv pbori_Cudd_zddWeakDiv
#define Cudd_zddWeakDivF pbori_Cudd_zddWeakDivF
#define Cudd_zddUnateProduct pbori_Cudd_zddUnateProduct
#define Cudd_zddProduct pbori_Cudd_zddProduct
#define Cudd_zddSubset0 pbori_Cudd_zddSubset0
#define Cudd_zddSubset1 pbori_Cudd_zddSubset1
#define Cudd_zddChange pbori_Cudd_zddChange
#define Cudd_zddDiff pbori_Cudd_zddDiff
#define Cudd_zddIntersect pbori_Cudd_zddIntersect
#define Cudd_zddUnion pbori_Cudd_zddUnion
#define Cudd_zddDiffConst pbori_Cudd_zddDiffConst
#define Cudd_zddIte pbori_Cudd_zddIte

#define cuddClearDeathRow pbori_cuddClearDeathRow
#define cuddCacheProfile pbori_cuddCacheProfile
#define cuddUniqueConst pbori_cuddUniqueConst
#define cuddUniqueInterZdd pbori_cuddUniqueInterZdd
#define cuddCacheInsert pbori_cuddCacheInsert
#define cuddCacheInsert2 pbori_cuddCacheInsert2
#define cuddCacheInsert1 pbori_cuddCacheInsert1
#define cuddCacheFlush pbori_cuddCacheFlush
#define cuddComputeFloorLog2 pbori_cuddComputeFloorLog2
#define cuddCacheResize pbori_cuddCacheResize
#define cuddConstantLookup pbori_cuddConstantLookup
#define cuddCacheLookup1Zdd pbori_cuddCacheLookup1Zdd
#define cuddReclaimZdd pbori_cuddReclaimZdd
#define cuddCacheLookup2Zdd pbori_cuddCacheLookup2Zdd
#define cuddCacheLookupZdd pbori_cuddCacheLookupZdd
#define cuddCacheLookup1 pbori_cuddCacheLookup1
#define cuddReclaim pbori_cuddReclaim
#define cuddCacheLookup2 pbori_cuddCacheLookup2
#define cuddCacheLookup pbori_cuddCacheLookup
#define cuddInitCache pbori_cuddInitCache
#define cuddZddFreeUniv pbori_cuddZddFreeUniv
#define cuddFreeTable pbori_cuddFreeTable
#define cuddZddInitUniv pbori_cuddZddInitUniv
#define cuddInitTable pbori_cuddInitTable
#define cuddUniqueInter pbori_cuddUniqueInter
#define cuddLocalCacheClearDead pbori_cuddLocalCacheClearDead
#define cuddHashTableLookup pbori_cuddHashTableLookup
#define cuddHashTableLookup1 pbori_cuddHashTableLookup1
#define cuddHashTableGenericLookup pbori_cuddHashTableGenericLookup
#define cuddHashTableLookup2 pbori_cuddHashTableLookup2
#define cuddHashTableLookup3 pbori_cuddHashTableLookup3
#define cuddLocalCacheClearAll pbori_cuddLocalCacheClearAll
#define cuddHashTableGenericQuit pbori_cuddHashTableGenericQuit
#define cuddLocalCacheQuit pbori_cuddLocalCacheQuit
#define cuddHashTableQuit pbori_cuddHashTableQuit
#define cuddLocalCacheInsert pbori_cuddLocalCacheInsert
#define cuddLocalCacheLookup pbori_cuddLocalCacheLookup
#define cuddHashTableInsert pbori_cuddHashTableInsert
#define cuddHashTableInit pbori_cuddHashTableInit
#define cuddLocalCacheInit pbori_cuddLocalCacheInit
#define cuddHashTableInsert3 pbori_cuddHashTableInsert3
#define cuddHashTableInsert2 pbori_cuddHashTableInsert2
#define cuddHashTableGenericInsert pbori_cuddHashTableGenericInsert
#define cuddHashTableInsert1 pbori_cuddHashTableInsert1
#define cuddIsInDeathRow pbori_cuddIsInDeathRow
#define cuddTimesInDeathRow pbori_cuddTimesInDeathRow
#define cuddShrinkDeathRow pbori_cuddShrinkDeathRow
#define cuddSlowTableGrowth pbori_cuddSlowTableGrowth
#define cuddResizeTableZdd pbori_cuddResizeTableZdd
#define cuddGarbageCollect pbori_cuddGarbageCollect
#define cuddRehash pbori_cuddRehash
#define cuddAllocNode pbori_cuddAllocNode
#define cuddZddGetPosVarIndex pbori_cuddZddGetPosVarIndex
#define cuddZddGetNode pbori_cuddZddGetNode
#define cuddZddGetNegVarIndex pbori_cuddZddGetNegVarIndex
#define cuddZddGetPosVarLevel pbori_cuddZddGetPosVarLevel
#define cuddZddGetNegVarLevel pbori_cuddZddGetNegVarLevel
#define cuddZddGetCofactors2 pbori_cuddZddGetCofactors2
#define cuddZddSubset1 pbori_cuddZddSubset1
#define cuddZddSubset0 pbori_cuddZddSubset0
#define cuddZddGetCofactors3 pbori_cuddZddGetCofactors3
#define cuddZddDivideF pbori_cuddZddDivideF
#define cuddZddIntersect pbori_cuddZddIntersect
#define cuddZddDivide pbori_cuddZddDivide
#define cuddZddWeakDiv pbori_cuddZddWeakDiv
#define cuddZddWeakDivF pbori_cuddZddWeakDivF
#define cuddZddUnateProduct pbori_cuddZddUnateProduct
#define cuddZddUnion pbori_cuddZddUnion
#define cuddZddProduct pbori_cuddZddProduct
#define cuddZddChangeAux pbori_cuddZddChangeAux
#define cuddZddChange pbori_cuddZddChange
#define cuddZddDiff pbori_cuddZddDiff
#define cuddZddIte pbori_cuddZddIte
#define cuddHashTableResize pbori_cuddHashTableResize

#define zdd_subset0_aux pbori_zdd_subset0_aux
#define zdd_subset1_aux pbori_zdd_subset1_aux

#define MMalloc pbori_MMalloc
#define MMrealloc pbori_MMrealloc
#define MMfree pbori_MMfree
#define MMoutOfMemory pbori_MMoutOfMemory
#define MMout_of_memory pbori_MMout_of_memory

#define DdManager pbori_DdManager
#endif
 
#endif /* polybori_cudd_prefix_internal_h_ */
