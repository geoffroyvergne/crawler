#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include <http/web-page.h>
#include <http/web-url.h>
#include <http/http-client.h>

struct memoryStruct {
  char *memory;
  size_t size;
};
 
// https://curl.se/libcurl/c/getinmemory.html
static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct memoryStruct *mem = (struct memoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

web_url* parseUrl(char* url) {

    //web_url webUrl;
    web_url* webUrl = malloc(sizeof(web_url));
    //webUrl->url = malloc(sizeof(char*) * 20000);
    webUrl->host = malloc(sizeof(char*) * 20000);
    webUrl->path = malloc(sizeof(char*) * 20000);
    webUrl->port = malloc(sizeof(int*));
    webUrl->sheme = malloc(sizeof(char*) * 2000);

    CURLU *curlu;
    CURLUcode ucode;

    //char *host;
    //std::string host;
    //char *path;

    curlu = curl_url();
    if(!curlu) return NULL;

    ucode = curl_url_set(curlu, CURLUPART_URL, url, 0);

    ucode = curl_url_get(curlu, CURLUPART_HOST, &webUrl->host, 0);
    //if(!ucode) {
        //printf("Host name : %s \n", host);
        //std::cout << "Hostname : " << host << std::endl;
        //webUrl->host = host;      
    //}

    ucode = curl_url_get(curlu, CURLUPART_PATH, &webUrl->path, 0);
    //if(!ucode) {
        //printf("Path : %s \n", path);
        //std::cout << "Path : " << path << std::endl;
        
        //webUrl->path = path;        
    //}

    //curl_free(path);
    //curl_free(host);
    
    return webUrl;
}

web_page* httpGet(char* url) {

    web_page* webPage = malloc(sizeof(web_page));
    webPage->content =  malloc(sizeof(char*) * 5000005);
    webPage->contentType =  malloc(sizeof(char*) * 20000);
    webPage->elapsed = malloc(sizeof(int*));
    webPage->header =  malloc(sizeof(char*) * 2000);
    //webPage->httpCode = malloc(sizeof(int*));
    webPage->port = malloc(sizeof(int*));
    webPage->sheme =  malloc(sizeof(char*) * 2000);
    //webPage->url =  malloc(sizeof(char*) * 2000);

    struct memoryStruct chunk;
    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */ 

    CURL *curl = curl_easy_init();    

    if(curl) {        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        
        //char* content;        
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webPage->content);

        //CURLcode res = curl_easy_perform(curl);
        curl_easy_perform(curl);

        //char* headerString;        
        //curl_easy_setopt(curl, CURLOPT_HEADERDATA, &webPage->header);

        //std::cout << "content : " << content.length() << std::endl;
        //std::cout << "header : " << headerString.length() << std::endl;
        //webPage->content = content;
        //webPage->header = headerString;
        //strcpy(webPage->header, headerString);

        //std::string *contentType;
        char *contentType;
        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);
        //std::cout << "Content type : " << contentType << std::endl;        
        //webPage->contentType = contentType;
        strcpy(webPage->contentType, contentType);
        //puts(webPage->contentType);

        int httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        //std::cout << "HTTP result : " << httpCode << std::endl;
        webPage->httpCode = httpCode;

        //double elapsed;
        //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //std::cout << "elapsed : " << elapsed << std::endl;
        //webPage->elapsed = elapsed;

        //char* effectiveUrl;
        //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
        //std::cout << "url : " << url << std::endl;
        //webPage->url = effectiveUrl;
        //puts(webPage->url);
        //strcpy(webPage->url, effectiveUrl);

        //printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
        //webPage->content = (char *) malloc( sizeof(char) * 2000 );
        strncpy(webPage->content, chunk.memory, chunk.size);
        //strcpy(webPage->content, "");
        //webPage->content = chunk.memory;

        //puts(chunk.memory);

        //CURLINFO_HTTP_VERSION
        //CURLINFO_SCHEME
        //CURLINFO_TOTAL_TIME

        free(chunk.memory);
        
        /* cleanup curl stuff */ 
        curl_easy_cleanup(curl);
        
        /* we're done with libcurl, so clean it up */ 
        curl_global_cleanup();
    }

    return webPage;
}

/*char* getHtmlContent() {
    return NULL;
}

web_url* getWebUrl() {
    return NULL;
}

web_page* getWebPage() {
    return NULL;
}

void getResults() {

}

void fail(CURL *h) {
    curl_url_cleanup(h);
    EXIT_FAILURE;
}*/
