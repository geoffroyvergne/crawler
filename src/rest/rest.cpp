#include <iostream>

#include <boost/log/trivial.hpp>

#include <rest.hpp>
#include <app.h>

#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>

boost::property_tree::ptree Rest::parseBody(std::string body) {    
    std::stringstream ss;
    ss << body;

    boost::property_tree::ptree root;
    boost::property_tree::read_json(ss, root);

    return root;
}

std::string Rest::jsonToString(boost::property_tree::ptree json) {
    std::stringstream resultJson;

    boost::property_tree::write_json(resultJson, json, false);

    return resultJson.str();
}



int Rest::connect(std::string address, int port) {
    

    return EXIT_SUCCESS;
}
