#include <iostream>

#include <http/web-page.hpp>
#include <http/web-url.hpp>

#ifndef HTTP_CLIENT
#define HTTP_CLIENT

class HttpClient {
    public:
        //HttpClient();
        HttpClient(std::string url);
        //std::string toString();
        WebUrl* parseUrl();
        WebPage* httpGet();
        WebPage* httpSslGet();
        std::string getHtmlContent();
        WebUrl* getWebUrl();
        WebPage* getWebPage();
        void getResults();
    private:        
        std::string url;
        static size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);        
        WebUrl* webUrl;
        WebPage* webPage;        
};

#endif
