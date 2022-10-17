/*
 * This file is part of the Susci project, an ultra lightweight general purpose
 * operating system aimed at devices without an MMU module and with very little
 * RAM memory.
 *
 * It is released under the terms of the MIT license, you can use Susca in your
 * projects, you just need to mention it in the documentation, manual or other
 * such place.
 *
 * Author: Cixo
 *
 *
 * This file stores data specific to the AVR ATtiny261 platform.
 */

#include "../settings.h"

#ifndef PLATFORMS_ATTINY261_H_INCLUDED
#define PLATFORMS_ATTINY261_H_INCLUDED

#ifdef MCU_ATTINY_261

#include <avr/io.h>

#include "../kernel/platform.h"

#ifdef USE_HARDWARE_UART
#define MCU_HAS_NOT_IT
#endif

#ifdef USE_PINS
#define USE_AVR_PINS
#endif

#ifdef USE_PINCHANGE
#define USE_AVR_PINCHANGE
#endif

#ifdef USE_TWI_SLAVE
#define USI_DATA USIDR
#define USI_CONTROL USICR
#define USI_STATUS USISR
#define SDA_PIN PINB
#define SDA_PORT PORTB
#define SDA_DDR DDRB
#define SDA_MASK _BV (0)
#define SCL_PIN PINB
#define SCL_PORT PORTB
#define SCL_DDR DDRB
#define SCL_MASK _BV (2)
#define USI_START_INTERRUPT USI_START_vect
#define USI_OVERFLOW_INTERRUPT USI_OVF_vect
#define USE_AVR_USI_TWI_SLAVE
#define USE_AVR_USI_TWI_SLAVE
#endif 

#ifdef USE_STORAGE
#define BYTE_EEPROM_ADDRESS
#define USE_AVR_STORAGE
#endif

/* Define values for this platform */
#define TICK_TIME(X) (SystemTick)(X * (F_CPU / 1000) / 1024)

#define LOW_DDR &DDRB
#define LOW_PIN &PINB
#define LOW_PORT &PORTB
#define LOW_PCMSK &PCMSK1

#ifdef DIP_LAYOUT
#define PIN_1 0
#define PIN_2 1
#define PIN_3 2
#define PIN_4 3
#define PIN_5 ERROR_VCC
#define PIN_6 ERROR_GND
#define PIN_7 4
#define PIN_8 5
#define PIN_9 6
#define PIN_10 7
#define PIN_11 15
#define PIN_12 14
#define PIN_13 13
#define PIN_14 12
#define PIN_15 ERROR_AVCC
#define PIN_16 ERROR_GND
#define PIN_17 11
#define PIN_18 10
#define PIN_19 9
#define PIN_20 8
#endif

#endif

#endif
