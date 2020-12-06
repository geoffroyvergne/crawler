#include <stdio.h>
#include <stdlib.h>
#include <cli.h>
#include <config.h>
#include <rest.h>

void printConfig(config conf) {    
    printf("Config : port=%d, host=%s\n", conf.port, conf.host);
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL); 

    config conf = cli_get_options(argc, argv);

    //printf("Crawler REST\n");
    printConfig(conf);

    rest_server_connect(conf.host, conf.port);

    return EXIT_SUCCESS;
}
