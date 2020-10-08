#include <iostream>

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
};
