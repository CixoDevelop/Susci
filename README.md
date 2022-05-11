# Susci - Operating system for small embedded devices
This project is an operating system for small non-MMU devices, currently mainly AVR microcontrollers, but plans to further extend support to other MCUs that are too weak to operate efficiently with systems such as FreeRTOS. This system has no expropriation, each process is a function that must terminate as quickly as possible for the system to decide which next one must be called. The system has functions such as:
 * Waiting for a certain time
 * Waiting for signal (may be from hardware interrupt)
 * Waiting for release by another process

## Install for avr-gcc (Linux only)
sudo ./Manager.py -i

## Soon the documentation will be published and the number of MCUs running the system will be increased!
