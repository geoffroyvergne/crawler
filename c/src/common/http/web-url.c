#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <http/web-url.h>

char* web_url_to_string(const web_url* webUrl) {
    char *result =  malloc(sizeof(char) * 2000);
    char* template = "WebUrl => url : %s host : %s path : %s";

    sprintf(result, template, 
        webUrl->url,
        webUrl->host, 
        webUrl->path
    );

    return result;
}

char* web_url_to_json(const web_url* webUrl) {
    return NULL;
}

