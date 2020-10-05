#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

#include <cli.hpp>
#include <ini.hpp>

int main(int argc, char** argv) {
    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    if (vm.count("configuration")) {
        std::string configurationFile = vm["configuration"].as<std::string>();
        std::cout << "Configuration file : " << configurationFile << std::endl;

        Ini *ini = new Ini(configurationFile);
        ini->getIniValues();

        free(ini);
    }

    free(cli);
    
    return EXIT_SUCCESS;
}
