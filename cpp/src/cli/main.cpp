#include <iostream>

#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>
#include <cli.hpp>
#include <config.hpp>

WebResponse* getWebResponse(std::string url) {
    HttpClient *httpClient = new HttpClient(url);
    HtmlParser *htmlParser = new HtmlParser(httpClient->getWebPage()->content);

    WebResponse *webResponse = new WebResponse(
        httpClient->getWebUrl(),
        httpClient->getWebPage(),
        htmlParser->getTagList()
    );

    return webResponse;
}

int main(int argc, char** argv) {
    config conf = cli_get_options(argc, argv);
    if(url.empty()) return EXIT_FAILURE;

    std::cout << "Crawler CLI url : " << conf.url << std::endl;
    std::string url = conf.url;

    WebResponse *webResponse = getWebResponse(url);
    std::cout << webResponse->toString(); 

    free(webResponse);

    return EXIT_SUCCESS;
}
