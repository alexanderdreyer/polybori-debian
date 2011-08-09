// -*- c++ -*-
//*****************************************************************************
/** @file pbori_tags.h
 *
 * @author Alexander Dreyer
 * @date 2006-07-20
 *
 * Decribes properties of polybori ordering classes
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id: pbori_tags.h,v 1.9 2008/07/08 21:41:58 alexanderdreyer Exp $
 *
 * @par History:
 * @verbatim
 * $Log: pbori_tags.h,v $
 * Revision 1.9  2008/07/08 21:41:58  alexanderdreyer
 * Merge: from developer's repository
 *
 * Revision 1.3  2007/11/06 15:03:37  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.2  2006/12/13 18:07:04  dreyer
 * ADD: poly /= exp
 *
 * Revision 1.1  2006/10/06 12:52:01  dreyer
 * ADD easy_equility_property and used in lex_compare
 *
 * @endverbatim
**/
//*****************************************************************************

// include basic definitions
#include "pbori_defs.h"
#include "order_tags.h"

#ifndef pbori_tags_h_
#define pbori_tags_h_

BEGIN_NAMESPACE_PBORI

/** @class invalid_tag
 * @brief This class shows, whether a property of an order is invalid.
 **/
struct invalid_tag {};

/** @class valid_tag
 * @brief This class shows, whether a property of an order is valid.
 **/
struct valid_tag {};

/** @class navigator_tag
 * @brief for iterator_category
 **/
struct navigator_tag {};

/** @class easy_equality_property
 *  @brief defines generic base for properties
 **/
template <class ValidityTag>
class equality_property {
public:

  /// Set marker for validity
  typedef ValidityTag easy_equality_property;
};


END_NAMESPACE_PBORI

#endif // order_tags_h_
