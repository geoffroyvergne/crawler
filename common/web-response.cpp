#include <iostream>
#include <vector>

#include <web-response.hpp>

WebResponse::WebResponse() {}

WebResponse::WebResponse(WebUrl* webUrl, WebPage* webPage, std::vector<HtmlTag*> tagList) {
    this->webPage = webPage;
    this->webUrl = webUrl;
    this->tagList = tagList;
}

std::string WebResponse::toString() {
    std::string result;
    result.append(this->webUrl->toString());
    result.append("\n");
    result.append(this->webPage->toString());
    result.append("\n");
    
    result.append("Tags\n");
    for (HtmlTag* tag: this->tagList){        
        result.append(tag->toString());
        result.append("\n");
    }

    return result;
}

std::string WebResponse::toJson() {
    std::string result;

    return result;
}