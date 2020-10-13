#include <iostream>
#include <boost/program_options.hpp>
#include <config.hpp>

#ifndef CONFIG_MGR
#define CONFIG_MGR

//#pragma once
class ConfigMgr {
    public:
        ConfigMgr(boost::program_options::variables_map vm);
        Config *getConfig();
    private:
        Config *config;
};

#endif
