# crawler

C++ web crawler

## Dependencies build

```
cmake
clang
conan
```

## Build

```
mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/
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

curl localhost:3000/index
{"code":200,"value":"Response OK"}

curl localhost:3000/version
{"code":200,"version":"1.0"}
```
