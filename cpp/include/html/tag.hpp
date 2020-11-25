#include <iostream>

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
        std::string toJson();
        //boost::property_tree::ptree toJson();
};

#endif 
