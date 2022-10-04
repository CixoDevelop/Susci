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

#pragma once

/* This is type for store pin number */
typedef uint8_t Pin;

/* This is type for pin mode */
typedef enum {
    INPUT = 0,
    OUTPUT = 1
} PinDirection;

/* This is type for binary pin state */
typedef enum {
    LOW = 0,
    HIGH = 1
} PinState;

/*
 * Description
 * + This return pointer to register who is responsible for manage controller
 * + pin direction (output mode).
 *
 * Return: 1
 * + volatile uint8_t*: Pointer to register
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static volatile uint8_t*
    createPinDirectionPointer (Pin pin_number)
{
    return
        (volatile uint8_t *) (LOW_DDR  + (((uint8_t) (pin_number / 8)) * 3));
}

/*
 * Description
 * + This return pointer to register who is responsible for manage controller
 * + pin input (current state).
 *
 * Return: 1
 * + volatile uint8_t*: Pointer to register
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static volatile uint8_t*
    createPinInputPointer (Pin pin_number)
{
    return
        (volatile uint8_t *) (LOW_PIN  + (((uint8_t) (pin_number / 8)) * 3));
}

/*
 * Description
 * + This return pointer to register who is responsible for manage controller
 * + pin output.
 *
 * Return: 1
 * + volatile uint8_t*: Pointer to register
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static volatile uint8_t*
    createPinOutputPointer (Pin pin_number)
{
    return
        (volatile uint8_t *) (LOW_PORT  + (((uint8_t) (pin_number / 8)) * 3));
}

/*
 * Description
 * + This return mask for pin given in parameter. You can use this mask
 * + in access to pin in register.
 *
 * Return: 1
 * + uint8_t: Pin mask
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static uint8_t
    createPinMask (Pin pin_number)
{
    return _BV (pin_number % 8);
}

/*
 * Description
 * + This set specified direction to specified pin. 
 *
 * Return: 0
 *
 * Params: 2
 * + Pin pin_number: Number of pin
 * + PinDirection new_direction: New pin direction
 */
static void
    setPinDirection (Pin pin_number, PinDirection new_direction)
{
	/* Pointer and mask to hardware */
    uint8_t mask = createPinMask (pin_number);
    volatile uint8_t *direction = 
		createPinDirectionPointer (pin_number);

	/* Prepare atomic operation */
    uint8_t sreg = SREG;
    cli ();

	/* Set specified direction */
    if (new_direction == OUTPUT)
        *direction |= mask;
    else
        *direction &= ~mask;

	/* End atomic operation */
    SREG = sreg;
}

/*
 * Description
 * + This set specified pin state to specified pin. Pin must be setup
 * + as output.
 *
 * Return: 0
 *
 * Params: 2
 * + Pin pin_number: Number of pin
 * + PinState new_state: New pin state
 */
static void
    setPinState (Pin pin_number, PinState new_state)
{
	/* Prepare pointer to hardware and mask */
    uint8_t mask = createPinMask (pin_number);
    volatile uint8_t *output = 
		createPinOutputPointer (pin_number);

	/* Prepare atomic operation */
    uint8_t sreg = SREG;
    cli ();

	/* Setup specified state */
    if (new_state == HIGH)
        *output |= mask;
    else
        *output &= ~mask;

	/* End atomic operation */
    SREG = sreg;
}

/*
 * Description
 * + This return current direction of pin specified in parameter.
 *
 * Return: 1
 * + PinDirection: Current direction of pin
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static PinDirection
    getPinDirection (Pin pin_number)
{
    uint8_t mask = createPinMask (pin_number);
    volatile uint8_t *direction = 
		createPinDirectionPointer (pin_number);

    return (PinDirection) ((*direction & mask) != 0);
}

/*
 * Description
 * + This return current state of pin specified in parameter.
 *
 * Return: 1
 * + PinState: Current state of specified pin
 *
 * Params: 1
 * + Pin pin_number: Number of pin
 */
static PinState
    getPinState (Pin pin_number)
{
    uint8_t mask = createPinMask (pin_number);
    volatile uint8_t *input = 
		createPinInputPointer (pin_number);

    return (PinState) (*input & mask);
}
