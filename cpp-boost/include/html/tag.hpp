#include <iostream>

//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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
        boost::property_tree::ptree toJson();
};

#endif 
