#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/trivial.hpp>

#include <cli.hpp>
#include <ini.hpp>
#include <rest.hpp>

int main(int argc, char** argv) {
    BOOST_LOG_TRIVIAL(info) << "Web Crawler";

    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    if (vm.count("configuration")) {
        std::string configurationFile = vm["configuration"].as<std::string>();
        std::cout << "Configuration file : " << configurationFile << std::endl;

        Ini *ini = new Ini(configurationFile);
        ini->getIniValues();

        free(ini);
    }

    if (vm.count("daemon")) {        
        BOOST_LOG_TRIVIAL(info) << "Daemon mode ... ";

        Rest *rest = new Rest();
        return rest->connect("0.0.0.0", 3000);

        free(rest);
    }

    if (vm.count("url")) {
        std::string url = vm["url"].as<std::string>();
        BOOST_LOG_TRIVIAL(info) << "url : " << url;
    }

    free(cli);
    
    return EXIT_SUCCESS;
}
