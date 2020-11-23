#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cli.h>
#include <config.h>
#include <http/http-client.h>
#include <html/tag.h>
#include <html/parser.h>

void printConfig(config conf) {    
    printf("Config : url=%s\n", conf.url);
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL); 

    config conf = cli_get_options(argc, argv);

    printf("Crawler CLI : %s\n", conf.url);

    web_url* webUrl = parseUrl(conf.url);
    web_page* webPage = httpGet(conf.url);

    puts(web_url_to_string(webUrl));
    puts(web_page_to_string(webPage));
    
    tag** tag_array = parser_string(webPage->content);
    for(int i=0; i<parser_get_get_tagI(); i++) {
        puts(tag_to_string(tag_array[i]));
    }

    return EXIT_SUCCESS;
}
