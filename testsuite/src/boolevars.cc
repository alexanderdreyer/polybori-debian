// -*- c++ -*-
//*****************************************************************************
/** @file boolevars.cc 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file contains tests for the Boolean Variables.
 *
 * @par Copyright:
 *   (c) 2006 by The PolyBoRi Team
 *
 * @internal 
 * @version \$Id$
 *
 * @par History:
 * @verbatim
 * $Log$
 * Revision 1.8  2008/04/10 12:45:01  dreyer
 * Fix: memory leak
 *
 * Revision 1.7  2007/11/06 15:03:42  dreyer
 * CHANGE: More generic copyright
 *
 * Revision 1.6  2007/07/06 18:46:31  dreyer
 * ADD: rewritten C++-Interface for Cudd
 *
 * Revision 1.5  2006/07/14 09:02:49  dreyer
 * ADD: greater_variable()
 *
 * Revision 1.4  2006/03/27 13:47:58  dreyer
 * ADD operator + and *, CHANGE BoolePolyRing::variable(i) generation
 *
 * Revision 1.3  2006/03/22 08:06:59  dreyer
 * ADD: Template specializations CDDInterface<ZDD>, CDDManager<Cudd>; ring uses shared_ptr now
 *
 * Revision 1.2  2006/03/17 16:53:37  dreyer
 * ADD added nNodes(), operator*= to BoolePolynomial
 *
 * Revision 1.1  2006/03/16 17:09:13  dreyer
 * ADD BoolePolynial functionality started
 *
 * @endverbatim
**/
//*****************************************************************************


// load standard iostream capapilities
#include <iostream>

// load polybori header file
# include "polybori.h"

USING_NAMESPACE_PBORI

int
main(){
////  BoolePolyRing the_ring(5);
 BoolePolynomial poly;
  
  //DdManager* manager = Cudd_Init(1,1,1, 0,0);

  //  Cudd_Quit(manager);

  std::cout << "Testing boolean ring variables" <<std::endl;   
#if 0
  try {
    BoolePolyRing the_ring(5);


    BoolePolynomial x = BooleVariable(0);
    std::cout << x << std::endl;

    BoolePolynomial y = BooleVariable(1);
    std::cout << y << std::endl;

    BoolePolynomial poly = x;
    poly += y;

    std::cout << "Sum: "<<std::endl;
    std::cout << poly <<std::endl;

    BoolePolynomial zeroPoly;

    std::cout << "Zero polynomial: " <<std::endl;
    std::cout << zeroPoly <<std::endl;

    std::cout << "0 += x " <<std::endl;
    zeroPoly += x;
    std::cout << zeroPoly <<std::endl;


    std::cout << "var(1) > var(2)" <<std::endl;
    std::cout << greater_variable(1, 2) <<std::endl;

    std::cout << "var(2) > var(1)" <<std::endl;
    std::cout << greater_variable(2, 1) <<std::endl;

    std::cout << "poly *= var" <<std::endl;
    std::cout <<  (poly *= BooleVariable(0)) << std::endl;
    std::cout << "poly % var" <<std::endl;
    std::cout <<  (poly % BooleVariable(0)) << std::endl;

    std::cout << "poly %= var" <<std::endl;
    std::cout <<  (poly %= BooleVariable(0)) << std::endl;
    std::cout << "Finished."<<std::endl;


    std::cout << "var * monom" <<std::endl;
    std::cout <<  (BooleVariable(0)  * BooleMonomial(BooleVariable(1)))<<
      std::endl;
  }
  catch (PBoRiError& err) {
    std::cout << "  Caught error # "<< err.code() <<std::endl;   
    std::cout << "    which says: "<< err.text() <<std::endl;  
 }
#endif
  return 0;
}
