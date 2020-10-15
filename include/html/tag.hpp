#include <iostream>
#include <json/json.h>

#ifndef TAG
#define TAG

//#pragma once

class HtmlTag {
    public:
        //Tag(std::string name, std::string text, std::string src);
        //Tag();
        std::string name;
        std::string content;
        std::string src;
        std::string href;
        std::string toString();
        Json::Value toJson();
};

#endif 
