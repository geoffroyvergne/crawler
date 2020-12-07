# crawler 

C web crawler

## Dependencies lib

```
inih
CuTest
libcurl
gumbo-parser
cJSON
```

### FetchContent
gumbo-parser

### find_package
boost
libcurl
libssl

## Dependencies build

```
cmake
clang
```

## Build

./build.sh && ./build/src/bin/crawler_cli --url http://localhost/test.html

## debug

lldb -- ./build/src/bin/crawler_cli --url http://localhost/test.html
r
bt

## run 

curl localhost:3000/version

curl -X POST \
-H 'Content-Type: application/json' \
-d '{"url":"http://localhost/simple-test.html"}' \
localhost:3000/url

## TODO

- [  ] add version and name in cmake variables
- [  ] add version in cli and rest /version
- [ X ] add post url rest
- [ X ] add rest return in json
- [ X ] group all json in one structure and function
- [  ] unit test all functions
- [  ] move external libraries in vendor directory
- [  ] 
