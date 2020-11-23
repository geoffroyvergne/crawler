#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <http/web-page.h>

char* web_page_to_string(const web_page* webPage) {
    char *result = malloc(sizeof(char) * 400000);
    
    char* template = "WebPage => url : %s httpCode : %d content type : %s content : %d";

    sprintf(result, template, 
        webPage->url,
        webPage->httpCode, 
        webPage->contentType,
        strlen(webPage->content)
        //webPage->content
    );

    return result;
}

char* web_page_to_json(const web_page* webPage) {
    return NULL;
}
