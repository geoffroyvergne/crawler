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
Crawler Version :  1.0
Allowed options:
  -h [ --help ]              produce help message 
  -v [ --version ]           get version
  -c [ --configuration ] arg Configuration fine name
  -u [ --url ] arg           URL to parse
```