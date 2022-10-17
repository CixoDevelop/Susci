target = core.bin
source = core.c
mcu = atmega328

susci_source = $(shell find susci/ -type f -name '*.c')
susci_object = $(patsubst %.c, %.o, $(susci_source))

CC = avr-gcc
CC_FLAGS = -mmcu=$(mcu) -Oz -Wall -Wextra -Wpedantic -fshort-enums 
CC_FLAGS += -Wl,--gc-sections -fdata-sections -ffunction-sections 
CC_FLAGS += -Wfatal-errors -std=c99 -fearly-inlining -Wno-array-bounds 
CC_FLAGS += -Wno-unused-parameter

SIZE = avr-size
SIZE_FLAGS = --mcu $(mcu) -C 

default: all

.PHONY: clean_susci clean

clean_susci:
	rm -rf $(susci_object)	

clean:
	rm -rf $(target)

$(susci_object): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(target): $(susci_object)
	$(CC) $(CC_FLAGS) $(susci_object) $(source) -o $(target) 

build: $(susci_object)
	$(CC) $(CC_FLAGS) $(susci_object) $(source) -o $(target) 

size: $(target)
	$(SIZE) $(SIZE_FLAGS) $(target)
	
all: clean build size

