extern crate getopts;
use getopts::Options;
use std::env;

use crate::rest;
use crate::html;
use crate::http;

fn get_url(url: &str) {
    match http::get_http(url) {
        Err(e) => println!("{:?}", e),
        Ok(http_results) => {
            html::get_html(&http_results.content);            
        },
    };    
}

fn print_usage(program: &str, opts: Options) {
    let brief = format!("Usage: {} FILE [options]", program);
    print!("{}", opts.usage(&brief));
}

pub fn get_cli() {
    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();

    let mut opts = Options::new();

    opts.optflag("h", "help", "print this help menu");
    opts.optflag("r", "rest", "run rest API");
    opts.optopt("u", "url", "URL to query", "NAME");

    let matches = match opts.parse(&args[1..]) {
        Ok(m) => { m }
        Err(f) => { panic!("{}", f.to_string()) }   
    };

    if matches.opt_present("h") {
        print_usage(&program, opts);
        return;
    }

    if matches.opt_present("r") {
        rest::get_rest();
    }

    if matches.opt_present("u") {        
        match matches.opt_str("u") {
            Some(u) => get_url(&u),
            None => panic!("{}", "Url mandatory !"),
        };
    }
}

