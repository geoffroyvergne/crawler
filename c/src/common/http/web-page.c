#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <json/cJSON.h>
#include <http/web-page.h>

char* web_page_to_string(web_page* webPage) {
    char *result = (char*) malloc(sizeof(char) * 400000);
    
    char* template = "WebPage => httpCode : '%ld' contentType : '%s' elapsed : '%f' content : %d";
    //char* template = "WebPage => httpCode : '%ld' contentType : '%s' content : %d";

    sprintf(result, template, 
        //webPage->url,
        *webPage->httpCode, 
        webPage->contentType,
        //*webPage->elapsed,
        0,
        strlen(webPage->content)
        //webPage->content
    );

    //printf("httpCode : %ld \n", *webPage->httpCode);

    return result;
}

char* web_page_to_json(web_page* webPage) {
    char *result = (char*) malloc(sizeof(char) * 400000);

    cJSON *resultJson = cJSON_CreateObject();
    //cJSON_AddStringToObject(resultJson, "url", webPage->url);
    cJSON_AddNumberToObject(resultJson, "httpCode", (int) *webPage->httpCode);
    //cJSON_AddNumberToObject(resultJson, "elapsed", (double) *webPage->elapsed);
    cJSON_AddNumberToObject(resultJson, "elapsed", 0);
    cJSON_AddStringToObject(resultJson, "contentType", webPage->contentType);
    cJSON_AddNumberToObject(resultJson, "content", strlen(webPage->content));

    //result = cJSON_Print(resultJson);
    result = cJSON_PrintUnformatted(resultJson);
    cJSON_Delete(resultJson);

    return result;
}
