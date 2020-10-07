#include "gtest/gtest.h"
#include <iostream>

TEST(module_name3, test_name3) {
    std::cout << "module_name3 test_name3" << std::endl;
    // Google Test will also provide macros for assertions.
    ASSERT_EQ(1+1, 2);
}

