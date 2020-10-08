#include <iostream>
#include <boost/program_options.hpp>
#include <config.hpp>

class ConfigManager {
    public:
        ConfigManager(boost::program_options::variables_map vm);
        Config *getConfig();
    private:
        Config *config;
};
