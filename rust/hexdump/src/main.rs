use std::fs;
use std::cmp::Ordering;

const COLUMN_WIDTH: u8 = 4;

fn main() {
    let bytes = fs::read("prueba.png").expect("No se pudo leer el archivo");

    let mut offset: u64 = 0;
    let mut counter: u8 = 0;
    let mut char_bytes: [char; COLUMN_WIDTH as usize] = [' '; COLUMN_WIDTH as usize];

    for byte in bytes{

        let char_byte: char = char::from(byte);

        match counter.cmp(&COLUMN_WIDTH){
            Ordering::Less => {
                print!(" {:02X} ", byte);
                char_bytes[counter as usize] = char_byte;
                counter += 1;
                offset += 1;
            },

            Ordering::Equal | Ordering::Greater => {
                print!("\n {:08X}:   {:02X} ", offset, byte);
                counter = 1;
                offset += 1;
        
            }

        }
    }
}
