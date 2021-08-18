use log::{info};
use actix_web::{get, post, web, App, HttpResponse, HttpRequest, HttpServer, Responder};
use crate::configuration::CONFIGURATION;
use crate::model::{WebStatus, PostUrl};

async fn greet(req: HttpRequest) -> impl Responder {
    let name = req.match_info().get("name").unwrap_or("World");
    format!("Hello {}!", &name)
}

async fn index() -> impl Responder {
    web::Json(WebStatus { code: 200, message: "index".to_string() })
}

#[get("/hello")]
async fn hello() -> impl Responder {
    HttpResponse::Ok().body("Hello world!")
}

#[post("/url")]
async fn url(req_body: String) -> impl Responder {    
    let body: PostUrl = serde_json::from_str(&req_body).unwrap();
    info!("Url : {}", body.url);

    HttpResponse::Ok()
        .content_type("application/json")
        .body(req_body)
}

#[actix_web::main]
async fn connect() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .service(hello)            
            .service(url)
            .route("/test", web::get().to(greet))
            .route("/test/{name}", web::get().to(greet))
            .route("/", web::get().to(index))
            .route("/index", web::get().to(index))
    })
    //.bind("127.0.0.1:3000")?
    //.bind(("127.0.0.1", 3000))?
    .bind((CONFIGURATION.host, CONFIGURATION.port))?
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

