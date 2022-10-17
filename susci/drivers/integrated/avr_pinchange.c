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
 * This file stores driver for setting pinchange interrupt on specified pins.
 */

#include "../../settings.h"
#include "../../platforms/avr.h"
#include "../../kernel/types.h"
#include "../../kernel/interface.h"
#include "pinchange.h"

#ifdef USE_AVR_PINCHANGE

#include <avr/io.h>
#include <avr/interrupt.h>

/** \fn setup_pinchange_on_pin
 * This function enable pinchange on specified pin.
 * @pin_number Number of pin
 */
void setup_pinchange_on_pin(pin_t pin_number) {
    volatile uint8_t *pcmask = LOW_PCMSK + (
		((uint8_t) (pin_number)) / 8
	);
    uint8_t mask = _BV (pin_number % 8);

    *pcmask |= mask;
}

/** \fn enable_pinchange_signal
 * This enable Pinchange interrupt in system. You must call them BEFORE 
 * setup pinchange on pins.
 */
void enable_pinchange_signal(void) {
    #ifdef PCMSK0
    PCMSK0 = 0x00;
    GIMSK |= (1 << PCIE0);
    #endif

    #ifdef PCMSK1
    PCMSK1 = 0x00;
    GIMSK |= (1 << PCIE1);
    #endif

    #ifdef PCMSK2
    PCMSK2 = 0x00;
    GIMSK |= (1 << PCIE2);
    #endif

    #ifdef PCMSK3
    PCMSK3 = 0x00;
    GIMSK |= (1 << PCIE3);
    #endif

    #ifdef PCMSK4
    PCMSK4 = 0x00;
    GIMSK |= (1 << PCIE4);
    #endif

    #ifdef PCMSK5
    PCMSK5 = 0x00;
    GIMSK |= (1 << PCIE5);
    #endif

    sei();
}

/* For all PCINT_vect make PINCHANGE_SIGNAL in system */
#ifdef PCINT_vect
ISR (PCINT_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT0_vect
ISR (PCINT0_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT1_vect
ISR (PCINT1_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT2_vect
ISR (PCINT2_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT3_vect
ISR (PCINT3_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT4_vect
ISR (PCINT4_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT5_vect
ISR (PCINT5_vect) { make_signal (PINCHANGE_SIGNAL); }
#endif

#endif
