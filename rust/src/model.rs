use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct HttpValues {
    pub url: String,
    pub status: u16,
    #[serde(skip_serializing)]
    pub content: String,
    pub headers: std::collections::HashMap<String, String>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct HtmlValues {
    pub title: String,
    pub h1: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct WebValues {
    pub http_values: Option<HttpValues>,
    pub html_values: Option<HtmlValues>
}

#[derive(Debug, Serialize, Deserialize)]
pub struct PostUrl {
    pub url: String
}

#[derive(Debug, Serialize, Deserialize)]
pub struct WebStatus {
    pub code: u16,
    pub message: String
}
