#include <config-mgr.hpp>
#include <boost/program_options.hpp>
#include <ini.hpp>

ConfigMgr::ConfigMgr(boost::program_options::variables_map vm) {
    this->config = new Config();

    // Cli config
    if (vm.count("host")) config->host = vm["host"].as<std::string>();
    if (vm.count("port")) config->port = vm["port"].as<int>();

    // Ini config
    if (vm.count("config")) {
        config->file = vm["config"].as<std::string>();
        std::cout << "Configuration file : " << config->file << std::endl;

        Ini *ini = new Ini(config->file);
        boost::property_tree::ptree propertyTree = ini->getPtree();

        if(!propertyTree.empty()) {
            config->host = propertyTree.get<std::string>("http.host");
            config->port = propertyTree.get<int>("http.port");
        }

        free(ini);
    }

    // TODO Env variables
}

Config *ConfigMgr::getConfig() {
    return this->config;
}
