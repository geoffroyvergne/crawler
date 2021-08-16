use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct HttpValues {
    pub url: String,
    pub status: u16,
    pub content: String,
    pub headers: std::collections::HashMap<String, String>,
}
