#include <iostream>
#include <http/web-url.hpp>

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + " => ");
    result.append("host : " + WebUrl::host + " => ");
    result.append("path : " + WebUrl::path);

    return result;
}

Json::Value WebUrl::toJson() {
    Json::Value result;

    result["url"] = WebUrl::url;
    result["host"] = WebUrl::host;
    result["path"] = WebUrl::path;

    return result;
}
