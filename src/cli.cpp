#include <iostream>
#include <boost/program_options.hpp>

#include <config.h>
#include <cli.hpp>

Cli::Cli(int argc, char** argv) {
    boost::program_options::variables_map variableMap;

    try {
        boost::program_options::options_description optionsDescription("Allowed options");
        optionsDescription.add_options()
            ("help,h", "produce help message ")
            ("version,v", "get version")    
            ("configuration,c", boost::program_options::value<std::string>(), "Configuration fine name")
        ;

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, optionsDescription), variableMap);
        boost::program_options::notify(variableMap);

        if (variableMap.count("help")) {
            this->getVersion();
            this->getHelp(&optionsDescription);

            exit(EXIT_SUCCESS);
        }

        if (variableMap.count("version")) {
            this->getVersion();
            
            exit(EXIT_SUCCESS);
        }

    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    this->variableMap = variableMap;
}

void Cli::getVersion() {
    std::cout << "Crawler Version :  " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
}

void Cli::getHelp(boost::program_options::options_description *optionsDescription) {
    std::cout << *optionsDescription << std::endl;
}

boost::program_options::variables_map Cli::getVariableMap() {
    return this->variableMap;;
}
