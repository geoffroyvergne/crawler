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
            ("host,h", boost::program_options::value<std::string>()->default_value("0.0.0.0"), "Host to listen")
            ("port,p", boost::program_options::value<int>()->default_value(3000), "Port to listen")
            ("config,c", boost::program_options::value<std::string>(), "Configuration file name")            
        ;

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, optionsDescription), variableMap);
        boost::program_options::notify(variableMap);

        if (variableMap.count("help")) {
            this->getVersion();
            this->getHelp(&optionsDescription);

            exit(EXIT_SUCCESS);
        }

        if (variableMap.count("version")) {
            BOOST_LOG_TRIVIAL(info) << this->getVersion();
            
            exit(EXIT_SUCCESS);
        }

    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch(...) {
        BOOST_LOG_TRIVIAL(error) << "Exception of unknown type!";
        exit(EXIT_FAILURE);
    }

    this->variableMap = variableMap;
}

std::string Cli::getVersion() {
    std::string version;

    version.append(APP_NAME);
    version.append(" : ");
    version.append(std::to_string(VERSION_MAJOR));
    version.append(".");
    version.append(std::to_string(VERSION_MINOR));

    return version;
}

void Cli::getHelp(boost::program_options::options_description *optionsDescription) {
    std::cout << *optionsDescription << std::endl;
}

boost::program_options::variables_map Cli::getVariableMap() {
    return this->variableMap;;
}
