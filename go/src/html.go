package main

import (
	"fmt"

	"golang.org/x/net/html"
)

func getHtml(content *string) {
	fmt.Println("HTML")

	tokenizer := html.NewTokenizer(content)
}
