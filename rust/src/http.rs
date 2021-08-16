use isahc::prelude::*;
//use crate::model;
use crate::model::HttpValues;

pub fn get_http(url: &str) -> Result<HttpValues, isahc::Error> {
    // Send a GET request and wait for the response headers.
    // Must be `mut` so we can read the response body.
    //let url = "http://localhost/simple-test.html";
    let mut response = isahc::get(url)?;

    if !response.status().is_success() {
        panic!("failed to get a successful response status!");
    }

    // Print some basic info about the response to standard output.
    //println!("Status: {}", response.status());
    //println!("Headers: {:#?}", response.headers());

    let mut headers = std::collections::HashMap::new();

    for key in response.headers().keys() {
        let value = response.headers().get(key);
    
        match value {
            Some(v) => headers.insert(key.to_string(), v.to_str().unwrap().to_string()),
            None    => headers.insert(key.to_string(), "".to_string()),
        };
    }

    let http_values = HttpValues {
        url: url.to_string(), 
        status: response.status().as_u16(),
        content: response.text()?,
        headers: headers,
    };

    //return (Ok(()), http_values);

    // Read the response body as text into a string and print it.
    //print!("{}", response.text()?);

    //println!("HttpValues: {:#?}", httpValues);

    Ok(http_values)
}
