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

#pragma once

/* Signal in system to trigger on pinchange */
#define PINCHANGE_SIGNAL 0x20

/*
 * Description
 * + This function enable pinchange on specified pin.
 *
 * Return: 0
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static void
    setupPinchangeOnPin (Pin pin_number)
{
    volatile uint8_t *pcmask = LOW_PCMSK + (
		((uint8_t) (pin_number)) / 8
	);
    uint8_t mask = _BV (pin_number % 8);

    *pcmask |= mask;
}

/*
 * Description
 * + This enable Pinchange interrupt in system.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static void
    enablePinchangeSignal ()
{
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

    sei ();
}

/* For all PCINT_vect make PINCHANGE_SIGNAL in system */
#ifdef PCINT_vect
    ISR (PCINT_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT0_vect
    ISR (PCINT0_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT1_vect
    ISR (PCINT1_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT2_vect
    ISR (PCINT2_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT3_vect
    ISR (PCINT3_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT4_vect
    ISR (PCINT4_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif

#ifdef PCINT5_vect
    ISR (PCINT5_vect) { makeSignal (PINCHANGE_SIGNAL); }
#endif
