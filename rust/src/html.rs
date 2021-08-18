use scraper::{Html, Selector};
use crate::model::HtmlValues;

pub fn get_html(html: &str) ->  HtmlValues {
    let fragment = Html::parse_fragment(html);
    let selector = Selector::parse("h1").unwrap();

    let h1 = fragment.select(&selector).next().unwrap();
    let title = fragment.select(&selector).next().unwrap();

    let html_values = HtmlValues {
        title: title.inner_html(),
        h1 : h1.inner_html()
    };

    html_values
}
