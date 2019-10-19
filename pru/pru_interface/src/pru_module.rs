use libc;
use libc::{c_uint};
use std::fs::File;
use std::path::PathBuf;
use std::slice;
use::prusst::{Pruss,IntcConfig, Sysevt};
use std::mem;

pub struct PruModule<'a>{
    pru: Pruss<'a>,
    num_leds: u32,
}

impl<'a> PruModule<'a>{
    fn new(num_leds: u32) -> PruModule<'a>{
        // initalize interface to pru
        let mut pru = Pruss::new(&IntcConfig::new_populated()).unwrap();
        // read binary file; 
        let mut file = File::open(PathBuf::from("./pru_binary.bin")).unwrap();
        

        // let led_data = vec![0x00ffffff; num_leds as usize]; 
        // let leds:[u32;7]=[0xffffffff;7];
        // pru.dram2.alloc(leds);
        let leds1:[u32;7] = [0x00000001,0x00000010,0x00000100,0x00001000,0x00010000,0x00100000,0x00ffffff];
        let leds2:[u32;1024] = [0x00000000;1024];

        // pru.dram0.alloc(leds);
        let mut segments = pru.dram0.split_at(mem::size_of::<[u32;7]>());
        segments.0.alloc(leds1);
        segments.1.alloc(leds2);
        let begin = segments.1.begin();
        let end = segments.1.end();
        println!("begin at {} and end at {}", begin, end);


        // pru.hostram.alloc(leds);

        unsafe {pru.pru0.load_code(&mut file).unwrap().run();}

        PruModule{
            pru:pru,
            num_leds:num_leds,
        }
    }

    fn update(&mut self,led_data: &[u32]){
        self.pru.dram0.alloc(led_data);
        self.pru.intc.send_sysevt(Sysevt::S18);
    }

    fn shutdown(&self){
        self.pru.intc.send_sysevt(Sysevt::S19);
    }

    fn test(&self){
        
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
    let module = unsafe{ &*ptr};
    module.shutdown();
    unsafe{Box::from_raw(ptr);}
}

#[no_mangle]
pub extern "C" fn pru_module_test(ptr: *mut PruModule){
    let module = unsafe{ &*ptr};
    module.test();
}
