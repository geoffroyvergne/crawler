#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include <html/parser.hpp>
#include <html/tag.hpp>

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

TEST(html, html_title_test) {    
    std::string content = "<title>test</title>";
    HtmlParser *htmlParser = new HtmlParser(content);

    std::vector<HtmlTag*> tagList = htmlParser->getTagList();
    HtmlTag* tag = *(tagList.begin());

    ASSERT_EQ(tag->name, "title");
    ASSERT_EQ(tag->content, "test");

    free(htmlParser);
}

TEST(html, html_a_href_test) {  
    std::string content = "<a href=\"test\">test</a>";
    HtmlParser *htmlParser = new HtmlParser(content);

    std::vector<HtmlTag*> tagList = htmlParser->getTagList();
    HtmlTag* tag = *(tagList.begin());

    ASSERT_EQ(tag->name, "a");
    ASSERT_EQ(tag->content, "test");
    ASSERT_EQ(tag->href, "test");

    free(htmlParser);
}