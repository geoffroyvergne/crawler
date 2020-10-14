# crawler

C++ web crawler

## Dependencies lib

## conan
boost/1.74.0
gtest/1.10.0
restinio/0.6.10
jsoncpp/1.9.4

gumbo-parser/0.10.1
libcurl/7.72.0

### FetchContent
gumbo-parser

### find_package( CURL )
libcurl


## Dependencies build

```
cmake
clang
conan
```

## Build

### Local

```

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/
```

### Docker

```
docker build . -t crawler
docker build -f Dockerfile -t crawler .
docker run --rm --name crawler hrawler --help

run -ti --rm crawler sh
docker run -ti --rm conanio/clang9-x86 bash
```

### Docker server mode

```
docker run -p 3000:3000 --name crawler -ti --rm crawler -d
curl localhost:3000/version
```

## Test

```
./build/bin/crawler_test
```

## Run

```
./build/bin/crawler_src_bin --help
crawler version :  1.0
Allowed options:
  --help                       Produce help message
  -v [ --version ]             Get version
  -d [ --daemon ]              Daemon mode
  -h [ --host ] arg (=0.0.0.0) Host to listen
  -p [ --port ] arg (=3000)    Port to listen
  -c [ --config ] arg          Configuration file name
  -u [ --url ] arg             URL to parse
```

### Server mode

```
./build/bin/crawler -d
./build/bin/crawler -d -c etc/test.ini

curl localhost:3000/index
{"code":200,"value":"Response OK"}

curl localhost:3000/version
{"code":200,"version":"1.0"}
```
## Web server test

```
cd var
build . -t web-server-test
docker run -d  --rm -p 80:80 --name web-server-test web-server-test

./build/bin/crawler -u http://localhost/test.html
./build/bin/crawler -u http://localhost/simple-test.html
```

