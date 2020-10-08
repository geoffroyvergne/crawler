#include <iostream>
#include <http/web-url.hpp>

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + "\n");
    result.append("host : " + WebUrl::host + "\n");
    result.append("path : " + WebUrl::path + "\n");


    return result;
}
