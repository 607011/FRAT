use std::fs::File;
use std::io::{BufWriter, Write};
use num_bigint::BigInt;

fn main() -> std::io::Result<()> {
    let chunk_size = 100_000;
    let filename = "fibonacci.txt";
    let mut file = File::create(filename)?;
    let mut writer = BufWriter::new(&mut file);
    let mut a = BigInt::from(0);
    let mut b = BigInt::from(1);
    let mut n = 0;
    loop {
        for _ in 0..chunk_size {
            writer.write_all(format!("{}\n", a).as_bytes())?;
            let c = &a + &b;
            a = b;
            b = c;
        }
        writer.flush()?;
        n += chunk_size;
        println!("{} total numbers written.", n);
    }
}
