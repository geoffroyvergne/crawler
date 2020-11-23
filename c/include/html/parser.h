#include <gumbo/gumbo.h>
#include <html/tag.h>

#ifndef HTML_PARSER
#define HTML_PARSER

int parser_get_get_tagI();
const tag** parser_string(char* content);
char* getHtmlFromFile(char* fileName);
char* getHtmlFromString(char* content);
//char* getTagList();
//static int tempTest();
char* cleanString(char* value);

#endif
