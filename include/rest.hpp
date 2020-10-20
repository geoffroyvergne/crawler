#include <restinio/all.hpp>

//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef REST
#define REST

//#pragma once
class Rest {
    public:
        int connect(std::string address, int port);
    private:
        //static Json::StreamWriterBuilder getBuilder();
        static restinio::request_handling_status_t handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params);
        static restinio::request_handling_status_t handleVersion(restinio::request_handle_t& req, restinio::router::route_params_t& params);
        static restinio::request_handling_status_t handleUrl(restinio::request_handle_t& req, restinio::router::route_params_t& params);
        static boost::property_tree::ptree parseBody(std::string body);
        static std::string jsonToString(boost::property_tree::ptree json);
};

#endif
