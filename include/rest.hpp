#include <restinio/all.hpp>
#include <json/json.h>

#ifndef REST
#define REST

//#pragma once
class Rest {
    public:
        int connect(std::string address, int port);
    private:
        static Json::StreamWriterBuilder getBuilder();
        static restinio::request_handling_status_t handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params);
        static restinio::request_handling_status_t handleVersion(restinio::request_handle_t& req, restinio::router::route_params_t& params);
        static restinio::request_handling_status_t handleUrl(restinio::request_handle_t& req, restinio::router::route_params_t& params);
};

#endif
