use isahc::prelude::*;
use crate::model::HttpValues;

pub fn get_http(url: &str) -> Result<HttpValues, isahc::Error> {
    let mut response = isahc::get(url)?;

    if !response.status().is_success() {
        panic!("failed to get a successful response status!");
    }

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

    Ok(http_values)
}
