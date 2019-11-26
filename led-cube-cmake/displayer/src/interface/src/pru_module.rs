use libc;
use libc::{c_uint};
use std::fs::File;
use std::path::PathBuf;
use std::slice;
use::prusst::{Pruss,IntcConfig, Sysevt, Evtout, Host, PruCode,};

use std::{thread, time};

const NUM_LEDS: usize = 7;

pub struct PruModule<'a>{
    code:PruCode<'a>,
    ref_data:&'a mut [u32;NUM_LEDS],
}


impl<'a> PruModule<'a>{
    fn new<'b>(pruss: &'b mut Pruss<'b>) -> PruModule<'b>{

        println!("reading pru binary file\n");
        let mut pru_binary = File::open(PathBuf::from("./pru_binary.bin")).unwrap();

        let led_data:[u32;NUM_LEDS] = [0x00000000;NUM_LEDS];
        let ref_to_pru_array = (*pruss).dram0.alloc(led_data);
        let mut code = (*pruss).pru0.load_code(&mut pru_binary).unwrap();
        unsafe {code.run();}
        
        PruModule {
            code:code,
            ref_data:ref_to_pru_array,
        }
    }

    fn update<'b>(&mut self,pruss:&'b mut Pruss<'b>,led_data: &[u32]){ 
        let irq = (*pruss).intc.register_irq(Evtout::E0);

        self.code.halt();
        (*self.ref_data).clone_from_slice(led_data);
        unsafe{self.code.run();}

        // wake up pru; 
        (*pruss).intc.send_sysevt(Sysevt::S18);
        // wait for signal from pru 
        irq.wait();
        (*pruss).intc.clear_sysevt(Sysevt::S19);
        (*pruss).intc.enable_host(Host::Evtout0);

        thread::sleep(time::Duration::from_millis(1000));
    }
}


#[no_mangle]
pub extern "C" fn pruss_new() -> *mut Pruss<'static>{
    Box::into_raw(Box::new(Pruss::new(&IntcConfig::new_populated()).unwrap()))
}


#[no_mangle]
pub extern "C" fn pru_module_new(pruss:*mut Pruss<'static>) -> *mut PruModule<'static>{
    let pruss = unsafe{&mut *pruss};
    Box::into_raw(Box::new(PruModule::new(pruss)))
}

#[no_mangle]
pub extern "C" fn pru_module_update(ptr:*mut PruModule,pruss:*mut Pruss<'static>,new_data: *const u32 ){
    let pruss = unsafe{&mut *pruss};
    let module = unsafe{ &mut *ptr};
    let new_led_data: &[u32] = unsafe{slice::from_raw_parts(new_data, NUM_LEDS)};
    module.update(pruss,new_led_data);
}

// #[no_mangle]
// pub extern "C" fn pru_module_shutdown(ptr: *mut PruModule){
//     // let module = unsafe{ &*ptr};
//     // module.shutdown();
//     // unsafe{Box::from_raw(ptr);}
// }