#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <html/tag.h>
#include <json/cJSON.h>

char* tag_to_string(tag** tag_array, int tagNum) {
    char *result = malloc(sizeof(char) * 5000000);
    char* template = "Tag => name : %s src : %s href : %s content : %s\n";

    for(int i=0; i<tagNum; i++) {
        char *tmpResult = (char*) malloc(sizeof(char) * 500000);
        sprintf(tmpResult, template, 
            tag_array[i]->name,
            tag_array[i]->src,
            tag_array[i]->href,
            tag_array[i]->content
        );
        strcat(result, tmpResult);
        free(tmpResult);
    }

    return result;
}

char* tag_to_json(tag** tag_array, int tagNum) {
    //char *result = malloc(sizeof(char) * 50000000);
    printf("%d %s\n", tagNum, tag_array[0]->name);

    cJSON *resultJson = cJSON_CreateObject();
    cJSON *tags = cJSON_CreateArray();
    cJSON_AddItemToObject(resultJson, "tags", tags);
    for(int i=0; i<tagNum; i++) {       
        cJSON *tag = cJSON_CreateObject();

        cJSON_AddStringToObject(tag, "name", tag_array[i]->name);
        cJSON_AddStringToObject(tag, "src", tag_array[i]->src);

        cJSON_AddStringToObject(tag, "href", tag_array[i]->href);
        cJSON_AddStringToObject(tag, "content", tag_array[i]->content);
        cJSON_AddItemToArray(tags, tag);

        //cJSON_Delete(tag);
    }
    

    //result = cJSON_Print(resultJson);
    //result = cJSON_PrintUnformatted(resultJson);
    //strcpy(result, (char*) cJSON_PrintUnformatted(resultJson));
    //cJSON_Delete(resultJson);
    //cJSON_Delete(tags);

    //return result;

    //puts(cJSON_PrintUnformatted(resultJson));
   
    return cJSON_PrintUnformatted(resultJson);
    
    //return "";
}
