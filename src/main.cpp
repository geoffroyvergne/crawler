#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/trivial.hpp>

#include <app.h>
#include <cli.hpp>
#include <ini.hpp>
#include <rest.hpp>
#include <config.hpp>

int main(int argc, char** argv) {
    BOOST_LOG_TRIVIAL(info) << "Starting " << APP_NAME;

    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    // Detect daemon mode (Http Rest API)
    if (vm.count("daemon")) {        
        BOOST_LOG_TRIVIAL(info) << "Daemon mode ... ";

        if (vm.count("host")) Config::host = vm["host"].as<std::string>();
        if (vm.count("port")) Config::port = vm["port"].as<int>();

        // Detect if configuration file is provided
        if (vm.count("config")) {
            Config::file = vm["config"].as<std::string>();
            std::cout << "Configuration file : " << Config::file << std::endl;

            Ini *ini = new Ini(Config::file);
            ini->getIniValues();

            free(ini);
        }

        BOOST_LOG_TRIVIAL(info) << APP_NAME << " run in Daemon mode";
        BOOST_LOG_TRIVIAL(info) << "host : " << Config::host << " port : " << Config::port;

        Rest *rest = new Rest();
        return rest->connect(Config::host, Config::port);

        free(rest);
    }

    // Detect Cli Mode
    else if (vm.count("url")) {
        std::string url = vm["url"].as<std::string>();
        BOOST_LOG_TRIVIAL(info) << "url : " << url;
    }

    free(cli);
    
    return EXIT_SUCCESS;
}
