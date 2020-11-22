# crawler

C++ web crawler

## Dependencies lib

```
boost 
libcurl
gumbo-parser
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
clang++
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

### Docker build

```
docker build . -t crawler
docker build -f Dockerfile -t crawler .

run -ti --rm crawler sh

docker run -ti --rm crawler sh
docker run -ti --rm crawler bash

docker run --rm crawler crawler_cli --help
```

### Docker server mode

```
docker run -p 3000:3000 --name crawler --rm crawler

curl localhost:3000/version
```

### Docker cli mode

```
docker run --rm --name crawler crawler crawler_cli --help
```

## Unit Tests

```
./build/src/bin/crawler_test --log_level=all
```

## Run

```
./build/src/bin/crawler_cli --help
crawler Cli mode
crawler : 1.0
Allowed options:
  --help                Produce help message
  -v [ --version ]      Get version
  -u [ --url ] arg      URL to parse
```

### Server mode

```
./build/bin/crawler_rest
./build/bin/crawler_rest -c etc/test.ini

curl localhost:3000/index
{"code":200,"value":"Response OK"}

curl localhost:3000/version
{"code":200,"version":"1.0"}

curl -X POST \
-H 'Content-Type: application/json' \
-d '{"url":"http://localhost/simple-test.html"}' \
localhost:3000/url

```
## Web server test

```
cd var
docker build . -t web-server-test
docker run -d  --rm -p 80:80 --name web-server-test web-server-test

./build/bin/crawler -u http://localhost/test.html
./build/bin/crawler -u http://localhost/simple-test.html
```

## TODO

- [ X ] Escape json content
- [ X ] Test ini conf file
- [ X ] Add option for json pretty print
- [ ] Add more unit tests
- [ ] Filter html fields to parse
- [ ] Add tag filter in cli and ini
- [ ] Add Variable env in config
- [ ] Add host before relative uri
- [ ] Add A title rel and IMG width height il post body url endpoint
- [ ] Use with docker minimal image (static build)
- [ ] Add end slash on url if path is empty
- [ ] Add Memory Leak checker -Valgrind
- [ X ] Docker no log because of multi thread
- [ X ] Docker can't kill ctrl + c
- [ ] Add ssl to the API rest part
- [ ] 