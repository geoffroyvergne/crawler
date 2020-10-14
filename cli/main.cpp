#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <app.h>
#include <cli.hpp>
#include <http/http-client.hpp>
#include <html/parser.hpp>
#include <web-response.hpp>

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
    BOOST_LOG_TRIVIAL(info) << APP_NAME << " Cli mode";

    // Get command line arguments
    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    if (vm.count("url")) {
        // Request URL
        std::string url = vm["url"].as<std::string>();
        WebResponse *webResponse = getWebResponse(url);
        std::cout << webResponse->toString(); 

        free(webResponse);
    }

    free(cli);
    
    return EXIT_SUCCESS;
}
