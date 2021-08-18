#[derive(Debug)]
pub struct Configuration {
    pub host: &'static str,
    pub port: u16
}

lazy_static! {
    #[derive(Debug)]
    pub static ref CONFIGURATION: Configuration = {
        let configuration = Configuration {
            host: "127.0.0.1",
            port: 3000
        };
        configuration
    };
}
