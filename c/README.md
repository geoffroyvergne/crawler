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

## TODO

- [  ] Docker service do not stops ctrl+c
- [  ] 