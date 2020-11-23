#include <gumbo/gumbo.h>

#ifndef TAG
#define TAG

typedef struct {
    char* name;     
    char* src;
    char* href;
    char* content;
} tag;

char* tag_to_string(const tag** tag_array, int tagNum);
char* tag_to_json(const tag** tag_array, int tagNum);

#endif
