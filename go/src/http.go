package main

import (
	"io"
	"net/http"
)

type httpValues struct {
	body   string
	status int
}

func getUrl(url *string) httpValues {
	httpValues := httpValues{}

	resp, err := http.Get(*url)

	if err != nil {
		// handle error
	}

	httpValues.status = resp.StatusCode

	/*for k, v := range resp.Header {
		fmt.Printf("Header field %q, Value %q\n", k, v)
	}*/

	//fmt.Printf("Accept : %q\n", resp.Header["Accept"])
	//fmt.Printf("Content-Type : %q\n", resp.Header["Content-Type"])

	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)

	httpValues.body = string(body)

	return httpValues
}
