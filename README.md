# Crawler C C++ C++ Boost Rust

## Web server test

```
cd var
docker build . -t web-server-test
docker run -d  --rm -p 80:80 --name web-server-test web-server-test

./build/bin/crawler -u http://localhost/test.html
./build/bin/crawler -u http://localhost/simple-test.html
```

