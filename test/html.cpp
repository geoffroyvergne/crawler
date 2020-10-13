#include "gtest/gtest.h"
#include <iostream>
#include <html/parser.hpp>

TEST(html, base) {
    //std::cout << "module_name2 test_name2" << std::endl;
    // Google Test will also provide macros for assertions.

    ASSERT_EQ(1+1, 2);
}

TEST(html, tempTest) {
    //std::cout << "module_name3 test_name3" << std::endl;
    // Google Test will also provide macros for assertions.

    ASSERT_EQ(HtmlParser::tempTest(), 2);
}

