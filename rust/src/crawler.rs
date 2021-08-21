use crate::model::{WebValues};
use crate::http;
use crate::html;

pub fn get_url(url: &str) -> WebValues {

    let mut web_values = WebValues {
        http_values: None,
        html_values: None
    };

    match http::get_http(url) {
        Ok(http_values) => {
            let html_values = html::get_html(&http_values.content);

            web_values.http_values = Some(http_values);
            web_values.html_values = Some(html_values);
        },
        Err(e) => {
            println!("{:?}", e);
        }
    };

    web_values
}
