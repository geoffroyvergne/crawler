#include "gtest/gtest.h"
#include <iostream>

#include <http/http-client.hpp>

TEST(http, base) {
    //std::cout << "module_name2 test_name2" << std::endl;
    // Google Test will also provide macros for assertions.

    ASSERT_EQ(1+1, 2);
}

TEST(http, webUrl) {    
    HttpClient *httpClient = new HttpClient("https://www.google.fr");
    WebUrl* webUrl = httpClient->parseUrl();

    //std::cout << webUrl->toString() << std::endl;

    ASSERT_EQ(webUrl->url, "https://www.google.fr");
    ASSERT_EQ(webUrl->host, "www.google.fr");
    ASSERT_EQ(webUrl->path, "/");
}