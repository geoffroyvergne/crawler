#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cli.h>
#include <config.h>
#include <http/http-client.h>
#include <html/tag.h>
#include <html/parser.h>
#include <web-response.h>

void printConfig(config conf) {    
    printf("Config : url=%s\n", conf.url);
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL); 

    config conf = cli_get_options(argc, argv);

    printf("Crawler CLI : %s\n", conf.url);

    web_response* webResponse = getWebResponse(conf.url);
    puts(web_response_to_string(webResponse));
    puts(web_response_to_json(webResponse));

    return EXIT_SUCCESS;
}
