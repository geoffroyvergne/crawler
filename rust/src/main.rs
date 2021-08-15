mod cli;
mod rest;
mod html;
mod http;

fn main() {
    println!("Crawler");

    cli::get_cli();
}
