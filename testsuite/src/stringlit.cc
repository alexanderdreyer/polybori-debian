// -*- c++ -*-
// $Id: stringlit.cc,v 1.9 2008/07/08 21:41:59 alexanderdreyer Exp $
//
//*****************************************************************************
/** @file stringlit.cc 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file contains tests for the class CStringLiteral.
 *
 *  (c) 2006 by The PolyBoRi Team
 *
**/
//*****************************************************************************
//
// Last edit by $Author: alexanderdreyer $ on $Date: 2008/07/08 21:41:59 $


// load standard iostream capapilities
#include <iostream>

// load polybori header file
# include "polybori.h"

# include "CStringLiteral.h"

# include "CLiteralCodes.h"

USING_NAMESPACE_PBORI

template <unsigned NUM = CLiteralCodes::first_code>
class print_lit {
public:
  void operator()() const {
    std::cout << '"'<< CStringLiteral<NUM>()() <<'"' <<std::endl;
    print_lit<NUM+1>()();
  };
};

template <>
class print_lit <CLiteralCodes::last_code>{
public:
  void operator()() const {  };
};


int
main(){

  std::cout << CStringLiteral<0>()()  <<std::endl;

  std::cout << CStringLiteral<1>()()  <<std::endl;

  print_lit<>()();

  return 0;
}
