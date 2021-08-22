# Crawler rust

https://docs.rs/getopts/0.2.21/getopts/
https://actix.rs/

## Build

```cargo build```

```cargo build --release```

## Run

```cargo run```

```cargo run -- -h```
```cargo run -- --help```

## Enable logging
```export RUST_LOG=info```

## Unit Test

```cargo test```

## Test

curl -X POST \
-H 'Content-Type: application/json' \
-d '{"url":"http://localhost/test.html"}' \
localhost:3000/url
