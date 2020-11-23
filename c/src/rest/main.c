#include <stdio.h>
#include <stdlib.h>
#include <cli.h>
#include <config.h>

void printConfig(config conf) {    
    printf("Config : port=%d, host=%s, target=%s\n", conf.port, conf.host, conf.target);
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL); 

    config conf = cli_get_options(argc, argv);

    //printf("Crawler REST\n");
    printConfig(conf);

    return EXIT_SUCCESS;
}
