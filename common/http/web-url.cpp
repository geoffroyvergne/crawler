#include <iostream>
#include <http/web-url.hpp>

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + " => ");
    result.append("host : " + WebUrl::host + " => ");
    result.append("path : " + WebUrl::path);

    return result;
}
