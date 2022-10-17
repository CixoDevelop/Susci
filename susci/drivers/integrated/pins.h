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
 * This file stores headers for drivers that is responsible for managment of
 * microcontroller pins.
 */
 
#ifndef DRIVERS_INTEGRATED_PINS_H_INCLUDED
#define DRIVERS_INTEGRATED_PINS_H_INCLUDED
 
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

#endif
