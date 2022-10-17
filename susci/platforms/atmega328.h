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

#ifndef PLATFORMS_ATMEGA328_H_INCLUDED
#define PLATFORMS_ATMEGA328_H_INCLUDED

#ifdef MCU_ATMEGA_328

#include <avr/io.h>

#include "../kernel/platform.h"

#ifdef USE_HARDWARE_UART
#define USE_AVR_HARDWARE_UART
#endif

#ifdef USE_PINS
#define USE_AVR_PINS
#endif

#ifdef USE_PINCHANGE
#define USE_AVR_PINCHANGE
#endif

#ifdef USE_TWI_SLAVE
#define NOT_IMPLEMENTED
#endif
 
#ifdef USE_STORAGE
#define USE_AVR_STORAGE
#endif

/* Define values for this platform */
#define TICK_TIME(X) ((system_tick_t)((X) * ((F_CPU) / 1000) / 1024))

#define LOW_DDR (&DDRB)
#define LOW_PIN (&PINB)
#define LOW_PORT (&PORTB)
#define LOW_PCMSK (&PCMSK2)

#define GIMSK PCICR

#ifdef DIP_LAYOUT
#define PIN_1 14
#define PIN_2 16
#define PIN_3 17
#define PIN_4 18
#define PIN_5 19
#define PIN_6 20
#define PIN_7 ERROR_VCC
#define PIN_8 ERROR_GND
#define PIN_9 6
#define PIN_10 7
#define PIN_11 21
#define PIN_12 22
#define PIN_13 23
#define PIN_14 0
#define PIN_15 1
#define PIN_16 2
#define PIN_17 3
#define PIN_18 4
#define PIN_19 5
#define PIN_20 ERROR_VCC
#define PIN_21 ERROR_AREF
#define PIN_22 ERROR_GND
#define PIN_23 8
#define PIN_24 9
#define PIN_25 10
#define PIN_26 11
#define PIN_27 12
#define PIN_28 13
#endif

#define UCSRB UCSR0B
#define RXCIE RXCIE0
#define RXEN RXEN0
#define TXEN TXEN0
#define UCSZ0 UCSZ00
#define UCSZ1 UCSZ01
#define UDR UDR0
#define UDRE UDRE0
#define UCSRA UCSR0A
#define USART_RXC_vect USART_RX_vect
#define UBRRL UBRR0L
#define UBRRH UBRR0H
#define UCSRC UCSR0C
#define URSEL UCSZ0

#endif

#endif
