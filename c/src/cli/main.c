#include <stdio.h>
#include <stdlib.h>
#include <cli.h>
#include <config.h>
#include <http/http-client.h>
#include <html/tag.h>
#include <html/parser.h>

void printConfig(config conf) {    
    printf("Config : url=%s\n", conf.url);
}

/*int getSize (tag** t) {
    int size = 0;
    while ( *t++ ) ++size;

    return size;
}*/

int main(int argc, char **argv) {
    setbuf(stdout, NULL); 

    config conf = getOptions(argc, argv);

    printf("Crawler CLI : %s\n", conf.url);

    web_url* webUrl = parseUrl(conf.url);
    web_page* webPage = httpGet(conf.url);

    puts(web_url_to_string(webUrl));
    puts(web_page_to_string(webPage));

    //puts(webPage->content);

    tag** tag_array = parseString(webPage->content);
    //int tag_array_size = getSize(tag_array);
    //printf("%d\n", tag_array_size);

    return EXIT_SUCCESS;
}
