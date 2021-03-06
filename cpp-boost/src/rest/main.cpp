#include <iostream>
//#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <app.h>

#include <cli.hpp>
#include <rest.hpp>
#include <config-mgr.hpp>

int main(int argc, char** argv) {
    setbuf(stdout, NULL);  

    //BOOST_LOG_TRIVIAL(info) << "Starting " << APP_NAME;
    std::cout << "Starting " << APP_NAME << std::endl;

    // Get command line arguments
    Cli *cli = new Cli(argc, argv);
    boost::program_options::variables_map vm = cli->getVariableMap();

    // Generate config object
    ConfigMgr *configMgr = new ConfigMgr(vm);
    Config *config = configMgr->getConfig();

    //BOOST_LOG_TRIVIAL(info) << "host : " << config->host << " port : " << config->port;
    std::cout << "host : " << config->host << " port : " << config->port << std::endl;

    Rest *rest = new Rest();
    return rest->connect(config->host, config->port);

    free(rest);
    free(configMgr);
    free(config);
    free(cli);
    
    return EXIT_SUCCESS;
}
