#include <iostream>
#include <cstdlib>
#include <rest/rest-server.hpp>
#include <rest/httplib.h>
#include <json/json.hpp>
#include <app.h>

#include <web-response.hpp>

void sig_handler(int signo);

RestServer::RestServer(std::string host, int port) {
    this->host = host;
    this->port = port;
}

void RestServer::connect() {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        std::cout << "can't catch SIGINT" << std::endl;
    } 

    this->svr.Get("/ping", [](const httplib::Request &, httplib::Response &res) {
        std::cout << "/ping" << std::endl;

        nlohmann::json j = {
            {"code", 200 },
            {"value", "pong" }
        };

        res.set_content(j.dump(), "application/json");
    });

    this->svr.Get("/echo", [](const httplib::Request &, httplib::Response &res) {
        std::cout << "/echo" << std::endl;
        
        nlohmann::json j = {
            {"code", 200 },
            {"value", "OK" }
        };

        res.set_content(j.dump(), "application/json");
    });

    this->svr.Get("/version", [](const httplib::Request &, httplib::Response &res) {
        std::string version = std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);
        std::cout << "/version " << APP_NAME << " " << version << std::endl;

        nlohmann::json j = {
            {"name", APP_NAME },
            {"version", version }
        };

        res.set_content(j.dump(), "application/json");
    });

    this->svr.Post("/url", [](const httplib::Request &req, httplib::Response &res) {
        //std::cout << "body : " << req.body << std::endl;
        
        auto jsonBody = nlohmann::json::parse(req.body);
        std::string url = jsonBody["url"];
        std::cout << "/url " << url << std::endl;

        WebResponse *webResponse = new WebResponse(url);

        res.set_content(webResponse->toJson(), "application/json");
        free(webResponse);        
    });

    this->svr.listen(this->host.c_str(), this->port);
}

void sig_handler(int signo) {
  if (signo == SIGINT) {
    //printf("received SIGINT\n");
    std::cout << "received SIGINT" << std::endl;

    //shutdown(socket_desc, 2);
    //shutdown(new_socket, 2);
    //pthread_exit(NULL);

    exit(0);
    //abort();
  }
}
