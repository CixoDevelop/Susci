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

#ifndef DRIVERS_INTEGRATED_AVRPINS_H_INCLUDED
#define DRIVERS_INTEGRATED_AVRPINS_H_INCLUDED

/** \def pin_t
 * This is type for store pin number 
 */
typedef uint8_t pin_t;

/** \enum pin_direction_t
 * This is type for pin mode 
 */
typedef enum {

    /* Input state */
    INPUT = 0,

    /* Output state */
    OUTPUT = 1

} pin_direction_t;

/** \enum pin_state_t
 * This is type for binary pin state.
 */
typedef enum {

    /* Low state 0V */
    LOW = 0,
    
    /* High state 3V3 or 5V */
    HIGH = 1

} pin_state_t;

/** \fn create_pin_direction_pointer
 * This return pointer to register who is responsible for manage controller
 * pin direction (output mode).
 * @pin_number Number of pin
 */
static volatile uint8_t *create_pin_direction_pointer(pin_t pin_number) {
    return
        (volatile uint8_t *) (LOW_DDR  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_input_pointer
 * This return pointer to register who is responsible for manage controller
 * pin input (current state).
 * @pin_number Number of pin
 */
static volatile uint8_t *create_pin_input_pointer(pin_t pin_number) {
    return
        (volatile uint8_t *) (LOW_PIN  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_output_pointer
 * This return pointer to register who is responsible for manage controller
 * pin output.
 * @pin_number Number of pin
 */
static volatile uint8_t *create_pin_output_pointer(pin_t pin_number) {
    return
        (volatile uint8_t *) (LOW_PORT  + (((uint8_t) (pin_number / 8)) * 3));
}

/** \fn create_pin_mask
 * This return mask for pin given in parameter. You can use this mask
 * in access to pin in register.
 * @pin_number Number of pin
 */
static inline uint8_t create_pin_mask(pin_t pin_number) {
    return _BV(pin_number % 8);
}

/** \fn set_pin_direction
 * This set specified direction to specified pin. 
 * @pin_number Number of pin
 * @new_direction New pin direction
 */
static void set_pin_direction(pin_t pin_number, pin_direction_t new_direction) {
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
static void set_pin_state(pin_t pin_number, pin_state_t new_state) {
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
static pin_direction_t get_pin_direction(pin_t pin_number) {
    return (pin_direction_t) (
        (*create_pin_direction_pointer(pin_number) & create_pin_mask(pin_number)) 
        != 0
    );
}

/** \fn get_pin_state
 * This return current state of pin specified in parameter.
 * @pin_number Number of pin
 */
static pin_state_t get_pin_state(pin_t pin_number) {
    return (pin_state_t) (
        *create_pin_input_pointer(pin_number) & create_pin_mask(pin_number)
    );
}

#endif
