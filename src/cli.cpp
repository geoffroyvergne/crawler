#include <iostream>
#include <boost/program_options.hpp>
#include "config.h"
#include "cli.hpp"

namespace po = boost::program_options;

void getVersion() {
    std::cout << "Crawler Version :  " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
}

void getHelp(po::options_description *desc) {
    std::cout << *desc << std::endl;
}

void initCli(int argc, char** argv) {
    po::variables_map vm;

    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message ")
            ("version,v", "get version")           
        ;

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            getVersion();
            getHelp(&desc);

            exit(EXIT_SUCCESS);
        }

        if (vm.count("version")) {
            getVersion();
            exit(EXIT_SUCCESS);
        }

    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return ;
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    //return vm;
}
