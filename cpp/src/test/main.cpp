#include <iostream>

#define CATCH_CONFIG_MAIN

/*int main(int argc, char** argv) {
    std::cout << "Crawler Test" << std::endl;

    return EXIT_SUCCESS;
}*/

#include <test/catch.hpp>

TEST_CASE( "Simple test" ) {
    REQUIRE( 1+1 == 2 );
}
