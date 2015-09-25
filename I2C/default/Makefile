###############################################################################
# Makefile for the project I2C
###############################################################################

## General Flags
PROJECT = I2C
MCU = atmega128
TARGET = I2C.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=I2C.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\ZOLI\OKTATAS\TANFOLYAM\SAMPLE\C\I2C\." 

## Objects that must be built in order to link
OBJECTS = I2Csample.o I2C_tools.o arit_tools.o SPI_tools.o Display.o general.o LM75_TempSensor.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) I2C.hex I2C.eep I2C.lss size

## Compile
I2Csample.o: ../I2Csample.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

I2C_tools.o: ../I2C_tools.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

arit_tools.o: ../arit_tools.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

SPI_tools.o: ../SPI_tools.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Display.o: ../Display.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

general.o: ../general.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

LM75_TempSensor.o: ../LM75_TempSensor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) I2C.elf dep/* I2C.hex I2C.eep I2C.lss I2C.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

