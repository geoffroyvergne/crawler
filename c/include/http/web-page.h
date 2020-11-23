#ifndef WEB_PAGE
#define WEB_PAGE

typedef struct {
    char* url; 
    int port;
    char* sheme;
    char* content;
    char* header; 
    char* contentType; 
    int httpCode;
    double elapsed;
} web_page;

char* web_page_to_string(const web_page* webPage);
char* web_page_to_json(const web_page* webPage);

#endif
