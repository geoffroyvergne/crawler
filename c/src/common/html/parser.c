#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <gumbo/gumbo.h>

#include <html/tag.h>
#include <html/parser.h>

const tag** tag_array;
const tag** parse(GumboNode* node);
int tagI;

int parser_get_get_tagI() {
    return tagI;
}

const tag** parser_string(char* content) {
    tagI = 0;
    tag_array = malloc(sizeof(tag*));
    //puts(content);
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, content, strlen(content));
    return parse(output->root);
}

const tag** parse(GumboNode* node) {
    
    tag* currentTag = malloc(sizeof(tag));
    currentTag->name = malloc(sizeof(char) * 2000);
    currentTag->content = malloc(sizeof(char) * 20000);
    currentTag->href = malloc(sizeof(char) * 2000);
    currentTag->src = malloc(sizeof(char) * 2000);

    if(node->type == GUMBO_NODE_TEXT) {
        //std::string name = gumbo_normalized_tagname(node->parent->v.element.tag);
        //std::string content = node->v.text.text;        

        //HtmlTag* currentTag = new HtmlTag();
        

        //currentTag->name = gumbo_normalized_tagname(node->parent->v.element.tag);
        strcpy(currentTag->name, gumbo_normalized_tagname(node->parent->v.element.tag));
        //currentTag->content = node->v.text.text;
        strcpy(currentTag->content, node->v.text.text);
        
        // A Href
        if(node->parent->v.element.tag == GUMBO_TAG_A) {
            
            GumboAttribute* gumboAttributeHref;
            if((gumboAttributeHref = gumbo_get_attribute(&node->parent->v.element.attributes, "href"))) {
                //currentTag->href = gumboAttributeHref->value;
                strcpy(currentTag->href, gumboAttributeHref->value);
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
        //tag* currentTag = malloc(sizeof(tag));

        //currentTag->name = gumbo_normalized_tagname(node->v.element.tag);
        //strcpy(currentTag->name, gumbo_normalized_tagname(node->v.element.tag));
        
        //name = gumbo_normalized_tagname(node->v.element.tag);
        strcpy(currentTag->name, gumbo_normalized_tagname(node->v.element.tag));
        
        GumboAttribute* gumboAttributeSrc;
        if((gumboAttributeSrc = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
            //currentTag->src = gumboAttributeSrc->value;
            strcpy(currentTag->src, gumboAttributeSrc->value);
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
