mod cli;
mod rest;

fn main() {
    println!("Hello, world!");

    cli::get_cli();
    rest::get_rest();
}
