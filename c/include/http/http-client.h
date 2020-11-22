#include <curl/curl.h>
#include <http/web-page.h>
#include <http/web-url.h>

#ifndef HTTP_CLIENT
#define HTTP_CLIENT

web_url* parseUrl(char* url);
web_page* httpGet(char* url);
/*char* getHtmlContent();
web_url* getWebUrl();
web_page* getWebPage();
void getResults();
void fail(CURL *h);*/
        
#endif
