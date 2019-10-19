#[no_mangle]
pub extern fn hello_rust() -> *const u8 {
    println!("in rust code!!!!");
    "Hello, world!\0".as_ptr()
}