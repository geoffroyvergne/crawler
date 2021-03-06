#include <iostream>
#include <http/web-page.hpp>

std::string WebPage::toString() {
    std::string result = "WebPage => ";
    
    result.append("Content : " + std::to_string(WebPage::content.length()) + " => ");
    result.append("Header : " + std::to_string(WebPage::header.length()) + " => ");
    result.append("HTTP Code : " + std::to_string(WebPage::httpCode) + " => ");
    result.append("ContentType : " + WebPage::contentType);

    return result;
}

boost::property_tree::ptree WebPage::toJson() {
    boost::property_tree::ptree result;

    result.put("content", std::to_string(WebPage::content.length()));
    result.put("header", std::to_string(WebPage::header.length()));
    result.put("httpCode", WebPage::httpCode);
    result.put("contentType", WebPage::contentType);

    return result;
}
