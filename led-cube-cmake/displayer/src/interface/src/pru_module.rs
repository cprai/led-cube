use libc;
use libc::{c_uint};
use std::fs::File;
use std::path::PathBuf;
use std::slice;
use::prusst::{Pruss,IntcConfig, Sysevt, Evtout, EvtoutIrq, MemSegment, Host, PruCode, Intc};

use std::{thread, time};

pub struct PruModule<'a>{
    // pru: Pruss<'a>,
    num_leds: u32,
    irq: EvtoutIrq,
    code:PruCode<'a>,
    ref_data:&'a mut [u32;7],
}


impl<'a> PruModule<'a>{
    fn new<'b>(pruss: &'b mut Pruss<'b>,num_leds: u32) -> PruModule<'b>{
        let num_leds = 7;
        // let mut pru = Pruss::new(&IntcConfig::new_populated()).unwrap();
        let irq = (*pruss).intc.register_irq(Evtout::E0);

        println!("reading pru binary file\n");
        let mut pru_binary = File::open(PathBuf::from("./pru_binary.bin")).unwrap();

        // let led_data:[u32;7] = [0x00000001;7];

        let led_data:[u32;7] = [0x0000001,0x00000020,0x00000300,0x00004000,0x00040000,0x00500000,0x00700000];
        
        println!("unwrapping pru binary file \n");
        let mut ref_to_pru_array = (*pruss).dram0.alloc(led_data);
        let mut code = (*pruss).pru0.load_code(&mut pru_binary).unwrap();
        unsafe {code.run();}
        // let mut ref_to_pru_array = unsafe {pru.dram0.alloc_uninitialized::<[u8; 7]>();}
        // for el in (*ref_to_pru_array).iter_mut(){
        //     *el = 0x00000001;
        //     println!("{}",*el);
        // }

        // self.pru.intc.send_sysevt(Sysevt::S18);
  
        // thread::sleep(time::Duration::from_millis(2000));
        // code.halt();

        // for el in (*ref_to_pru_array).iter_mut(){
        //     *el = 0x00111000;
        //     println!("{}",*el);
        // }
        // unsafe {code.run();}
        // (*pruss).intc.send_sysevt(Sysevt::S18);  
        // thread::sleep(time::Duration::from_millis(2000));
        
        PruModule {
            num_leds:num_leds,
            irq:irq,
            code:code,
            ref_data:ref_to_pru_array,
        }
    }

    fn update<'b>(&mut self,pruss:&'b mut Pruss<'b>,led_data: &[u32]){ 
        // print!("Calling update function \n");
        // thread::sleep(time::Duration::from_millis(1000));
        println!("led_data_conents{:?}", led_data);

        let irq = (*pruss).intc.register_irq(Evtout::E0);

        // let mut led_data_copy:[u32;7] = [0x00000000;7];
        // let led_data1:[u32;7] = [0x0000001,0x00000001,0x00000001,0x00000000,0x00000000,0x00000000,0x00000000];
        // led_data_copy.clone_from_slice(led_data);
        self.code.halt();
        // (*self.ref_data).clone_from_slice(&led_data_copy);
           
        for x in 0..7 {
            let a = led_data[x];

            self.ref_data[x]=a;
        }

        // (*pruss).dram0.alloc(led_data_copy);
        // thread::sleep(time::Duration::from_millis(1000));
         println!("ref data is: {:?}",(*self.ref_data));
        unsafe{self.code.run();}
        (*pruss).intc.send_sysevt(Sysevt::S18);
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
pub extern "C" fn pru_module_new(pruss:*mut Pruss<'static>,num_leds:c_uint) -> *mut PruModule<'static>{
    let pruss = unsafe{&mut *pruss};
    Box::into_raw(Box::new(PruModule::new(pruss,num_leds)))
}

#[no_mangle]
pub extern "C" fn pru_module_update(ptr:*mut PruModule,pruss:*mut Pruss<'static>,new_data: *const libc::uint32_t ){
    let pruss = unsafe{&mut *pruss};
    let module = unsafe{ &mut *ptr};
    let new_led_data: &[u32] = unsafe{slice::from_raw_parts(new_data, module.num_leds as usize)};
    module.update(pruss,new_led_data);
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
