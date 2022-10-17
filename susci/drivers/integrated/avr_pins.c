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
#include "../../platforms/avr.h"
#include "../../kernel/types.h"
#include "pins.h"
#include "avr_pins.h"

#ifdef USE_AVR_PINS

#include <avr/io.h>
#include <avr/interrupt.h>

/** \fn set_pin_direction
 * This set specified direction to specified pin. 
 * @pin_number Number of pin
 * @new_direction New pin direction
 */
void set_pin_direction(pin_t pin_number, pin_direction_t new_direction) {
    uint8_t mask = create_pin_mask(pin_number);
    volatile uint8_t *direction = create_pin_direction_pointer(pin_number);

	/* This is atomic operation */
    uint8_t sreg = SREG;
    cli ();

    if (new_direction == OUTPUT) *direction |= mask;
    else *direction &= ~mask;

    SREG = sreg;
}

/** \fn set_pin_state
 * This set specified pin state to specified pin. Pin must be setup
 * as output.
 * @pin_number Number of pin
 * @new_state New pin state
 */
void set_pin_state(pin_t pin_number, pin_state_t new_state) {
    uint8_t mask = create_pin_mask(pin_number);
    volatile uint8_t *output = create_pin_output_pointer(pin_number);

    /* This is atomic operation */
    uint8_t sreg = SREG;
    cli();

    if (new_state == HIGH) *output |= mask;
    else *output &= ~mask;

    SREG = sreg;
}

/** \fn get_pin_direction
 * This return current direction of pin specified in parameter.
 * @pin_number Number of pin
 */
pin_direction_t get_pin_direction(pin_t pin_number) {
    return (pin_direction_t) (
        (*create_pin_direction_pointer(pin_number) & create_pin_mask(pin_number)) 
        != 0
    );
}

/** \fn get_pin_state
 * This return current state of pin specified in parameter.
 * @pin_number Number of pin
 */
pin_state_t get_pin_state(pin_t pin_number) {
    return (pin_state_t) (
        *create_pin_input_pointer(pin_number) & create_pin_mask(pin_number)
    );
}

#endif
