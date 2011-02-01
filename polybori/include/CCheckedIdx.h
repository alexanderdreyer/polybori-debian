// -*- c++ -*-
//*****************************************************************************
/** @file CCheckedIdx.h 
 *
 * @author 
 * @date 
 *
 * 
 *
 * @par Copyright:
 *   (c) by The PolyBoRi Team
 *
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"

#ifndef CCheckedIdx_h_
#define CCheckedIdx_h_

BEGIN_NAMESPACE_PBORI

/** @class CCheckedIdx
 * @brief This class defines CCheckedIdx.
 * 
 * It checks the the range of CTypes::idx_type;
 **/
class CCheckedIdx:
  public CTypes::auxtypes_type {

  /// Type of *this
  typedef CCheckedIdx self;

public:
  CCheckedIdx(idx_type idx): m_idx(idx) {
    if UNLIKELY(idx < 0) handle_error();
  }
  CCheckedIdx(const self& rhs): m_idx(rhs.m_idx) { }
  ~CCheckedIdx() {}

  operator idx_type() const { return m_idx; }
private:
  void handle_error() const;
  idx_type m_idx;
};

END_NAMESPACE_PBORI

#endif
