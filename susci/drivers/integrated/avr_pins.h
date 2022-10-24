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
 * This file stores drivers that is responsible for managment of microcontroller
 * pins. This can return pointers to hardware or atomic change pin state.
 */

#include "../../settings.h"
#include "../../kernel/types.h"
#include "../../platforms/avr.h"
#include "pins.h"

#ifndef DRIVERS_INTEGRATED_AVRPINS_H_INCLUDED
#define DRIVERS_INTEGRATED_AVRPINS_H_INCLUDED

#ifdef USE_AVR_PINS

/** \fn create_pin_direction_pointer
 * This return pointer to register who is responsible for manage controller
 * pin direction (output mode).
 * @pin_number Number of pin
 */
static inline volatile uint8_t *create_pin_direction_pointer(
	pin_t pin_number
) {
    return
        (volatile uint8_t *) (LOW_DDR  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_input_pointer
 * This return pointer to register who is responsible for manage controller
 * pin input (current state).
 * @pin_number Number of pin
 */
static inline volatile uint8_t *create_pin_input_pointer(
	pin_t pin_number
) {
    return
        (volatile uint8_t *) (LOW_PIN  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_output_pointer
 * This return pointer to register who is responsible for manage controller
 * pin output.
 * @pin_number Number of pin
 */
static inline volatile uint8_t *create_pin_output_pointer(
	pin_t pin_number
) {
    return
        (volatile uint8_t *) (LOW_PORT  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_mask
 * This return mask for pin given in parameter. You can use this mask
 * in access to pin in register.
 * @pin_number Number of pin
 */
static inline uint8_t create_pin_mask(
	pin_t pin_number
) {
    return _BV(pin_number % 8);
}

#endif


#endif
