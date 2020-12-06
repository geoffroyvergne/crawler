#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <gumbo/gumbo.h>

#include <html/tag.h>
#include <html/parser.h>

tag** parse(GumboNode* node);

tag** tag_array;
int tagI;
int maxtagArraySize = 100;

int parser_get_get_tagI() {
    return tagI;
}

tag** parser_string(char* content) {
    tagI = 0;
    //tag_array = (tag**) malloc(sizeof(tag));
    tag_array = (tag**) calloc(maxtagArraySize, sizeof(tag));
    //puts(content);
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, content, strlen(content));
    return parse(output->root);
}

tag** parse(GumboNode* node) {
   
    if(node->type == GUMBO_NODE_TEXT) {
        tag* currentTag = (tag*) malloc(sizeof(tag));
        currentTag->name = (char*) malloc(sizeof(char) * 500000);
        currentTag->content = (char*) malloc(sizeof(char) * 50000);
        currentTag->href = (char*) malloc(sizeof(char) * 20000);
        currentTag->src = (char*) malloc(sizeof(char) * 20000);

        //std::string name = gumbo_normalized_tagname(node->parent->v.element.tag);
        //std::string content = node->v.text.text;        

        //HtmlTag* currentTag = new HtmlTag();
        

        //currentTag->name = gumbo_normalized_tagname(node->parent->v.element.tag);
        strncpy(currentTag->name, gumbo_normalized_tagname(node->parent->v.element.tag), strlen(gumbo_normalized_tagname(node->parent->v.element.tag)));
        //currentTag->content = node->v.text.text;
        strncpy(currentTag->content, node->v.text.text, strlen(node->v.text.text));
        
        // A Href
        if(node->parent->v.element.tag == GUMBO_TAG_A) {
            
            GumboAttribute* gumboAttributeHref;
            if((gumboAttributeHref = gumbo_get_attribute(&node->parent->v.element.attributes, "href"))) {
                //currentTag->href = gumboAttributeHref->value;
                strncpy(currentTag->href, gumboAttributeHref->value, strlen(gumboAttributeHref->value));
            }
        }

        //std::cout << "Tag : " << tag << " => Text : " << content << std::endl;
        //std::cout << currentTag.toString() << std::endl;

        //this->tagList.push_back(currentTag);
        //puts(tag_to_string(currentTag));
        //printf("tag %d %s\n", tagI, currentTag->name);
        tag_array[tagI] = currentTag;
        tagI ++;

        //free(currentTag);
    }

    // META tag

    // Link tag

    // IMG tag
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_IMG) {
        tag* currentTag = malloc(sizeof(tag));
        currentTag->name = (char*) malloc(sizeof(char) * 500000);
        currentTag->content = (char*) malloc(sizeof(char) * 50000);
        currentTag->href = (char*) malloc(sizeof(char) * 20000);
        currentTag->src = (char*) malloc(sizeof(char) * 20000);

        //tag* currentTag = malloc(sizeof(tag));

        //currentTag->name = gumbo_normalized_tagname(node->v.element.tag);
        //strcpy(currentTag->name, gumbo_normalized_tagname(node->v.element.tag));
        
        //name = gumbo_normalized_tagname(node->v.element.tag);
        strncpy(currentTag->name, gumbo_normalized_tagname(node->v.element.tag), strlen(gumbo_normalized_tagname(node->v.element.tag)));
        
        GumboAttribute* gumboAttributeSrc;
        if((gumboAttributeSrc = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
            //currentTag->src = gumboAttributeSrc->value;
            strncpy(currentTag->src, gumboAttributeSrc->value, strlen(gumboAttributeSrc->value));
        }

        //std::cout << "Tag : " << name << " => src : " << src << std::endl;
        //printf("Tag : %s name : %s\n", currentTag->name, currentTag->src);

        //HtmlTag* currentTag = new HtmlTag();
        
        //currentTag->name = gumbo_normalized_tagname(node->v.element.tag);
        //currentTag->src = src;

        //this->tagList.push_back(currentTag);
        //puts(tag_to_string(currentTag));
        //printf("tag %d %s\n", tagI, currentTag->name);
        tag_array[tagI] = currentTag;
        tagI ++;

        //free(currentTag);
    }

    if (node->type == GUMBO_NODE_ELEMENT) {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            parse((GumboNode*) children->data[i]);
        }
    }

    return tag_array;
}

char* getHtmlFromFile(char* fileName) {
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(fileName, "r");

   if (handler) {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(buffer, sizeof(char), string_size, handler);

       buffer[string_size] = '\0';

       if (string_size != read_size) {           
           free(buffer);
           buffer = NULL;
       }

       fclose(handler);
    }

    return buffer;
}

char* getHtmlFromString(char* content) {
    return content;
}

/*static int tempTest() {
    return 1+1;
}*/

char* cleanString(char* value) {
    return value;
}
