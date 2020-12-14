extern crate getopts;
use getopts::Options;
use std::env;

use crate::rest;

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
    opts.optflag("u", "url", "URL to query");

    let matches = match opts.parse(&args[1..]) {
        Ok(m) => { m }
        Err(f) => { panic!(f.to_string()) }
    };

    if matches.opt_present("h") {
        print_usage(&program, opts);
        return;
    }

    if matches.opt_present("r") {
        rest::get_rest();
    }

    if matches.opt_present("u") {
        println!("URL");
    }
}

