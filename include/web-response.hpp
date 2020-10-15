#include <iostream>
#include <vector>

#include <http/web-page.hpp>
#include <http/web-url.hpp>
#include <html/tag.hpp>
#include <json/json.h>

#ifndef WEB_RESPONSE
#define WEB_RESPONSE

//#pragma once
class WebResponse {
    public: 
        WebResponse();
        WebResponse(WebUrl* webUrl, WebPage* webPage, std::vector<HtmlTag*> tagList);
        WebUrl* webUrl;
        WebPage* webPage;
        std::vector<HtmlTag*> tagList;
        void printString();
        std::string toString();
        Json::Value toJson();
};

#endif
