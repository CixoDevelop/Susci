![Logo](https://raw.githubusercontent.com/CixoDevelop/Susci/main/Logos/susci_hd.png)

# Susci - Operating system for small embedded devices
This project is an operating system for small non-MMU devices, currently mainly AVR microcontrollers, but plans to further extend support to other MCUs that are too weak to operate efficiently with systems such as FreeRTOS. This system has no expropriation, each process is a function that must terminate as quickly as possible for the system to decide which next one must be called. The system has functions such as:
 * Waiting for a certain time
 * Waiting for signal (may be from hardware interrupt)
 * Waiting for release by another process


## How to use it?
 * Clone this repo
 * You can remove LICENSE, README.md
 * Read core.c and select preferences
 * Write Your code in core.c and project/
 * Read descriptions and changes defaults values in make.sh
 * Build it with make.sh
 * Build docs with doxygen doxygen
 * For start writing read docs, if you can not mean any element, write to me!

## Update 22.10 v12 changes (Latest)
 * Improved formatting for better, more standard
 * Improving the file structure
 * Documentation added (FINALLY AFTER LONG PROMISE)
 * The current version allows you to work immediately on the cloned repository

## Update 22.10 v4 changes
 * Added drivers for managment pins (AVR)
 * Added Pinchange signal (AVR)
 * Added ShiftRegister driver (AVR + 74HC595)

## Update 22.8 v18 changes
 * Addes shared memory 
 * Added TWI slave support
 * Added USI TWI slave implementation for AtTiny devices
 
## Update 22.7 v26 changes
 * Added semaphores (down counting)
 * Buffers added (default 8 bytes)
 * CircularBuffers added (default 8 bytes)
 * Added the ability for the process to return an IDLE, which is considered a failed, and although the process was in READY state, another one will be executed
 * Scheduler has been broken down into smaller functions
 * Time management improved

## The project manager will be recreated and documentation will be added
