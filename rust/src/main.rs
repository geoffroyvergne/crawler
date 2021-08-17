mod cli;
mod rest;
mod html;
mod http;
mod model;

/*#[derive(Debug, Clone, PartialEq)]
pub enum Node {
    Text(String),
    Test(String)
}*/

fn main() {
    println!("Crawler");

    //let node = Node::Text(String::from("test"));
    //println!("Node : {:#?}", node);

    /*match node {
        Some(n) => println!("Node : {}", n),
        None => println!("na")
    }*/

    cli::get_cli();
}
