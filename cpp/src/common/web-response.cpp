#include <iostream>
#include <vector>
#include <json/json.hpp>

#include <http/web-page.hpp>
#include <http/web-url.hpp>
#include <html/tag.hpp>

#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>

WebResponse::WebResponse() {}

WebResponse::WebResponse(std::string url) {
    HttpClient *httpClient = new HttpClient(url);
    HtmlParser *htmlParser = new HtmlParser(httpClient->getWebPage()->content);
    
    this->webPage = httpClient->getWebPage();
    this->webUrl = httpClient->getWebUrl();
    this->tagList =  htmlParser->getTagList();
}

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
    nlohmann::json webResponseJson;

    webResponseJson["web-url"]["url"] = this->webUrl->url;
    webResponseJson["web-url"]["host"] = this->webUrl->host;
    webResponseJson["web-url"]["port"] = std::to_string(this->webUrl->port);
    webResponseJson["web-url"]["path"] = this->webUrl->path;

    webResponseJson["web-page"]["url"] = this->webPage->url;
    webResponseJson["web-page"]["sheme"] = this->webPage->sheme;
    webResponseJson["web-page"]["port"] = std::to_string(this->webPage->port);
    webResponseJson["web-page"]["httpCode"] = std::to_string(this->webPage->httpCode);
    webResponseJson["web-page"]["contentType"] = this->webPage->contentType;
    webResponseJson["web-page"]["content"] = std::to_string(this->webPage->content.length());

    webResponseJson["tags"] = nlohmann::json::array();

    auto jsonTags = nlohmann::json::array();
    auto jsonTag = nlohmann::json::object();

    for (HtmlTag* tag: this->tagList){       
        jsonTag["name"] = tag->name;
        jsonTag["href"] = tag->href;
        jsonTag["src"] = tag->src;
        jsonTag["content"] = tag->content;

        webResponseJson["tags"].push_back(jsonTag);
    }

    return webResponseJson.dump();
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

