#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <html/tag.h>

char* tag_to_string(const tag* tag) {
    char *result = malloc(sizeof(char) * 40000);
    char* template = "Tag => name : %s src : %s href : %d content : %d";

    sprintf(result, template, 
        tag->name,
        tag->src,
        strlen(tag->href),
        strlen(tag->content)
    );

    return result;
}

char* tagToJson(const tag* tag) {
    return NULL;
}