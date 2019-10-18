extern crate prusst;

use prusst::{Pruss, IntcConfig, Sysevt, Evtout};
use std::env;
use std::fs::File;

use std::path::PathBuf;

fn main() {
    
    let args: Vec<String> = env::args().collect();

    let filename= &args[1];

    let mut path = PathBuf::from("./");
    path.push(filename);

    let print = path.display();
    println!("Searching for {}", print);
    // let filename = &args[2];

    // println!("Searching for {}", query);
    // println!("In file {}", filename);

    // Configure and get a view of the PRU subsystem.
    let mut pruss = Pruss::new(&IntcConfig::new_populated()).unwrap();

    // Get a handle to an event out before it is triggered.
    let irq = pruss.intc.register_irq(Evtout::E0);

    // Open, load and run a PRU binary.
    let mut file = File::open(path).unwrap();

    pruss.intc.clear_sysevt(Sysevt::S19);
    let led_data :[u32; 7] = [0xffffffff;7];
    // let data: u32 =0xffffffff;
    // pruss.dram2.alloc(led_data);
    pruss.dram0.alloc(led_data);
    pruss.dram2.alloc(led_data);
    pruss.hostram.alloc(led_data);
    unsafe {pruss.pru0.load_code(&mut file).unwrap().run();}
    irq.wait();
    
    // Clear the triggering interrupt.

    // pruss.intc.send_sysevt(Sysevt::S18);
    // // Wait for the PRU code from hello.bin to trigger an event out.

    // Clear the triggering interrupt.
    pruss.intc.clear_sysevt(Sysevt::S19);

    // Do nothing: the `pruss` destructor will stop any running code and release ressources.
    println!("We are done...");
}
