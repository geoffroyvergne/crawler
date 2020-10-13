#include <iostream>
#include <vector>
#include <gumbo.h>
#include <html/tag.hpp>

class HtmlParser {
    public:
        HtmlParser(std::string htmlContent);
        void parse(GumboNode* node);
        std::string getHtmlFromFile(std::string fileName);
        std::string getHtmlFromString(std::string html);
        std::vector<HtmlTag*> getTagList();
        static int tempTest();
    
    private:
        std::vector<HtmlTag*> tagList;
        std::string cleanString(std::string* value);
};
