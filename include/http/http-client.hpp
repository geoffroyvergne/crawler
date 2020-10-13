#include <iostream>
#include <http/web-page.hpp>
#include <http/web-url.hpp>
#include <curl/curl.h>

class HttpClient {
    public:
        //HttpClient();
        HttpClient(std::string url);
        //std::string toString();
        WebUrl* parseUrl();
        WebPage* httpGet();
        std::string getHtmlContent();
        WebUrl* getWebUrl();
        WebPage* getWebPage();
    private:
        void getResults();
        std::string url;
        static void fail(CURLU *curlu);
        static size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);        
        WebUrl* webUrl;
        WebPage* webPage;
};
