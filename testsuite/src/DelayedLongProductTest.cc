// -*- c++ -*-
//*****************************************************************************
/** @file DelayedLongProductTest.cc
 *
 * @author Alexander Dreyer
 * @date 2012-02-24
 *
 * boost/test-driven unit test
 * 
 * @par Copyright:
 *   (c) 2012 by The PolyBoRi Team
 *
 **/
//*****************************************************************************


#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp> 
using boost::test_tools::output_test_stream;

#include <polybori/groebner/DelayedLongProduct.h>
#include <polybori/groebner/LongLongConstant.h>
USING_NAMESPACE_PBORI
USING_NAMESPACE_PBORIGB

struct Fdelayedlongprod {
  Fdelayedlongprod() {

    BOOST_TEST_MESSAGE( "setup fixture" );
  }

  ~Fdelayedlongprod() { BOOST_TEST_MESSAGE( "teardown fixture" ); }
};


BOOST_FIXTURE_TEST_SUITE(DelayedLongProductTest, Fdelayedlongprod)

BOOST_AUTO_TEST_CASE(test_less) {

  BOOST_TEST_MESSAGE( "operator<..." );

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(-1), 
					(unsigned long)(-1)) >
		     LongLongConstant<(unsigned long)(-1), (unsigned long)(-1)>()), false);

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(-1), 
					(unsigned long)(-1)) >
		     LongLongConstant<(unsigned long)(-1), 0>()), false);

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(-1), 
					(unsigned long)(-1)) >
		     LongLongConstant<(unsigned long)(-1)/2, 
		     (unsigned long)(-1)>()), true);

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(2)<<(sizeof(long)*4),
					(unsigned long)(2)<<(sizeof(long)*4)) >
		     LongLongConstant<3,(unsigned long)(-1)>()), true);

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(2)<<(sizeof(long)*4),
					(unsigned long)(2)<<(sizeof(long)*4)) >
		    LongLongConstant<4,0>()), false);

  BOOST_CHECK_EQUAL((DelayedLongProduct((unsigned long)(2)<<(sizeof(long)*4),
					(unsigned long)(2)<<(sizeof(long)*4) )>
		    LongLongConstant<4,1>()), false);

}

BOOST_AUTO_TEST_SUITE_END()
