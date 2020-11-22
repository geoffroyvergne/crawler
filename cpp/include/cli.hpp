#include <boost/program_options.hpp>

#ifndef CLI
#define CLI

//#pragma once
class Cli {
    public:
        //Cli();
        Cli(int argc, char** argv);
        boost::program_options::variables_map getVariableMap();
        std::string getVersion();
        
    private:
        boost::program_options::variables_map variableMap;
        
        void getHelp(boost::program_options::options_description *optionsDescription);
};

#endif
