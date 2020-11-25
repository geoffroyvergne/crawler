#include <iostream>
#include <json/json.hpp>
#include <http/web-url.hpp>

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + " => ");
    result.append("host : " + WebUrl::host + " => ");
    result.append("port : " + std::to_string(WebUrl::port) + " => ");
    result.append("path : " + WebUrl::path);

    return result;
}

std::string WebUrl::toJson() {
    nlohmann::json j = {
        {"url", WebUrl::url },
        {"host", WebUrl::host },
        {"port", std::to_string(WebUrl::port) },
        {"path", WebUrl::path }
    };

    return j.dump();
}

/*boost::property_tree::ptree WebUrl::toJson() {    
    boost::property_tree::ptree result;

    result.put("url", WebUrl::url);
    result.put("host", WebUrl::host);
    result.put("port", std::to_string(WebUrl::port));
    result.put("path", WebUrl::path);

    return result;
}*/
