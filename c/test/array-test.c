#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* test;
    char* name;     
    char* src;
    char* href;
    char* content;
    long* httpCode;
    double* elapsed;
} tag;

tag** tag_array;
int tagI;
int maxTag = 50;

int main() {
    printf("array test\n");
    tag_array = (tag**) calloc(maxTag, sizeof(tag));
    

    for(tagI=0; tagI<maxTag; tagI++) {
        tag* currentTag = malloc(sizeof(tag));
        currentTag->test = malloc(sizeof(char) * 50);
        currentTag->name = malloc(sizeof(char) * 50);
        currentTag->content = malloc(sizeof(char) * 50);
        currentTag->href = malloc(sizeof(char) * 50);
        currentTag->src = malloc(sizeof(char) * 50);

        currentTag->httpCode = malloc(sizeof(long));
        currentTag->elapsed = malloc(sizeof(double));

        //memset(currentTag, 0, sizeof(tag));

        strcpy(currentTag->name, "name");
        strcpy(currentTag->test, "test");
        strcpy(currentTag->content, "content");
        strcpy(currentTag->href, "href");
        strcpy(currentTag->src, "src");

        *currentTag->httpCode = (long)200;
        *currentTag->elapsed = (double)1.215;

        tag_array[tagI] = currentTag; 
        //free(currentTag);       
    }

    for(tagI=0; tagI<maxTag; tagI++) {
        printf("'name' : %s 'test' : %s 'content' : %s 'href' : %s 'src' : %s httpCode : %ld elapsed : %f\n", 
            tag_array[tagI]->name,
            tag_array[tagI]->test,
            tag_array[tagI]->content,
            tag_array[tagI]->href,
            tag_array[tagI]->src,
            *tag_array[tagI]->httpCode,
            *tag_array[tagI]->elapsed
        );
    }

    free(tag_array);

    return 0;
}

