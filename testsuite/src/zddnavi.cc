// -*- c++ -*-
//*****************************************************************************
/** @file 
 *
 * @author Alexander Dreyer
 * @date 2006-03-06
 *
 * This file contains elementary tests for getting thwe leading term
 *
 * @par Copyright:
 *   (c) 2006 by
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
 * Revision 1.3  2006/04/07 16:32:08  dreyer
 * ADD dd_transform and resp. examples
 *
 * Revision 1.2  2006/04/06 15:54:50  dreyer
 * CHANGE testsuite revised
 *
 * Revision 1.1  2006/04/06 13:05:54  dreyer
 * CHANGE more suitable names for CCuddNavigator functions
 *
 * Revision 1.3  2006/03/30 11:57:11  dreyer
 * CHANGE: Made use of 0/1 constants and the sets {}, {{}} consistent
 *
 * Revision 1.2  2006/03/30 08:52:57  dreyer
 * CHANGE: testsuite revised
 *
 * Revision 1.1  2006/03/28 07:34:03  dreyer
 * + Initial Version
 *
 * @endverbatim
**/
//*****************************************************************************


// load standard iostream capapilities
#include <iostream>
#include <list>
#include <iterator>
#include <sstream>

// load polybori header file
# include "polybori.h"

#include "pbori_algo.h"

USING_NAMESPACE_PBORI


template <class NaviType, class TermType, class ListType>
void
find_paths(NaviType navi, const TermType& currentPath, ListType& theList ) {

  if (navi.isConstant()) {      // Reached end of path
    if (navi.terminalValue())   // Case of a valid path
      theList.push_back(currentPath);
  }
  else {
    find_paths(navi.thenBranch(), currentPath.change(*navi), theList);
    find_paths(navi.elseBranch(), currentPath, theList);
  }
}


template <class IteratorType>
void print1D(IteratorType first, IteratorType last) {

  while (first != last) {
    std::cout << *first <<", ";
    ++first;
  }
}

template<class IteratorType>
void print2D(IteratorType first, IteratorType last) {

  while (first != last) {
    print1D( (*first).begin(), (*first).end());
    std::cout << std::endl;
    ++first;
  }
}


// dummy type for storing monomial data
class variables_list :
  public std::list<int> {
public:
  
  typedef std::list<int> base;
  variables_list() : base() {}
};

std::ostream& 
operator<<(std::ostream& os, const variables_list& varlist) {

   std::copy(varlist.begin(), varlist.end(), 
             std::ostream_iterator<variables_list::value_type>(os, " ") );

  return os;
}


int
main(){

  std::cout << "Testing navigating through decision diagrams" <<std::endl;   

  try {
    BoolePolyRing the_ring(5);

    BoolePolynomial x = the_ring.variable(0);
    BoolePolynomial y = the_ring.variable(1);

    BoolePolynomial z = BooleVariable(2);

    BoolePolynomial v = BooleVariable(3);
    BoolePolynomial w = BooleVariable(4);

    BoolePolynomial poly = (x*z) * (z + v*w) + y;

    std::cout << "poly:  "<<std::endl;
    std::cout << poly <<std::endl;

    std::cout << "Navigation: "<<std::endl;

    BoolePolynomial::navigator navi = poly.navigation();

    std::list<CDDInterface<ZDD> > theList;

    dd_transform( navi, BoolePolyRing::ringOne(),  
                  std::back_inserter(theList),
                  change<CDDInterface<ZDD> >() );

    std::copy(theList.begin(), theList.end(), 
              std::ostream_iterator<BoolePolynomial>(std::cout, "\n") );


    std::cout <<std::endl<< "Printing via dd_transform: "<<std::endl;
    dd_transform( navi, BoolePolyRing::ringOne(), 
                  std::ostream_iterator<BoolePolynomial>(std::cout, ""),
                  change<CDDInterface<ZDD>, int> () );

    std::cout <<std::endl<< "Storing via dd_transform: "<<std::endl;

    std::list<std::list<int>  > allLists;

    dd_transform( navi, std::list<int>(),
                  std::back_inserter(allLists),
                  push_back<std::list<int> >() );

    print2D(allLists.begin(), allLists.end());

    std::cout <<std::endl<< "pure print dd_transform: "<<std::endl;

    dd_transform( navi, variables_list(),
                  std::ostream_iterator<variables_list>(std::cout, "\n"),
                  push_back<variables_list>() );



    std::cout << "Finished."<<std::endl;

  }
  catch (PBoRiError& err) {
    std::cout << "  Caught error # "<< err.code() <<std::endl;   
    std::cout << "    which says: "<< err.text() <<std::endl;  
 }

  return 0;
}