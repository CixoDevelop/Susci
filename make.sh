#!/bin/bash

GCC=avr-gcc #Or gcc for Your MCU
SIZE=avr-size #Or Your size command
MCU=attiny261 #Or Your MCU

$GCC -o core.bin core.c -mmcu=$MCU -Os -Wall -Wextra -Wpedantic -Wno-unused-function -Wno-array-bounds
$SIZE -C --mcu $MCU core.bin
