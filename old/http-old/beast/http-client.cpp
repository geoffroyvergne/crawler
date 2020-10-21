#include <iostream>
#include <string>
#include <http/http-client.hpp>
#include <boost/regex.hpp>
//#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

/*std::string HttpClient::make_string(boost::asio::streambuf& streambuf) {
    return {
        boost::asio::buffers_begin(streambuf.data()), 
        boost::asio::buffers_end(streambuf.data())
    };
}*/

WebUrl* HttpClient::getWebUrl() {
    return this->webUrl;
}

WebPage* HttpClient::getWebPage() {
    return this->webPage;
}

std::string HttpClient::getHtmlContent() {
    return this->webPage->content;
}

HttpClient::HttpClient(std::string url) {
    this->url = url;

    this->webUrl = this->parseUrl();
    this->webPage = this->httpGet();
}

void HttpClient::getResults() {
    //std::cout << webUrl->toString() << std::endl;
    //std::cout << webPage->toString() << std::endl;

    //free(webPage);
    //free(webUrl);
}

WebUrl* HttpClient::parseUrl() {
    WebUrl* webUrl = new WebUrl();
    webUrl->url = this->url;

    const std::string regex = "(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)";

    boost::regex ex(regex);
    boost::cmatch what;

    if(regex_match(url.c_str(), what, ex)) {
        webUrl->sheme       = std::string(what[1].first, what[1].second);
        webUrl->host        = std::string(what[2].first, what[2].second);
        
        std::string port = std::string(what[3].first, what[3].second);

        if(!port.empty()) {
            webUrl->port        = std::stoi(port.c_str());
        } else {
            if(webUrl->sheme == "http") webUrl->port = 80;
            if(webUrl->sheme == "https") webUrl->port = 443;
        }

        webUrl->path        = std::string(what[4].first, what[4].second);
        webUrl->query       = std::string(what[5].first, what[5].second);
        webUrl->fragment    = std::string(what[6].first, what[6].second);

        if(webUrl->path.empty()) webUrl->path = "/";
    }    

    return webUrl;
}

/*std::vector<std::string> HttpClient::extractHeader(std::string header) {
    std::vector<std::string> results;
    boost::split(results, header, boost::is_any_of(":"));
    
    boost::trim(results.at(0));
    boost::algorithm::to_lower(results.at(0));
    
    boost::trim(results.at(1));
    boost::algorithm::to_lower(results.at(1));

    return results;
}*/

WebPage* HttpClient::httpGet() {
    WebPage* webPage = new WebPage();
    webPage->url = this->url;

    int version = 10;

    try {
        // The io_context is required for all I/O
        boost::asio::io_context ioc;

        // These objects perform our I/O
        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(this->webUrl->host, std::to_string(this->webUrl->port));

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, this->webUrl->path, version};
        req.set(boost::beast::http::field::host, this->webUrl->host);
        req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        boost::beast::http::write(stream, req);

        // This buffer is used for reading and must be persisted
        boost::beast::flat_buffer buffer;

        // Declare a container to hold the response
        boost::beast::http::response<boost::beast::http::dynamic_body> res;

        // Receive the HTTP response
        boost::beast::http::read(stream, buffer, res);

        // Write the message to standard out
        //std::cout << res << std::endl;

        //std::cout << res.result_int() << std::endl;
        //std::cout << res.result() << std::endl;
        //std::cout << res.reason() << std::endl;

        //std::cout << boost::beast::buffers_to_string(res.body().data()) << std::endl;

        webPage->httpCode = res.result_int();
        webPage->content = boost::beast::buffers_to_string(res.body().data());

        for (auto& h : res.base()) {
            std::cout << "name: " << h.name() << ", name_string: " << h.name_string() << ", value: " << h.value() << "\n";
        }

        // Gracefully close the socket
        boost::beast::error_code ec;
        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if(ec && ec != boost::beast::errc::not_connected) {
            throw boost::beast::system_error{ec};
        }

    } catch(std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return webPage;
    }

    return webPage;
}
