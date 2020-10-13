#include <iostream>
#include <html/tag.hpp>

std::string HtmlTag::toString() {
    std::string result;

    !HtmlTag::name.empty() ? result.append("'Name' : " + HtmlTag::name + " ") : result.append(" ");
    !HtmlTag::content.empty() ? result.append("'Content' : " + HtmlTag::content + " ") : result.append(" ");
    !HtmlTag::src.empty() ? result.append("'Src' : " + HtmlTag::src + " ") : result.append(" ");
    !HtmlTag::href.empty() ? result.append("'Href' : " + HtmlTag::href + " ") : result.append(" ");

    return result;
}
