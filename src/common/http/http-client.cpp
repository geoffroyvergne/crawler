#include <iostream>
#include <string>
#include <http/http-client.hpp>
#include <boost/regex.hpp>
//#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

std::string HttpClient::make_string(boost::asio::streambuf& streambuf) {
    return {
        boost::asio::buffers_begin(streambuf.data()), 
        boost::asio::buffers_end(streambuf.data())
    };
}

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
        }

        webUrl->path        = std::string(what[4].first, what[4].second);
        webUrl->query       = std::string(what[5].first, what[5].second);
        webUrl->fragment    = std::string(what[6].first, what[6].second);
    }    

    return webUrl;
}

std::vector<std::string> HttpClient::extractHeader(std::string header) {
    std::vector<std::string> results;
    boost::split(results, header, boost::is_any_of(":"));
    
    boost::trim(results.at(0));
    boost::algorithm::to_lower(results.at(0));
    
    boost::trim(results.at(1));
    boost::algorithm::to_lower(results.at(1));

    return results;
}

WebPage* HttpClient::httpGet() {
    WebPage* webPage = new WebPage();
    webPage->url = this->url;

    try {
        std::string httpVersion;
        std::string content;
        int statusCode;

        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(this->webUrl->host, this->webUrl->sheme);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << this->webUrl->path << " HTTP/1.0\r\n";
        request_stream << "Host: " << this->webUrl->host << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);

        response_stream >> httpVersion;
        
        response_stream >> statusCode;

        webPage->httpCode = statusCode;

        std::string status_message;
        std::getline(response_stream, status_message);

        if (!response_stream || httpVersion.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            exit(EXIT_FAILURE);
        }     

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        
        std::map<std::string, std::string> headerMap;
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            //std::cout << header << "\n";
            //headerList.push_back(header);

            std::vector<std::string> results = this->extractHeader(header);
            headerMap[results.at(0)] = results.at(1);
        }   

        webPage->contentType = headerMap.at("content-type");

        // Write whatever content we already have to output.
        if (response.size() > 0) {            
            content.append(this->make_string(response));
        }

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {            
            content.append(this->make_string(response));
        }

        if (error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }

        //std::cout << "content : " << content << std::endl;

        webPage->content = content;

    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return webPage;
}
