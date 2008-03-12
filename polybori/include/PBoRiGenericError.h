// -*- c++ -*-
//*****************************************************************************
/** @file PBoRiError.h 
 *
 * @author Alexander Dreyer
 * @date 2008-03-11
 *
 * This file defines the template class PBoriError, which is used for polybori's
 * exception handling.
 *
 * @par Copyright:
 *   (c) 2008 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.1  2008/03/11 10:04:12  dreyer
 * Fix: Exceptions: Division by zero, Polynomial(0).lead(), and ITE
 *
 * @endverbatim
**/
//*****************************************************************************

// load PolyBoRi settings
#include "pbori_defs.h"

// Get runtime-definable error type
#include "PBoRiError.h"

#ifndef PBoRiGenericError_h_
#define PBoRiGenericError_h_


BEGIN_NAMESPACE_PBORI

/** @class PBoRiGenericError
 * @brief This template class is used for polybori's exception handling.
 *
 * It's mainly a wrapper for PBoRiError, which allows compile-time distinction
 * of errors.
 * 
 **/
template <CTypes::errornum_type ErrorCode>
class PBoRiGenericError: 
  public PBoRiError {
public:
  /// adopt global error code enumeration
  typedef CTypes::errornum_type errornum_type;

  /// adopt global error text type
  typedef CTypes::errortext_type errortext_type;

  enum { error_code = ErrorCode };

  /// Default constructor
  PBoRiGenericError(): PBoRiError(error_code) {}

};

END_NAMESPACE_PBORI

#endif // of #ifndef PBoRiGenericError_h_