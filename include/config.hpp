#include <iostream>

#ifndef CONFIG
#define CONFIG

//#pragma once
class Config {
    public:
        std::string file;
        std::string host;
        int port;
};

#endif
