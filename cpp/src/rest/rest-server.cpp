#include <iostream>
#include <rest/rest-server.hpp>
#include <rest/httplib.h>
#include <json/json.hpp>
#include <app.h>

#include <web-response.hpp>

/*WebResponse* getWebResponse(std::string url) {
    HttpClient *httpClient = new HttpClient(url);
    HtmlParser *htmlParser = new HtmlParser(httpClient->getWebPage()->content);

    WebResponse *webResponse = new WebResponse(
        httpClient->getWebUrl(),
        httpClient->getWebPage(),
        htmlParser->getTagList()
    );

    return webResponse;
}*/

RestServer::RestServer(std::string host, int port) {
    this->host = host;
    this->port = port;
}

void RestServer::connect() {    
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
        std::string content = "/version " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);
        std::cout << APP_NAME << " " << content << std::endl;

        nlohmann::json j = {
            {"name", APP_NAME },
            {"version", content }
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
