use scraper::{Html, Selector};

pub fn get_html(html: &str) {
    let fragment = Html::parse_fragment(html);
    let selector = Selector::parse("h1").unwrap();

    let h1 = fragment.select(&selector).next().unwrap();
    println!("h1 : {}", h1.inner_html());

    let title = fragment.select(&selector).next().unwrap();
    println!("title : {}", title.inner_html());
}
