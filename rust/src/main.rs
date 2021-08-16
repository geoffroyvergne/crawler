mod cli;
mod rest;
mod html;
mod http;
mod model;

fn main() {
    println!("Crawler");

    cli::get_cli();
}
