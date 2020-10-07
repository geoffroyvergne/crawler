// https://www.boost.org/doc/libs/1_74_0/libs/test/doc/html/boost_test/tests_organization/test_cases/test_organization_nullary.html

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE main
#include <boost/test/unit_test.hpp>
//#include <boost/bind/bind.hpp>

/*using namespace boost::unit_test;

class test_class {
public:
  void test_method1() {
    BOOST_TEST( true );
  }

  void test_method2() {
    BOOST_TEST( true );
  }
};

boost::unit_test::test_suite* init_unit_test_suite() {
  boost::shared_ptr<test_class> tester( new test_class );

  framework::master_test_suite().
    add( BOOST_TEST_CASE( boost::bind( &test_class::test_method1, tester )));
  framework::master_test_suite().
    add( BOOST_TEST_CASE( boost::bind( &test_class::test_method2, tester )));
  return 0;
}*/

BOOST_AUTO_TEST_CASE( free_test_main_function ) {
  BOOST_TEST( true );
}

/*#include <iostream>

int main(int argc, char** argv){
    std::cout << "Crawler Test ..." << std::endl;

    return EXIT_SUCCESS;
}*/
