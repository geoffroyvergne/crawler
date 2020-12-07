#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <web-response.h>
#include <http/web-page.h>
#include <http/web-url.h>
#include <http/http-client.h>
#include <html/tag.h>
#include <html/parser.h>
#include <json/cJSON.h>

web_response* getWebResponse(char* url) {
    web_url* webUrl = parseUrl(url);
    web_page* webPage = httpGet(url);
    tag** tag_array = parser_string(webPage->content);

    web_response* webResponse = malloc(sizeof(web_response));
    webResponse->webUrl = webUrl;
    webResponse->webPage = webPage;
    webResponse->tag_array = tag_array;

    return webResponse;
}

char* web_response_to_string(web_response* webResponse) {
    char *result =  malloc(sizeof(char) * 5000000);
    char* tag_template = "Tag => name : %s src : %s href : %s content : %s\n";
    char* template = "WebUrl => url : %s host : %s path : %s\nWebPage => httpCode : '%ld' contentType : '%s' elapsed : '%f' content : %d\n";

    sprintf(result, template, 
        webResponse->webUrl->url,
        webResponse->webUrl->host, 
        webResponse->webUrl->path,
        *webResponse->webPage->httpCode, 
        webResponse->webPage->contentType,
        //*webResponse->webPage->elapsed,
        0,
        strlen(webResponse->webPage->content)
        //webResponse->webPage->content
    );

    for(int i=0; i<parser_get_get_tagI(); i++) {
        char *tmpResult = (char*) malloc(sizeof(char) * 500000);
        sprintf(tmpResult, tag_template, 
            webResponse->tag_array[i]->name,
            webResponse->tag_array[i]->src,
            webResponse->tag_array[i]->href,
            webResponse->tag_array[i]->content
        );
        strcat(result, tmpResult);
        free(tmpResult);
    }

    return result;
}

char* web_response_to_json(web_response* webResponse) {
    char *result =  malloc(sizeof(char) * 5000000);

    cJSON *resultJson = cJSON_CreateObject();

    // WEBURL
    cJSON *resultJsonWebUrl = cJSON_CreateObject();
    cJSON_AddStringToObject(resultJsonWebUrl, "url", webResponse->webUrl->url);
    cJSON_AddStringToObject(resultJsonWebUrl, "host", webResponse->webUrl->host);
    cJSON_AddStringToObject(resultJsonWebUrl, "path", webResponse->webUrl->path);
    cJSON_AddItemReferenceToObject(resultJson, "web-url", resultJsonWebUrl);

    // WEBPAGE
    cJSON *resultJsonWebPage = cJSON_CreateObject();
    cJSON_AddNumberToObject(resultJson, "httpCode", (int) *webResponse->webPage->httpCode);
    //cJSON_AddNumberToObject(resultJson, "elapsed", (double) *webPage->elapsed);
    cJSON_AddNumberToObject(resultJson, "elapsed", 0);
    cJSON_AddStringToObject(resultJson, "contentType", webResponse->webPage->contentType);
    cJSON_AddNumberToObject(resultJson, "content", strlen(webResponse->webPage->content));
    cJSON_AddItemReferenceToObject(resultJson, "web-page", resultJsonWebPage);

    // TAG
    cJSON *tags = cJSON_CreateArray();
    cJSON_AddItemToObject(resultJson, "tags", tags);

    for(int i=0; i<parser_get_get_tagI(); i++) {       
        cJSON *tag = cJSON_CreateObject();

        cJSON_AddStringToObject(tag, "name", webResponse->tag_array[i]->name);
        cJSON_AddStringToObject(tag, "src", webResponse->tag_array[i]->src);

        cJSON_AddStringToObject(tag, "href", webResponse->tag_array[i]->href);
        cJSON_AddStringToObject(tag, "content", webResponse->tag_array[i]->content);
        cJSON_AddItemToArray(tags, tag);
    }

    result = cJSON_PrintUnformatted(resultJson);
    cJSON_Delete(resultJson);

    return result;
}
