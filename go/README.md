# Crawler go

## .bash_profil

```
export GOROOT=/usr/local/opt/go/libexec
export GOPATH=~/dev/crawler

export GOROOT=/usr/local/opt/go/libexec
export GOPATH=~/dev/github/crawler

export GOBIN=$GOPATH/bin
export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
```

## Init

go mod init example.com/crawler

go get .
go get github.com/pborman/getopt


## Run
```go run main.go```

