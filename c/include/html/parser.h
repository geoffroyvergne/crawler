#include <gumbo/gumbo.h>
#include <html/tag.h>

#ifndef HTML_PARSER
#define HTML_PARSER

tag** parseString(char* content);
tag** parse(GumboNode* node);
char* getHtmlFromFile(char* fileName);
char* getHtmlFromString(char* content);
//char* getTagList();
static int tempTest();
char* cleanString(char* value);

#endif
