#include <iostream>
#include <html/tag.hpp>

std::string HtmlTag::toString() {
    std::string result = "Tag";

    !HtmlTag::name.empty() ? result.append(" => 'Name' : " + HtmlTag::name + " ") : result.append("");
    !HtmlTag::content.empty() ? result.append(" => 'Content' : " + HtmlTag::content + " ") : result.append("");
    !HtmlTag::src.empty() ? result.append(" => 'Src' : " + HtmlTag::src + " ") : result.append("");
    !HtmlTag::href.empty() ? result.append(" => 'Href' : " + HtmlTag::href + " ") : result.append("");

    return result;
}

/*boost::property_tree::ptree HtmlTag::toJson() {    
    boost::property_tree::ptree result;

    if(!HtmlTag::name.empty()) result.put("name", HtmlTag::name);
    if(!HtmlTag::content.empty()) result.put("content", HtmlTag::content);
    if(!HtmlTag::src.empty()) result.put("src", HtmlTag::src);
    if(!HtmlTag::href.empty()) result.put("href", HtmlTag::href);

    return result;
}*/
