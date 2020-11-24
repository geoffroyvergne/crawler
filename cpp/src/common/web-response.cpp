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

/*boost::property_tree::ptree WebResponse::toJson() {
    boost::property_tree::ptree result;
    
    result.add_child("weburl", this->webUrl->toJson());
    result.add_child("webpage", this->webPage->toJson());

    boost::property_tree::ptree jsonTagList;
    for (HtmlTag* tag: this->tagList){         
        jsonTagList.push_back(std::make_pair("", tag->toJson()));
    }

    result.add_child("tags", jsonTagList);

    return result;
}*/

