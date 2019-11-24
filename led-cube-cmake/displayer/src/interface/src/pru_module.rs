use libc;
use libc::{c_uint};
use std::fs::File;
use std::path::PathBuf;
use std::slice;
use::prusst::{Pruss,IntcConfig, Sysevt, Evtout, EvtoutIrq, MemSegment, Host};

use std::{thread, time};

pub struct PruModule<'a>{
    pru: Pruss<'a>,
    num_leds: u32,
    irq: EvtoutIrq,
}


impl<'a> PruModule<'a>{
    fn new(num_leds: u32) -> PruModule<'a>{
        let mut pru = Pruss::new(&IntcConfig::new_populated()).unwrap();
        let irq = pru.intc.register_irq(Evtout::E0);

        println!("reading pru binary file\n");
        let mut pru_binary = File::open(PathBuf::from("./pru_binary.bin")).unwrap();

        let led_data:[u32;7] = [0x11111111;7];

        // let led_data:[u32;7] = [0x0000001,0x00000020,0x00000300,0x00004000,0x00040000,0x00500000,0x00700000];
        let mut ref_to_pru_array = pru.dram0.alloc(led_data);
        println!("unwrapping pru binary file \n");
        let mut code = pru.pru0.load_code(&mut pru_binary).unwrap();
  
        // let mut ref_to_pru_array = unsafe {pru.dram0.alloc_uninitialized::<[u8; 7]>();}
        // for el in (*ref_to_pru_array).iter_mut(){
        //     *el = 0x11111111;
        //     println!("{}",*el);
        // }

        unsafe { code.run();}
        PruModule{
            pru:pru,
            num_leds:num_leds,
            irq:irq,
        }
    }

    fn update(&mut self,led_data: &[u32]){ 
        print!("Calling update function \n");
        // thread::sleep(time::Duration::from_millis(1000));

        let mut led_data_copy:[u32;7] = [0x00000000;7];
        led_data_copy.clone_from_slice(led_data);
        println!("{:?}", led_data_copy);

        self.pru.dram0.alloc(led_data_copy);
        self.pru.intc.send_sysevt(Sysevt::S18);

        self.irq.wait();
        // Clear the triggering interrupt.
        println!("recieved signal from pru(inside update) \n");
        self.pru.intc.clear_sysevt(Sysevt::S19);
        self.pru.intc.enable_host(Host::Evtout0);
        thread::sleep(time::Duration::from_millis(2000));
    }
}

#[no_mangle]
pub extern "C" fn pru_module_new(num_leds:c_uint) -> *mut PruModule<'static>{
    Box::into_raw(Box::new(PruModule::new(num_leds)))
}

#[no_mangle]
pub extern "C" fn pru_module_update(ptr: *mut PruModule,new_data: *const c_uint ){
    let module = unsafe{ &mut *ptr};
    let new_led_data: &[c_uint] = unsafe{slice::from_raw_parts(new_data, module.num_leds as usize)};
    module.update(new_led_data);
}

#[no_mangle]
pub extern "C" fn pru_module_shutdown(ptr: *mut PruModule){
    // let module = unsafe{ &*ptr};
    // module.shutdown();
    // unsafe{Box::from_raw(ptr);}
}

#[no_mangle]
pub extern "C" fn pru_module_test(ptr: *mut PruModule){
    // let module = unsafe{ &*ptr};
    // module.test();
}
