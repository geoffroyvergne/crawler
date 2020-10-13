#include <iostream>
#include <http/web-page.hpp>

std::string WebPage::toString() {
    std::string result = "WebPage => ";
    
    result.append("Content : " + std::to_string(WebPage::content.length()) + "\n");
    result.append("Header : " + std::to_string(WebPage::header.length()) + "\n");
    result.append("HTTP Code : " + std::to_string(WebPage::httpCode) + "\n");
    result.append("ContentType : " + WebPage::contentType + "\n");

    return result;
}
