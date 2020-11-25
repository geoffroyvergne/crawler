#include <iostream>
#include <rest/httplib.h>
#include <rest/rest-server.hpp>
#include <config.hpp>
#include <cli.hpp>
#include <INIReader.h>


int main(int argc, char** argv) {
    
    config conf = cli_get_options(argc, argv);

    if(!conf.file.empty()) {
        INIReader reader(conf.file);

        if (reader.ParseError() != 0) {
            std::cout << "Can't load '../etc/test.ini'" << std::endl;
            return EXIT_FAILURE;
        }

        conf.port = reader.GetInteger("http", "port", 3000);
        conf.host = reader.Get("http", "host", "127.0.0.1");
    }

    std::cout << "Crawler REST host : " << conf.host << " port : " << conf.port << std::endl;

    RestServer* restServer = new RestServer(conf.host, conf.port);
    restServer->connect();

    return EXIT_SUCCESS;
}
