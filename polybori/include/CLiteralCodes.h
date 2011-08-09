// -*- c++ -*-
//*****************************************************************************
/** @file CLiteralCodes.h
 *
 * @author Alexander Dreyer
 * @date 2006-07-04
 *
 * This file contains a class for codes representing string literals.
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id: CLiteralCodes.h,v 1.9 2008/07/08 21:41:58 alexanderdreyer Exp $
 *
 * @par History:
 * @verbatim
 * $Log: CLiteralCodes.h,v $
 * Revision 1.9  2008/07/08 21:41:58  alexanderdreyer
 * Merge: from developer's repository
 *
 * Revision 1.3  2007/11/19 14:13:26  dreyer
 * Fix: consistend naming of cartesianProduct
 *
 * Revision 1.2  2007/11/06 15:03:34  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.1  2006/07/04 14:11:03  dreyer
 * ADD: Generic and handy treatment of string literals
 *
 * @endverbatim
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"

#ifndef CLiteralCodes_h_
#define CLiteralCodes_h_

BEGIN_NAMESPACE_PBORI

/** @class CLiteralCodes
 * @brief This template class defines enumerative codes for the string literals
 * defined by the CStringLiterals class.
 **/
class CLiteralCodes {
public:

  /// Define codes representing string literals
  enum literal_codes {
    first_code = 0, 
    empty = first_code,
    space,
    plus,
    term_separator,
    times,
    comma,
    list_separator,
    default_variable_name,
    variable_head,
    variable_tail,
    between_list_separator,
    last_code
  };

};

END_NAMESPACE_PBORI

#endif
