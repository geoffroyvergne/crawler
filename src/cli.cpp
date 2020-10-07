#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

#include <config.h>
#include <cli.hpp>

Cli::Cli(int argc, char** argv) {
    boost::program_options::variables_map variableMap;

    try {
        boost::program_options::options_description optionsDescription("Allowed options");
        optionsDescription.add_options()
            ("help,h", "Produce help message ")
            ("version,v", "Get version") 
            ("daemon,d", "Daemon mode")    
            ("configuration,c", boost::program_options::value<std::string>(), "Configuration fine name")
            ("url,u", boost::program_options::value<std::string>(), "URL to parse")
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
        //std::cerr << "error: " << e.what() << std::endl;
        BOOST_LOG_TRIVIAL(error) << "error: " << e.what();
    } catch(...) {
        //std::cerr << "Exception of unknown type!" << std::endl;
        BOOST_LOG_TRIVIAL(error) << "Exception of unknown type!";
    }

    this->variableMap = variableMap;
}

void Cli::getVersion() {
    BOOST_LOG_TRIVIAL(info) << "Crawler Version :  " << VERSION_MAJOR << "." << VERSION_MINOR;
    //std::cout << "Crawler Version :  " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
}

void Cli::getHelp(boost::program_options::options_description *optionsDescription) {
    std::cout << *optionsDescription << std::endl;
}

boost::program_options::variables_map Cli::getVariableMap() {
    return this->variableMap;;
}
