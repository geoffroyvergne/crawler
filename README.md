# crawler

C++ web crawler

## Dependencies build

```
cmake
clang
conan
```

## Build

### Local

```
mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/
```

### Docker

```
docker build . -t crawler
docker build -f Dockerfile -t crawler .
docker run --rm --name crawler

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
./build/bin/crawler_test_bin
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
./build/bin/crawler_src_bin -d
./build/bin/crawler -d -c etc/test.ini

curl localhost:3000/index
{"code":200,"value":"Response OK"}

curl localhost:3000/version
{"code":200,"version":"1.0"}
```
