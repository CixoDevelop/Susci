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

/** \fn set_pin_direction
 * This set specified direction to specified pin. 
 * @pin_number Number of pin
 * @new_direction New pin direction
 */
void set_pin_direction(pin_t pin_number, pin_direction_t new_direction);

/** \fn set_pin_state
 * This set specified pin state to specified pin. Pin must be setup
 * as output.
 * @pin_number Number of pin
 * @new_state New pin state
 */
void set_pin_state(pin_t pin_number, pin_state_t new_state);

/** \fn get_pin_direction
 * This return current direction of pin specified in parameter.
 * @pin_number Number of pin
 */
pin_direction_t get_pin_direction(pin_t pin_number);

/** \fn get_pin_state
 * This return current state of pin specified in parameter.
 * @pin_number Number of pin
 */
pin_state_t get_pin_state(pin_t pin_number);

#endif

#endif
