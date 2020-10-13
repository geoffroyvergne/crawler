#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <app.h>

#include <cli.hpp>
#include <rest.hpp>
#include <config-mgr.hpp>

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
    BOOST_LOG_TRIVIAL(info) << "Starting " << APP_NAME;

    // Get command line arguments
    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    // Generate config object
    ConfigMgr *configMgr = new ConfigMgr(vm);
    Config *config = configMgr->getConfig();

    // Detect daemon mode (Http Rest API)
    if (vm.count("daemon")) {        
        BOOST_LOG_TRIVIAL(info) << APP_NAME << " run in Daemon mode";
        BOOST_LOG_TRIVIAL(info) << "host : " << config->host << " port : " << config->port;

        Rest *rest = new Rest();
        return rest->connect(config->host, config->port);

        free(rest);
    }

    // Detect Cli Mode
    else if (vm.count("url")) {
        BOOST_LOG_TRIVIAL(info) << APP_NAME << " run in CLI mode";

        // Request URL
        std::string url = vm["url"].as<std::string>();
        WebResponse *webResponse = getWebResponse(url);
        webResponse->toString();

        free(webResponse);
    }

    free(configMgr);
    free(config);
    free(cli);
    
    return EXIT_SUCCESS;
}
