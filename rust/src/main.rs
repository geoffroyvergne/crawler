use log::{info};
use crate::configuration::CONFIGURATION;

mod cli;
mod html;
mod http;
mod model;
mod configuration;
mod rest;

#[path = "crawler.rs"]
mod crawler;

fn main() {
    env_logger::init();
    info!("Crawler");

    let matches = cli::get_cli();

    if matches.opt_present("u") {     
        match matches.opt_str("u") {
            Some(u) => {                                
                let web_values = crawler::get_url(&u);
                let web_values_json = serde_json::to_string_pretty(&web_values).unwrap();
                info!("{:?}", web_values_json);
            },
            None => panic!("{}", "Url mandatory !"),
        };
    }

    if matches.opt_present("r") {        
        match matches.opt_str("s") {
            Some(s) => {                                
                CONFIGURATION.lock().unwrap().host = s;
                info!("host : {:#?}", CONFIGURATION.lock().unwrap().host);
            },
            None => {
                info!("no host");                                
            },
        };

        match matches.opt_str("p") {
            Some(p) => {                                
                CONFIGURATION.lock().unwrap().port = p.parse::<u16>().unwrap();
                info!("port : {:#?}", CONFIGURATION.lock().unwrap().port);
            },
            None => {
                info!("no port");                                
            },
        };
        
        rest::get_rest();
    }

    if matches.opt_present("c") {
        info!("{:#?}", CONFIGURATION.lock().unwrap());
        info!("Host : {}", CONFIGURATION.lock().unwrap().host);
        info!("Port : {}", CONFIGURATION.lock().unwrap().port);
    }

    if matches.opt_present("t") {
        info!("Test");
    }
}

#[allow(dead_code)]
fn test() -> String {
    "test".to_string()
}