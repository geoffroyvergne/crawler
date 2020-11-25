#include <iostream>

#ifndef CONFIG
#define CONFIG

typedef struct {
    std::string url; 
    int port;
    std::string host;    
    std::string file;
} config;

#endif
