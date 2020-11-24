#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <http/web-url.h>
#include <json/cJSON.h>

char* web_url_to_string(const web_url* webUrl) {
    char *result =  malloc(sizeof(char) * 500000);
    //char* template = "WebUrl => url : %s host : %s path : %s";
    char* template = "WebUrl => host : %s path : %s";

    sprintf(result, template, 
        //webUrl->url,
        webUrl->host, 
        webUrl->path
    );

    return result;
}

char* web_url_to_json(const web_url* webUrl) {
    char *result =  malloc(sizeof(char) * 500000);

    cJSON *resultJson = cJSON_CreateObject();
    //cJSON_AddStringToObject(resultJson, "url", webUrl->url);
    cJSON_AddStringToObject(resultJson, "host", webUrl->host);
    cJSON_AddStringToObject(resultJson, "path", webUrl->path);

    //result = cJSON_Print(resultJson);
    result = cJSON_PrintUnformatted(resultJson);
    cJSON_Delete(resultJson);

    return result;
}

