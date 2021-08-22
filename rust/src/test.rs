#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        assert_eq!(2, 2);
    }

    #[test]
    fn test_test() {
        assert_eq!(test(), "test".to_string());
    }
}
