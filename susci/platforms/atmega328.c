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
 * This file stores data specific to the AVR ATmega328 platform.
 */

#include "../settings.h"
#include "../kernel/platform.h"
#include "atmega328.h"

#ifdef MCU_ATMEGA_328

#include <avr/io.h>
#include <avr/interrupt.h>

/** \fn platform_init
 * This function is responsible for preparing the platform for the operating
 * system to work, for example starting the system timer.
 */
void platform_init(void) {
    /* Run timer in 16 bit mode */
    TCCR1A = 0x00;

    /* And F_CPU / 1024 Hz frequency */
    TCCR1B = (1 << CS12) | (1 << CS10);
}

/** \fn get_time
 * This function takes the current state of the system timer and then returns
 * it. Note, it pauses interrupts while it is running!
 */
system_tick_t get_time(void) {
    /* Run this opetation atomic */
    uint8_t sreg = SREG;

    cli();
    
    system_tick_t current_time = TCNT1L;
    current_time  |= ((uint8_t) TCNT1H << 8);

    SREG = sreg;

    return current_time;
}

/* Catch bad ISR so no reset occurs */
ISR (BADISR_vect) {}

#endif
