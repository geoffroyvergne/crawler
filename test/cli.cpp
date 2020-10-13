#include "gtest/gtest.h"
#include <iostream>
//#include <app.h>
#include <cli.hpp>

TEST(cli, base) {
    //std::cout << "module_name1 test_name1" << std::endl;
    // Google Test will also provide macros for assertions.
    ASSERT_EQ(1+1, 2);
}


TEST(cli, version) {
    /*int argc = 2;
    char* array[] = {"crawler", "--version"};
    char** argv = array;
    
    Cli *cli = new Cli(argc, argv);*/

    //Cli *cli = new Cli();
}
