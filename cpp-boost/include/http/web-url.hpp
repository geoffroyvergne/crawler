#include <iostream>

//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef WEB_URL
#define WEB_URL

//pragma once
class WebUrl {
    public:
        //WebUrl();        
        std::string url;
        std::string host;
        std::string path;
        int port;
        std::string query;
        std::string sheme;
        std::string fragment;
        std::string toString();
        boost::property_tree::ptree toJson();
};

#endif
