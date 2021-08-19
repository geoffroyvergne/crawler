use log::{info};

#[macro_use]
extern crate lazy_static;

use crate::configuration::CONFIGURATION;

mod cli;
mod rest;
mod html;
mod http;
mod model;
mod configuration;
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
        rest::get_rest();
    }

    if matches.opt_present("c") {
        info!("{:#?}", CONFIGURATION);
        info!("{}:{}", CONFIGURATION.host, CONFIGURATION.port);
    }

    if matches.opt_present("t") {
        info!("Test");
    }
}
