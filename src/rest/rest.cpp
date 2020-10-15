#include <iostream>

#include <restinio/all.hpp>
#include <json/json.h>
#include <boost/log/trivial.hpp>

#include <rest.hpp>
#include <app.h>

#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>

Json::StreamWriterBuilder Rest::getBuilder() {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "";

    return builder;
}

Json::Value parseBody(std::string body) {
    const auto bodyLength = static_cast<int>(body.length());

    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    if (!reader->parse(body.c_str(), body.c_str() + bodyLength, &root, &err)) {        
        BOOST_LOG_TRIVIAL(error) << "error json body parsing : " << err;
    }

    return root;
}

restinio::request_handling_status_t Rest::handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params) {
    //const auto qp = restinio::parse_query(req->header().query());

    Json::Value data;
    data["code"] = 200;
    data["value"] = "Response OK";

    BOOST_LOG_TRIVIAL(info) << "/index";

    return req->create_response(restinio::status_ok())
        .set_body(Json::writeString(Rest::getBuilder(), data))
        .append_header(restinio::http_field::content_type, "application/json")
        .done();
}

restinio::request_handling_status_t Rest::handleVersion(restinio::request_handle_t& req, restinio::router::route_params_t& params) {
    Json::Value data;    
    data["app"] = APP_NAME;    
    data["version"] = std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);    

    BOOST_LOG_TRIVIAL(info) << "/version " << std::to_string(VERSION_MAJOR) << "." << std::to_string(VERSION_MINOR);

    return req->create_response(restinio::status_ok())
        .set_body(Json::writeString(Rest::getBuilder(), data))
        .append_header(restinio::http_field::content_type, "application/json")
        .done();
}

restinio::request_handling_status_t Rest::handleUrl(restinio::request_handle_t& req, restinio::router::route_params_t& params) {

    std::string body = req->body();
    Json::Value root = parseBody(body);

    if(root.empty() || root["url"].empty()) {
        return req->create_response(restinio::status_bad_request()).done();
    }

    const std::string url = root["url"].asString();

    BOOST_LOG_TRIVIAL(info) << "/url " << url;

    // HTTP GET on url
    HttpClient *httpClient = new HttpClient(url);

    //Parse HTML content
    HtmlParser *htmlParser = new HtmlParser(httpClient->getWebPage()->content);

    WebResponse *webResponse = new WebResponse(
        httpClient->getWebUrl(),
        httpClient->getWebPage(),
        htmlParser->getTagList()
    );

    std::cout << webResponse->toString();

    // Transform result to JSON
    Json::Value data = webResponse->toJson();

    return req->create_response(restinio::status_ok())
    .set_body(Json::writeString(Rest::getBuilder(), data))
    .append_header(restinio::http_field::content_type, "application/json")
    .done();
}

int Rest::connect(std::string address, int port) {
    try {
        std::unique_ptr<restinio::router::express_router_t<>> router = std::make_unique<restinio::router::express_router_t<>>();

        router->http_get(R"(/index)", [](auto req, auto params) {
            return Rest::handleIndex(req, params);            
        });

        router->http_get(R"(/version)", [](auto req, auto params) {
            return Rest::handleVersion(req, params);            
        });

        router->http_post(R"(/url)", [](auto req, auto params) {
            return Rest::handleUrl(req, params);            
        });

        router->non_matched_request_handler([](auto req){
            return req->create_response(restinio::status_not_found()).connection_close().done();
        });

        struct server_traits : public restinio::default_single_thread_traits_t {
            using request_handler_t = restinio::router::express_router_t<>;
        };

        restinio::run(            
            restinio::on_thread_pool<server_traits>(std::thread::hardware_concurrency())
            //restinio::on_this_thread<server_traits>()
            .port(port)
            .address(address)
            .request_handler(std::move(router)));
            
    } catch(const std::exception & e) {
        BOOST_LOG_TRIVIAL(error) << "error: " << e.what();
		return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
