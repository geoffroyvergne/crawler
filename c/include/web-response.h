#include <http/web-page.h>
#include <http/web-url.h>
#include <html/tag.h>

#ifndef WEB_RESPONSE
#define WEB_RESPONSE

typedef struct {
    web_page* webPage;
    web_url* webUrl;
    tag** tag_array;
} web_response;

web_response* getWebResponse(char* url);
char* web_response_to_string(web_response* webResponse);
char* web_response_to_json(web_response* webResponse);

#endif
