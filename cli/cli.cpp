#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

#include <app.h>
#include <cli.hpp>
#include <config.hpp>

//Cli::Cli() {}

Cli::Cli(int argc, char** argv) {
    boost::program_options::variables_map variableMap;
    boost::program_options::options_description optionsDescription("Allowed options");

    try {
        optionsDescription.add_options()
            ("help", "Produce help message")
            ("version,v", "Get version")             
            ("url,u", boost::program_options::value<std::string>()->required(), "URL to parse")
        ;

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, optionsDescription), variableMap);
        boost::program_options::notify(variableMap);

    } catch (const boost::program_options::required_option & e) {
        if (variableMap.count("help")) {
            BOOST_LOG_TRIVIAL(info) << this->getVersion();
            this->getHelp(&optionsDescription);

            exit(EXIT_FAILURE);
        } else if (variableMap.count("version")) {
            BOOST_LOG_TRIVIAL(info) << this->getVersion();

            exit(EXIT_SUCCESS);
        } else {
            BOOST_LOG_TRIVIAL(error) << "error: " << e.what();
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
