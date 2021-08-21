extern crate getopts;
use getopts::{Options, Matches};
use std::env;
use log::{info};

fn print_usage(program: &str, opts: Options) {
    let brief = format!("Usage: {} FILE [options]", program);
    info!("{}", opts.usage(&brief));
}

pub fn get_cli() -> Matches {
    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();

    let mut opts = Options::new();

    opts.optflag("h", "help", "print this help menu");
    opts.optflag("t", "test", "print test");
    opts.optflag("c", "config", "print configuration");
    opts.optflag("r", "rest", "run rest API");
    opts.optopt("u", "url", "URL to query", "<URL>");
    opts.optopt("s", "host", "Host to expose", "<HOST>");
    opts.optopt("p", "port", "Port to expose", "<PORT>");

    let matches = match opts.parse(&args[1..]) {
        Ok(m) => { m }
        Err(f) => { panic!("{}", f.to_string()) }   
    };

    if matches.opt_present("help") {
        print_usage(&program, opts);
        ()       
    }    

    matches
}

