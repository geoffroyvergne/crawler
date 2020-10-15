#include <iostream>
#include <json/json.h>

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
        Json::Value toJson();
};

#endif
