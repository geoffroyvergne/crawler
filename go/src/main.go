package main

import (
	"fmt"
	//"log"
)

func main() {
	fmt.Println("Crawler")
	cli := getCli()

	if *cli.optRest {
		fmt.Println("Rest API")
	}

	if len(*cli.optName) > 0 {
		fmt.Println("Hello " + *cli.optName + "!")
	}

	if len(*cli.optUrl) > 0 {
		fmt.Println("url : " + *cli.optUrl)

		body := getUrl(cli.optUrl).body

		//fmt.Println(body)
		getHtml(&body)
	}
}
