// -*- c++ -*-
//*****************************************************************************
/** @file order_traits.h
 *
 * @author Alexander Dreyer
 * @date 2006-07-20
 *
 * File retired, but kept for future use.
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id: order_traits.h,v 1.9 2008/07/08 21:41:58 alexanderdreyer Exp $
 *
 * @par History:
 * @verbatim
 * $Log: order_traits.h,v $
 * Revision 1.9  2008/07/08 21:41:58  alexanderdreyer
 * Merge: from developer's repository
 *
 * Revision 1.4  2007/11/06 15:03:36  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.3  2006/10/05 12:51:32  dreyer
 * CHANGE: Made lex-based comparisions more generic.
 *
 * Revision 1.2  2006/10/04 13:09:56  dreyer
 * ADD: added compile-time optimied iterators and genericBegin/genericEnd
 *
 * Revision 1.1  2006/07/20 08:55:49  dreyer
 * ADD isOrdered() and  isLexicographical()
 *
 * @endverbatim
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"

// include orderings
#include "LexOrder.h"
#include "DegLexOrder.h"
#include "DegRevLexAscOrder.h"

#include <functional>

#ifndef order_traits_h_
#define order_traits_h_

BEGIN_NAMESPACE_PBORI



template <class OrderType>
class order_traits {


};

END_NAMESPACE_PBORI

#endif // order_traits_h_
