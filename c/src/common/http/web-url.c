#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <http/web-url.h>

char* web_url_to_string(web_url* webUrl) {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    char* template = "url : %s host : %s path : %s \n";

    sprintf(result, template, 
        webUrl->url,
        webUrl->host, 
        webUrl->path
    );

    return result;
}

char* web_url_to_json(web_url* webUrl) {
    return NULL;
}

