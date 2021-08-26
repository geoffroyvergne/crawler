package main

import (
	"fmt"
	"io"
	"log"
	"strings"

	"golang.org/x/net/html"
)

type htmlValues struct {
	title string
	p     string
	h1    string
}

func getHtml(content *string) htmlValues {
	//fmt.Println("HTML " + content)

	htmlValues := htmlValues{}

	htmlMap := make(map[string][]string)

	textTags := []string{
		"title", "a", "p", "h1",
	}

	tag := ""
	enter := false

	tokenizer := html.NewTokenizer(strings.NewReader(*content))
	for {
		tt := tokenizer.Next()
		token := tokenizer.Token()

		err := tokenizer.Err()
		if err == io.EOF {
			break
		}

		switch tt {
		case html.ErrorToken:
			log.Fatal(err)
		case html.StartTagToken, html.SelfClosingTagToken:
			enter = false

			tag = token.Data
			for _, ttt := range textTags {
				if tag == ttt {
					enter = true
					break
				}
			}
		case html.TextToken:
			if enter {
				data := strings.TrimSpace(token.Data)

				if len(data) > 0 {
					//fmt.Println(tag + " : " + data)
					htmlMap[tag] = append(htmlMap[tag], data)
				}
			}
		}
	}

	for key, value := range htmlMap {
		fmt.Println("Tag:", key, "=>", "data:", value)
	}

	return htmlValues
}

/*func gettag(textTags string, tokenizer Tokenizer) string {
	tag := ""
	enter := false

	for {
		tt := tokenizer.Next()
		token := tokenizer.Token()

		err := tokenizer.Err()
		if err == io.EOF {
			break
		}

		switch tt {
		case html.ErrorToken:
			log.Fatal(err)
		case html.StartTagToken, html.SelfClosingTagToken:
			enter = false

			tag = token.Data
			for _, ttt := range textTags {
				if tag == ttt {
					enter = true
					break
				}
			}
		case html.TextToken:
			if enter {
				data := strings.TrimSpace(token.Data)

				if len(data) > 0 {
					//fmt.Println(tag + " : " + data)
					return data
				}
			}
		}
	}

	return ""
}*/
