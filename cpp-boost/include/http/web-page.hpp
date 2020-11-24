#include <iostream>

//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef WEB_PAGE
#define WEB_PAGE

//#pragma once
class WebPage {
    public:
        //WebPage();
        std::string url;
        int port;
        std::string sheme;
        std::string content;
        std::string header;
        std::string contentType;
        int httpCode;
        double elapsed;
        std::string toString();
        boost::property_tree::ptree toJson();
};

#endif 
