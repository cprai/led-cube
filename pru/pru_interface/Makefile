
TARGET = --target=armv7-unknown-linux-gnueabihf
LINKER = -C linker=arm-linux-gnueabihf-gcc

NFS_DIR = /home/misha/NFS/public/LEDCube/
OUT_DIR = ./target/armv7-unknown-linux-gnueabihf/debug
LIB_NAME = libpru_module.so
	

program :
	cargo build $(TARGET)
#	patchelf --set-interpreter /lib/ld-linux-armhf.so.3 $(OUT_DIR)/hello_world
	cp $(OUT_DIR)/$(LIB_NAME) $(NFS_DIR)
#	$(RUST_C) $(TARGET) $(LINKER) $(SOURCES) 
#	patchelf --set-interpreter /lib/ld-linux-armhf.so.3 $(TARGET)
