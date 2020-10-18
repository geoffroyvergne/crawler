#include <iostream>
#include <http/web-url.hpp>

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + " => ");
    result.append("host : " + WebUrl::host + " => ");
    result.append("path : " + WebUrl::path);

    return result;
}

boost::property_tree::ptree WebUrl::toJson() {    
    boost::property_tree::ptree result;

    result.put("url", WebUrl::url);
    result.put("host", WebUrl::host);
    result.put("path", WebUrl::path);

    return result;
}
