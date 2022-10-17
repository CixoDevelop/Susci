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
#include "pins.h"

#ifndef DRIVERS_INTEGRATED_PINCHANGE_H_INCLUDED
#define DRIVERS_INTEGRATED_PINCHANGE_H_INCLUDED

#ifdef USE_AVR_PINCHANGE

/** \def PINCHANGE_SIGNAL
 * Signal in system to trigger on pinchange 
 */
#define PINCHANGE_SIGNAL 0x20

/** \fn setup_pinchange_on_pin
 * This function enable pinchange on specified pin.
 * @pin_number Number of pin
 */
void setup_pinchange_on_pin(pin_t pin_number);

/** \fn enable_pinchange_signal
 * This enable Pinchange interrupt in system. You must call them BEFORE 
 * setup pinchange on pins.
 */
void enable_pinchange_signal(void);

#endif

#endif
