#include "gtest/gtest.h"
#include <iostream>
#include <mysqrt.h>

TEST(mysqrt, basicTest) {
    //std::cout << "mysqrt mysqrt" << std::endl;
    // Google Test will also provide macros for assertions.
    const double outputValue = mysqrt(4);

    ASSERT_EQ(outputValue, 2);
}