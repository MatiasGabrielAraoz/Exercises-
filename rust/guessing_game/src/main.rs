use std::{cmp::Ordering, io};
use rand::Rng;


fn main() {
    print!("insertá un numero del 1 al 100: \n");
    
    let random_number = rand::thread_rng().gen_range(1..=100);


    loop {
            
        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("No se pudo leer la linea");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        
        match guess.cmp(&random_number) {
            Ordering::Less => println!("muy bajo"),
            Ordering::Equal => {
                println!("Ganaste");
                break;
            },
            Ordering::Greater => println!("muy alto")
        };
    }

}
