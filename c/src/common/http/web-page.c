#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <json/cJSON.h>
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
    char *result =  malloc(sizeof(char) * 400000);

    cJSON *resultJson = cJSON_CreateObject();
    cJSON_AddStringToObject(resultJson, "url", webPage->url);
    cJSON_AddNumberToObject(resultJson, "httpCode", webPage->httpCode);
    cJSON_AddStringToObject(resultJson, "contentType", webPage->contentType);
    cJSON_AddNumberToObject(resultJson, "content", strlen(webPage->content));

    //result = cJSON_Print(resultJson);
    result = cJSON_PrintUnformatted(resultJson);
    cJSON_Delete(resultJson);

    return result;
}
