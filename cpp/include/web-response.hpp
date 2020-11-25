#include <iostream>
#include <vector>

#include <http/web-page.hpp>
#include <http/web-url.hpp>
#include <html/tag.hpp>

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

#ifndef WEB_RESPONSE
#define WEB_RESPONSE

//#pragma once
class WebResponse {
    public: 
        WebResponse();
        WebResponse(std::string url);
        WebResponse(WebUrl* webUrl, WebPage* webPage, std::vector<HtmlTag*> tagList);
        WebUrl* webUrl;
        WebPage* webPage;
        std::vector<HtmlTag*> tagList;
        void printString();
        std::string toString();
        std::string toJson();
        //boost::property_tree::ptree toJson();
};

#endif
