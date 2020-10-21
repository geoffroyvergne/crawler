#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <boost/log/trivial.hpp>

#include <rest.hpp>
#include <app.h>

#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

template<class Body, class Allocator, class Send>
void handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {   
    const auto response = 
        [&req](boost::beast::string_view content, boost::beast::string_view contentType, http::status status) {
		http::response<http::string_body> res{ status, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, contentType);
		res.keep_alive(req.keep_alive());
        res.body() = content.to_string();
        res.content_length(content.length());
		res.prepare_payload();
		return res;
	};

    if( req.target().empty() || req.target()[0] != '/' || req.target().find("..") != beast::string_view::npos ) {        
        return send(response("400 bad request", "application/text", http::status::bad_request)); 
    }

    if(req.target() == "/index" && req.method() == http::verb::get) {
        std::string content = "GET /index endpoint";
        std::cout << content << std::endl;
        
        boost::property_tree::ptree root;
    
        root.put("code", 200);
        root.put("value", "Response OK");

        return send(response(Rest::jsonToString(root), "application/json", http::status::ok));
    }

    if(req.target() == "/version" && req.method() == http::verb::get) {
        std::string content = "/version " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);
        std::cout << content << std::endl;

        BOOST_LOG_TRIVIAL(info) << content;

        std::stringstream resultJson;
        boost::property_tree::ptree root;
    
        root.put("app", APP_NAME);
        root.put("version", content);

        boost::property_tree::write_json(resultJson, root); 
        
        return send(response(Rest::jsonToString(root), "application/json", http::status::ok));
    }

    if(req.target() == "/url" && req.method() == http::verb::post) {
        std::string body = req.body();
        boost::property_tree::ptree root = Rest::parseBody(body);

        // Check if url is set in body json
        if(root.empty() || root.get<std::string>("url").empty()) {
            //return req->create_response(restinio::status_bad_request()).done();
            return send(response("404 not found", "application/text", http::status::not_found));
        }

        const std::string url = root.get<std::string>("url");

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
        std::string resultJson = Rest::jsonToString(webResponse->toJson());

        return send(response(resultJson, "application/json", http::status::ok));
    }

    return send(response("404 not found", "application/text", http::status::not_found));
}

void fail(beast::error_code ec, char const* what) {
    BOOST_LOG_TRIVIAL(error) << ": " << ec.message();
}

template<class Stream> struct send_lambda {
    Stream& stream_;
    bool& close_;
    beast::error_code& ec_;

    explicit send_lambda(Stream& stream, bool& close, beast::error_code& ec) : stream_(stream), close_(close), ec_(ec){}

    template<bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const {
        close_ = msg.need_eof();
        http::serializer<isRequest, Body, Fields> sr{msg};
        http::write(stream_, sr, ec_);
    }
};

void do_session(tcp::socket& socket, std::shared_ptr<std::string const> const& doc_root) {
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<tcp::socket> lambda{socket, close, ec};

    for(;;) {
        // Read a request
        http::request<http::string_body> req;
        http::read(socket, buffer, req, ec);

        if(ec == http::error::end_of_stream) break;
        if(ec) return fail(ec, "read");

        // Send the response
        handle_request(*doc_root, std::move(req), lambda);
        if(ec) return fail(ec, "write");
        if(close) break;
    }

    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

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
    try {        
        auto ipAddress = net::ip::make_address(address);
        auto ipPort = static_cast<unsigned short>(port);
        auto doc_root = std::make_shared<std::string>("./");

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {ipAddress, ipPort}};
        for(;;) {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{
                std::bind(&do_session, std::move(socket), doc_root)
            }.detach();
        }
    } catch (const std::exception& e) {
        //std::cerr << "Error: " << e.what() << std::endl;
        
        BOOST_LOG_TRIVIAL(error) << "Error: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
