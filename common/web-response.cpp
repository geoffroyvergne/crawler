#include <iostream>
#include <vector>

#include <web-response.hpp>

WebResponse::WebResponse() {}

WebResponse::WebResponse(WebUrl* webUrl, WebPage* webPage, std::vector<HtmlTag*> tagList) {
    this->webPage = webPage;
    this->webUrl = webUrl;
    this->tagList = tagList;
}

void WebResponse::toString() {
    std::cout << this->webUrl->toString() << std::endl;
    std::cout << this->webPage->toString() << std::endl;

    std::cout << "Tags" << std::endl;
    for (HtmlTag* tag: this->tagList){
        std::cout << tag->toString() << std::endl;
    }
}
