#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( cli )

BOOST_AUTO_TEST_CASE(base) {
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(version) {
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
