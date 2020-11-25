#include <iostream>
#include <getopt.h>
#include <cli.hpp>
#include <config.hpp>

config cli_get_options(int argc, char **argv) {
    int opt;
    int option_index = 0;

    config conf;    

    conf.port = 3000;    
    conf.host = "127.0.0.1";
    //conf.file = "";

    while ((opt = getopt_long(argc, argv, "vhp:h:t:c:o:", long_options_rest, &option_index)) != -1) {
        switch(opt) {
            case 0:
                break;
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                print_version();
                print_usage();
                exit(EXIT_SUCCESS);
                break;           
            case 'p':                
                conf.port = atoi(optarg);                
                break;
            case 'o':                
                conf.host = optarg;
                break;
            case 'c':                
                conf.file = optarg;                
                break;   
            case '?':
                break;
                exit(EXIT_FAILURE);
            default: print_usage(); 
                exit(EXIT_FAILURE);
        }
    }

    if(optind < argc) {
        std::cout << "non-option ARGV-elements:" << std::endl;
        while(optind < argc) {
            std::cout << argv[optind++] << std::endl;
        }
        
        exit(EXIT_FAILURE);
    }

    return conf;
}

void print_usage() {
    std::cout << "Usage: crawler" << std::endl;
}

void print_version() {
    std::cout << "version 1.0" << std::endl;
}
