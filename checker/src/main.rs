use std::io::{self, Write};
use std::fs::File;
use std::io::{BufReader, BufRead};
use num_bigint::BigInt;
use std::error::Error;

fn main() -> Result<(), Box<dyn Error>> {
    let filename = "fibonacci.txt";
    print!("Reading {} ... ", &filename);
    io::stdout().flush().unwrap();
    let file = File::open(filename)?;
    let reader = BufReader::new(file);
    let mut prev: BigInt = BigInt::from(0);
    let mut next: BigInt = BigInt::from(1);
    let mut n: u64 = 0;
    for line in reader.lines() {
        let num_str = line?;
        let num: BigInt = num_str.parse()?;
        if num != prev {
            eprintln!("ERROR: Wrong number at line {}", n + 1);
            return Ok(());
        }
        let tmp = next.clone();
        next += &prev;
        prev = tmp;
        n += 1;
        if n % 10_000 == 0 {
            print!("\rReading {} ... {} ", &filename, &n);
            io::stdout().flush().unwrap();
        }
    }
    println!("\nSUCCESS: {} Fibonacci numbers verified.", n);
    Ok(())
}
