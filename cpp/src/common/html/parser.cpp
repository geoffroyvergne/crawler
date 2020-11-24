#include <iostream>
#include <fstream>
#include <string>
//#include <regex>

#include <gumbo/gumbo.h>
#include <html/parser.hpp>
//#include <boost/algorithm/string.hpp>

int HtmlParser::tempTest() {
    return 1+1;
}

HtmlParser::HtmlParser(std::string htmlContent) {
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, htmlContent.data(), htmlContent.length());
    parse(output->root);
}

std::string HtmlParser::cleanString(std::string* value) {
    //boost::algorithm::replace_all(*value, " ", "");
    //boost::algorithm::replace_all(*value, "\r\n", " ");
    //boost::algorithm::replace_all(*value, "\r", " ");
    //boost::algorithm::replace_all(*value, "\n", " ");

    return *value;
}

void HtmlParser::parse(GumboNode* node) {
    if(node->type == GUMBO_NODE_TEXT) {
        std::string name = gumbo_normalized_tagname(node->parent->v.element.tag);
        std::string content = node->v.text.text;

        HtmlTag* currentTag = new HtmlTag();
        
        // A Href
        if(node->parent->v.element.tag == GUMBO_TAG_A) {
            //std::string href;
            GumboAttribute* gumboAttributeHref;
            if((gumboAttributeHref = gumbo_get_attribute(&node->parent->v.element.attributes, "href"))) {
                //href = gumboAttributeHref->value;
                currentTag->href = gumboAttributeHref->value;
            }
        }

        currentTag->name = name;
        currentTag->content = this->cleanString(&content);        

        //std::cout << "Tag : " << tag << " => Text : " << content << std::endl;
        //std::cout << currentTag.toString() << std::endl;

        this->tagList.push_back(currentTag);

        //free(currentTag);
    }

    // META tag

    // Link tag

    // IMG tag
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_IMG) {
        std::string name = gumbo_normalized_tagname(node->v.element.tag);
        std::string src;
        
        GumboAttribute* gumboAttributeSrc;
        if((gumboAttributeSrc = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
            src = gumboAttributeSrc->value;
        }

        //std::cout << "Tag : " << name << " => src : " << src << std::endl;

        HtmlTag* currentTag = new HtmlTag();
        currentTag->name = gumbo_normalized_tagname(node->v.element.tag);
        currentTag->src = src;

        this->tagList.push_back(currentTag);

        //free(currentTag);
    }

    if (node->type == GUMBO_NODE_ELEMENT) {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            parse((GumboNode*) children->data[i]);
        }
    }
}

std::string HtmlParser::getHtmlFromFile(std::string fileName) {
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if (!in) {
        std::cout << "File " << fileName << " not found!\n";
        exit(EXIT_FAILURE);
    }

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    return contents;
}

std::string HtmlParser::getHtmlFromString(std::string html) {
    return html;
}

std::vector<HtmlTag*> HtmlParser::getTagList() {
    return this->tagList;
}

