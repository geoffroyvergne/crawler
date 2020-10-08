#include <iostream>

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
};
