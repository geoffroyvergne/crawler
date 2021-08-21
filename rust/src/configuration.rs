use std::{sync::Mutex};
use once_cell::sync::Lazy;

#[derive(Debug)]
pub struct Configuration {
    pub host: String,
    pub port: u16
}

pub static CONFIGURATION: Lazy<Mutex<Configuration>> = Lazy::new(|| {
    let configuration = Configuration {
        host: "127.0.0.1".to_string(),
        port: 3000
    };
    Mutex::new(configuration)
});
