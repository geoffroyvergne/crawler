#include <iostream>
#include <boost/test/unit_test.hpp>

#include <http/http-client.hpp>

BOOST_AUTO_TEST_SUITE( http )

BOOST_AUTO_TEST_CASE(base) {
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(webUrl) {
    HttpClient *httpClient = new HttpClient("https://www.google.fr/");
    WebUrl* webUrl = httpClient->parseUrl();

    BOOST_CHECK(webUrl->sheme == "https");
    BOOST_CHECK(webUrl->url == "https://www.google.fr/");
    BOOST_CHECK(webUrl->host == "www.google.fr");
    BOOST_CHECK(webUrl->path == "/");
}

BOOST_AUTO_TEST_SUITE_END()
