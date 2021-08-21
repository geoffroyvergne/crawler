use log::{info};
use actix_web::{post, web, App, HttpResponse, HttpServer, Responder};
use crate::configuration::CONFIGURATION;
use crate::model::{WebStatus, PostUrl};

#[path = "crawler.rs"]
pub mod crawler;

async fn index() -> impl Responder {
    web::Json(WebStatus { code: 200, message: "index".to_string() })
}

#[post("/url")]
async fn url(req_body: String) -> impl Responder {    
    let body: PostUrl = serde_json::from_str(&req_body).unwrap();
    info!("Url : {}", body.url);

    let web_values = crawler::get_url(&body.url);

    HttpResponse::Ok()
        .content_type("application/json")
        .json(web_values)
}

#[actix_web::main]
async fn connect() -> std::io::Result<()> {
    let host = CONFIGURATION.lock().unwrap().host.to_string();
    let port = CONFIGURATION.lock().unwrap().port;

    HttpServer::new(|| {
        App::new()                    
            .service(url)            
            .route("/", web::get().to(index))
            .route("/index", web::get().to(index))
    })
    //.bind(("127.0.0.1", 3000))?
    .bind((host, port))?
    .run()
    .await
}

pub fn get_rest() {    
    info!("REST");

    match connect() {
        Err(e) => println!("{:?}", e),
        _ => ()
    }    
}
