
PRU_ASM = clpru
PRU_HEX = hexpru
ASM_FLAGS = --silicon_version=3

LINKER = -z am335x_PRU.cmd

INSTALL_DIR = ..

SOURCES = led_pru.c

TARGET_DIR = /home/misha/NFS/public/LEDCube
TARGET = test.bin

OBJ = $(SOURCES:.c=.obj)
ELF = $(SOURCES:.c=.elf)

$(TARGET_DIR)/$(TARGET): $(ELF)
	$(PRU_HEX) -b -o $@ $< --quiet

$(ELF): $(OBJ)
	$(PRU_ASM) $(LINKER) -o $@ $< 


$(OBJ): $(SOURCES)
	$(PRU_ASM) $(ASM_FLAGS) -c $(SOURCES)


clean :
	rm -r $(OBJ) $(ELF)

#
# %.elf: %.obj $(LINKER_CMD)
# 	$(PRU_ASM) $(LINKER_CMD) -o $@ $<