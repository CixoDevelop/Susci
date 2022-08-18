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

#pragma once

/* Include all standard libraries for AVR */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Define values for this platform */
#define MAX_SYSTEM_TIME 65535
#define TICK_TIME(X) (SystemTick)(X * (F_CPU / 1000) / 1024)

typedef uint16_t SystemTick;

/* Include System plarform for override */
#include "../Kernel/Platform.h"

/*
 * Description
 * + This function is responsible for preparing the platform for the operating
 * + system to work, for example starting the system timer.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void
	platformInit (void)
{
    /* Run timer in 16 bit mode */
    TCCR0A = (1 << TCW0);

    /* And F_CPU / 1024 Hz frequency */
    TCCR0B = (1 << CS02) | (1 << CS00);
}

/*
 * Description
 * + This function takes the current state of the system timer and then returns
 * + it. Note, it pauses interrupts while it is running!
 *
 * Return: 1
 * + 16 bit integer value which is the current state of the system timer
 *
 * Params: 0
 * + void
 */
static SystemTick
    getTime (void)
{
    /* Save SREG */
    uint8_t sreg = SREG;

    /* Disable interrupt */
    cli ();

    /* Get TCNT0 */
    SystemTick actual_time = TCNT0L;
    actual_time  |= ((uint8_t) TCNT0H << 8);

    /* Restore SREG */
    SREG = sreg;

    /* Return TCNT0 */
    return actual_time;
}

/* Catch bad ISR so no reset occurs */
ISR (BADISR_vect) {}

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

    #define USE_TWI_SLAVE_TINY_IMPLEMENTATION

#endif
