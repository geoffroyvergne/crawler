use log::{info};

#[macro_use]
extern crate lazy_static;
use crate::configuration::CONFIGURATION;

use crate::model::{WebValues};

mod cli;
mod rest;
mod html;
mod http;
mod model;
mod configuration;

fn get_url(url: &str) {
    //let mut web_values = WebValues::new();

    match http::get_http(url) {
        Ok(http_values) => {
            let html_values = html::get_html(&http_values.content);

            let web_values = WebValues {
                http_values: http_values,
                html_values: html_values
            };

            //web_values

            let web_values_json = serde_json::to_string_pretty(&web_values).unwrap();
            info!("{:?}", web_values_json);
        },
        Err(e) => println!("{:?}", e),
        //Err(e) => web_values,
    };    

    //web_values
}

fn main() {
    env_logger::init();
    info!("Crawler");

    let matches = cli::get_cli();

    if matches.opt_present("u") {        
        match matches.opt_str("u") {
            Some(u) => {
                get_url(&u);
                /*let web_values = get_url(&u);
                let web_values_json = serde_json::to_string_pretty(&web_values).unwrap();
                info!("{:?}", web_values_json);*/
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
