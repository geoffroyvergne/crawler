package main

import (
	"os"

	"github.com/pborman/getopt"
)

type cli struct {
	optName *string
	optUrl  *string
	optHelp *bool
	optRest *bool
}

func getCli() *cli {

	cli := cli{}
	cli.optName = getopt.StringLong("name", 'n', "", "Your name")
	cli.optUrl = getopt.StringLong("url", 'u', "", "URL to parse")
	//cli.optHelp = getopt.BoolLong("help", 0, "Help")
	cli.optRest = getopt.BoolLong("rest", 0, "Run Rest API")
	getopt.Parse()

	if *getopt.BoolLong("help", 0, "Help") {
		getopt.Usage()
		os.Exit(0)
	}

	return &cli

}
