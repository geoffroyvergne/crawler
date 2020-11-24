#ifndef WEB_URL
#define WEB_URL

typedef struct {
    //char* url; 
    int* port;
    char* host;
    char* path;
    char* query;
    char* sheme; 
    char* fragment; 
} web_url;

char* web_url_to_string(const web_url* webUrl);
char* web_url_to_json(const web_url* webUrl);

#endif
