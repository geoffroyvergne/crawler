#include <string.h>
#include <stdlib.h>

#define HTTPSERVER_IMPL
#include <httpserver.h>

#include <json/cJSON.h>
#include <web-response.h>

//#define RESPONSE "Hello, World!"
struct http_server_s* server;

void sig_handler(int signo);

char* parseRequestUrl(const char* json) {
    char* url = (char *) malloc(sizeof(char) * 5000);
    cJSON *UrlJson = cJSON_Parse(json);
    if (json != NULL) {
        url = cJSON_GetObjectItemCaseSensitive(UrlJson, "url")->valuestring;
    }

    free(UrlJson);
    //free(json);

    return url;
}

int request_target_is(struct http_request_s* request, char const * target) {
  http_string_t url = http_request_target(request);
  int len = strlen(target);
  return len == url.len && memcmp(url.buf, target, url.len) == 0;
}

char* getStatus(int code, char* message) {
    cJSON *resultJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(resultJson, "code", code);
    cJSON_AddStringToObject(resultJson, "message", message);

    return cJSON_PrintUnformatted(resultJson);
}

void handle_request(struct http_request_s* request) {

    struct http_response_s* response = http_response_init();

    char *bodyResponse = (char *) malloc(sizeof(char) * 5000000);

    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/plain");

    if (request_target_is(request, "/echo")) {
        puts("/echo");
        bodyResponse = getStatus(200, "hello");

    } else if(request_target_is(request, "/ping")) {        
        puts("/ping");
        bodyResponse = getStatus(200, "pong");

    } else if(request_target_is(request, "/version")) {
        puts("/version");
        bodyResponse = getStatus(200, "version");

    } else if(request_target_is(request, "/url")) {
        http_string_t method = http_request_method(request);
        
        if(strstr(method.buf, "POST") != NULL) {            
            http_string_t body = http_request_body(request);
            char* url = parseRequestUrl(body.buf);

            printf("/url : %s", url);

            web_response* webResponse = getWebResponse(url);
            bodyResponse = web_response_to_json(webResponse);
        } else {
            http_response_status(response, 405);
            bodyResponse = getStatus(405, "METHOD NOT ALLOWED");
        }
    } else {
        http_response_status(response, 404);
        bodyResponse = getStatus(404, "NOT FOUND");
    }

    http_response_body(response, bodyResponse, strlen(bodyResponse));
    http_respond(request, response);
}

void rest_server_connect(char* host, int port) {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("can't catch SIGINT\n");
    }

    server = http_server_init(port, handle_request);    
    http_server_listen_addr(server, host);
}

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("received SIGINT\n");
    free(server);

    exit(0);
  }
}
