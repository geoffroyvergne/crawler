#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

#include <app.h>
#include <cli.hpp>
#include <config.hpp>

Cli::Cli(int argc, char** argv) {
    boost::program_options::variables_map variableMap;

    try {
        boost::program_options::options_description optionsDescription("Allowed options");
        optionsDescription.add_options()
            ("help", "Produce help message")
            ("version,v", "Get version") 
            ("daemon,d", "Daemon mode")
            ("host,h", boost::program_options::value<std::string>()->default_value("0.0.0.0"), "Host to listen")
            ("port,p", boost::program_options::value<int>()->default_value(3000), "Port to listen")
            ("config,c", boost::program_options::value<std::string>(), "Configuration file name")
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
        BOOST_LOG_TRIVIAL(error) << "error: " << e.what();
        exit(EXIT_FAILURE);
    } catch(...) {
        BOOST_LOG_TRIVIAL(error) << "Exception of unknown type!";
        exit(EXIT_FAILURE);
    }

    this->variableMap = variableMap;
}

void Cli::getVersion() {
    BOOST_LOG_TRIVIAL(info) << APP_NAME << " version :  " << VERSION_MAJOR << "." << VERSION_MINOR;
}

void Cli::getHelp(boost::program_options::options_description *optionsDescription) {
    std::cout << *optionsDescription << std::endl;
}

boost::program_options::variables_map Cli::getVariableMap() {
    return this->variableMap;;
}
