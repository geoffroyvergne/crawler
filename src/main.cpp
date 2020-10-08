#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <app.h>
#include <cli.hpp>
#include <rest.hpp>
#include <config-manager.hpp>

#include <http/http-client.hpp>

int main(int argc, char** argv) {
    BOOST_LOG_TRIVIAL(info) << "Starting " << APP_NAME;

    // Get command line arguments
    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    // Generate config object
    ConfigManager *configManager = new ConfigManager(vm);
    Config *config = configManager->getConfig();

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
        std::string url = vm["url"].as<std::string>();

        HttpClient *httpClient = new HttpClient(url);
        httpClient->getResults();
        
        free(httpClient);
    }

    free(config);
    free(cli);
    
    return EXIT_SUCCESS;
}
