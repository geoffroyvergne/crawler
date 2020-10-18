#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <html/parser.hpp>
#include <html/tag.hpp>

BOOST_AUTO_TEST_SUITE( html )

BOOST_AUTO_TEST_CASE(base) {
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(tempTest) {
    BOOST_CHECK(HtmlParser::tempTest() == 2);
}

BOOST_AUTO_TEST_CASE(html_title_test) {
    std::string content = "<title>test</title>";
    HtmlParser *htmlParser = new HtmlParser(content);

    std::vector<HtmlTag*> tagList = htmlParser->getTagList();
    HtmlTag* tag = *(tagList.begin());

    BOOST_CHECK(tag->name == "title");
    BOOST_CHECK(tag->content == "test");

    free(htmlParser);
}

BOOST_AUTO_TEST_CASE(html_a_href_test) {
    std::string content = "<a href=\"test\">test</a>";
    HtmlParser *htmlParser = new HtmlParser(content);

    std::vector<HtmlTag*> tagList = htmlParser->getTagList();
    HtmlTag* tag = *(tagList.begin());

    BOOST_CHECK(tag->name == "a");
    BOOST_CHECK(tag->content == "test");
    BOOST_CHECK(tag->href == "test");

    free(htmlParser);
}

BOOST_AUTO_TEST_SUITE_END()
