# crawler

C++ web crawler

# Build

# Run

curl localhost:3000/version

curl -X POST \
-H 'Content-Type: application/json' \
-d '{"url":"http://localhost/simple-test.html"}' \
localhost:3000/url

# Test

# Docker

### Docker build

```
docker build . -t crawler

docker run -ti --rm crawler bash
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

## debug

lldb -- ./build/src/bin/crawler_cli --url http://localhost/test.html
r
bt


# TODO

- [ ] Factorize WebResponse getWebResponse
- [ ] Factorize version and name management
- [ ] 
