
PRU_ASM = clpru
PRU_HEX = hexpru
ASM_FLAGS = --silicon_version=3

# LINKER = -z am335x_PRU.cmd
LINKER = -z am335x_pru_imem.cmd 

INSTALL_DIR = ..

SOURCES = led_pru.c

TARGET_DIR = /home/misha/NFS/public/led-cube
TARGET = pru_binary.bin

OBJ = $(SOURCES:.c=.obj)
ELF = $(SOURCES:.c=.elf)

STACK_SIZE=0x100
HEAP_SIZE=0x100

LFLAGS = --stack_size=$(STACK_SIZE) --heap_size=$(HEAP_SIZE)

$(TARGET_DIR)/$(TARGET): $(ELF)
	$(PRU_HEX) -b -o $@ $< --quiet
	# $(PRU_HEX) -o $(TARGET_DIR)/$(TARGET) $(ELF) --quiet
	# $(PRU_HEX) -b -o $(TARGET_DIR)/$(TARGET) $(ELF) --quiet

$(ELF): $(OBJ)
	$(PRU_ASM) $(LINKER) -m pru.map -o $@ $< 


$(OBJ): $(SOURCES)
	$(PRU_ASM) $(ASM_FLAGS) -c $(SOURCES)

clean :
	rm -r $(OBJ) $(ELF) *.b10

#
# %.elf: %.obj $(LINKER_CMD)
# 	$(PRU_ASM) $(LINKER_CMD) -o $@ $<