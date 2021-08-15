use serde::{Deserialize, Serialize};
use isahc::prelude::*;

#[derive(Serialize, Deserialize)]
struct HttpValues {
    //url: String,
    status: u16,
    //headers: std::collections::HashMap<String, String>,
}

pub fn get_http() -> Result<(), isahc::Error> {
    // Send a GET request and wait for the response headers.
    // Must be `mut` so we can read the response body.
    let mut response = isahc::get("http://localhost/simple-test.html")?;

    if !response.status().is_success() {
        panic!("failed to get a successful response status!");
    }

    // Print some basic info about the response to standard output.
    //println!("Status: {}", response.status());
    //println!("Headers: {:#?}", response.headers());

    let httpValues = HttpValues {
        status: response.status().as_u16(),
    };

    for key in response.headers().keys() {
        println!("{:?} : {:?}", key, response.headers().get(key));
    }

    /*let server = response.headers().get("server");
    
    match server {
        Some(s) => println!("Header server: {}", s.to_str().unwrap()),
        None    => println!("Header server empty"),
    }*/

    // Read the response body as text into a string and print it.
    print!("{}", response.text()?);

    //println!("HttpValues: {:#?}", httpValues);

    Ok(())
}
