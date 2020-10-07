#include <restinio/all.hpp>
#include "json/json.h"

restinio::request_handling_status_t handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params);
int connect(std::string address, int port);

class Rest {
    public:
        //Rest();
        int connect(std::string address, int port);
    private:
        static Json::StreamWriterBuilder getBuilder();
        static restinio::request_handling_status_t handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params);
};
