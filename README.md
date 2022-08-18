![Logo](https://raw.githubusercontent.com/CixoDevelop/Susci/main/Logos/susci_hd.png)

# Susci - Operating system for small embedded devices
This project is an operating system for small non-MMU devices, currently mainly AVR microcontrollers, but plans to further extend support to other MCUs that are too weak to operate efficiently with systems such as FreeRTOS. This system has no expropriation, each process is a function that must terminate as quickly as possible for the system to decide which next one must be called. The system has functions such as:
 * Waiting for a certain time
 * Waiting for signal (may be from hardware interrupt)
 * Waiting for release by another process

## Install for avr-gcc (Linux only)
sudo ./Manager.py -i

## Latest update changes
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
