#include <gumbo/gumbo.h>

#ifndef TAG
#define TAG

typedef struct {
    char* name;     
    char* src;
    char* href;
    char* content;
} tag;

char* tag_to_string(tag** tag_array, int tagNum);
char* tag_to_json(tag** tag_array, int tagNum);

#endif
