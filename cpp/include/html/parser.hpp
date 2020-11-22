#include <iostream>
#include <vector>
#include <gumbo/gumbo.h>
#include <html/tag.hpp>

#ifndef HTML_PARSER
#define HTML_PARSER

//#pragma once
class HtmlParser {
    public:
        HtmlParser(std::string htmlContent);
        void parse(GumboNode* node);
        std::string getHtmlFromFile(std::string fileName);
        std::string getHtmlFromString(std::string html);
        std::vector<HtmlTag*> getTagList();
        static int tempTest();
    
    private:
        std::vector<HtmlTag*> tagList;
        std::string cleanString(std::string* value);
};

#endif 
