# Crawler go

## .bash_profil

```
export GOROOT=/usr/local/opt/go/libexec
export GOPATH=/Users/gv/dev/crawler
export GOBIN=$GOPATH/bin
export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
```

## Init

go mod init example.com/crawler

go get .
go get github.com/pborman/getopt
go get github.com/pborman/getopt/v2

## Run
```go run main.go```

