LED_CUBE_CMAKE = ../led-cube-cmake
OUT_DIR = /home/misha/NFS/public/led-cube/
TARGET = led-testing
PRU = ../pru

pru-module:
	cd pru && make

led-cube-module:
	mkdir -p led-cube && cd ./led-cube && cmake $(LED_CUBE_CMAKE)
	cd led-cube && make
	patchelf --set-interpreter /lib/ld-linux-armhf.so.3 $(OUT_DIR)/$(TARGET)

lcm-make: 
	cd led-cube && make
	patchelf --set-interpreter /lib/ld-linux-armhf.so.3 $(OUT_DIR)/$(TARGET)

clean: 
	cd pru && make clean

all : pru-module led-cube-module
