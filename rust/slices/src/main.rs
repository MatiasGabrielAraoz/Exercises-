use std::{io::{self, stdin}, result::IterMut};

fn main(){
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Debes introducir texto");
    
    let word = first_word(&input);

    println!("{word}")
}

fn first_word(text: &str) -> &str{
    let bytes = text.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            let first_word = &text[..i];
            return first_word;
        }
    }
    let first_word = &text[..text.len()];
    first_word

}

