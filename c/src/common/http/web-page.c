#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <http/web-page.h>

char* web_page_to_string(web_page* webPage) {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    char* template = "url : %s httpCode : %d content type : %s content : %d \n";

    sprintf(result, template, 
        webPage->url,
        webPage->httpCode, 
        webPage->contentType,
        strlen(webPage->content)
    );

    return result;
}

char* web_page_to_json(web_page* webPage) {
    return NULL;
}
