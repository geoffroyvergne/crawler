#include <gumbo/gumbo.h>

#ifndef TAG
#define TAG

typedef struct {
    char* name;     
    char* src;
    char* href;
    char* content;
} tag;

void tag_to_string();
void tag_to_json();

#endif
