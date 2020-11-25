#include <iostream>
#include <rest/httplib.h>

#ifndef REST_SERVER
#define REST_SERVER

class RestServer {
    public:
        RestServer(std::string host, int port);
        void connect();
    private:
        httplib::Server svr;
        std::string host;
        int port;
};

#endif
