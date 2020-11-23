#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <html/tag.h>
#include <json/cJSON.h>

char* tag_to_string(const tag** tag_array, int tagNum) {
    char *result = malloc(sizeof(char) * 5000000);
    char* template = "Tag => name : %s src : %s href : %d content : %d\n";

    for(int i=0; i<tagNum; i++) {
        char *tmpResult = malloc(sizeof(char) * 500000);
        sprintf(tmpResult, template, 
            tag_array[i]->name,
            tag_array[i]->src,
            strlen(tag_array[i]->href),
            strlen(tag_array[i]->content)
        );
        strcat(result, tmpResult);
        free(tmpResult);
    }

    return result;
}

char* tag_to_json(const tag** tag_array, int tagNum) {
    char *result = malloc(sizeof(char) * 5000000);

    cJSON *resultJson = cJSON_CreateObject();
    cJSON *tags = cJSON_CreateArray();
    cJSON_AddItemToObject(resultJson, "tags", tags);
    for(int i=0; i<tagNum; i++) {
        cJSON *tag = cJSON_CreateObject();
        cJSON_AddStringToObject(tag, "name", tag_array[i]->name);
        cJSON_AddStringToObject(tag, "src", tag_array[i]->src);
        cJSON_AddNumberToObject(tag, "href", strlen(tag_array[i]->href));
        cJSON_AddNumberToObject(tag, "content", strlen(tag_array[i]->content));
        cJSON_AddItemToArray(tags, tag);
        //cJSON_Delete(tag);
    }
    //cJSON_Delete(tags);

    //result = cJSON_Print(resultJson);
    //result = cJSON_PrintUnformatted(resultJson);
    strcat(result, cJSON_PrintUnformatted(resultJson));
    cJSON_Delete(resultJson);

    return result;
}
