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
 * This file stores driver who is responsible for managment shift registers. 
 * This has driver that is standard Susci service for sending data to 
 * register hardware.
 */

#pragma once

/* This struct store config of shift register */
typedef struct {
	
	/* To sending data */
    Latch latch;
	
	/* Shift Register pins */
    Pin DA;
    Pin ST_CP;
    Pin SH_CP;
} ShiftRegister;

/*
 * Description
 * + This prepare shift register object in in memory.
 *
 * Return: 1
 * + ShiftRegister: New shift register object
 *
 * Params: 3
 * + Pin DA: DA shift register pin
 * + Pin ST_CP: ST_CP shift register pin
 * + Pin SH_CP: SH_CP shift register pin
 */
static ShiftRegister
    createShiftRegister (Pin DA, Pin ST_CP, Pin SH_CP)
{
	/* Set pins as outputs and low state */
    uint8_t DA_mask = createPinMask (DA);
    uint8_t ST_CP_mask = createPinMask (ST_CP);
    uint8_t SH_CP_mask = createPinMask (SH_CP);

    *createPinOutputPointer (DA) &= ~DA_mask;
    *createPinOutputPointer (ST_CP) &= ~ST_CP_mask;
    *createPinOutputPointer (SH_CP) &= ~SH_CP_mask;

    *createPinDirectionPointer (DA) |= DA_mask;
    *createPinDirectionPointer (ST_CP) |= ST_CP_mask;
    *createPinDirectionPointer (SH_CP) |= SH_CP_mask;

	/* New object */
    return (ShiftRegister) {createLatch (), DA, ST_CP, SH_CP};
}

/*
 * Description
 * + This is service to manage shift register hardware.
 *
 * Return: 1
 * + ExecState: Service state
 *
 * Params: 1
 * + void *shift_register_pointer: This is pointer to object
 */
static ExecState
    shiftRegisterDriver (void *shift_register_pointer)
{
	/* Cast shift register pointer */
    ShiftRegister *shift_register = shift_register_pointer;

	/* Check any data was received */
    if (getLatchFlag (&shift_register->latch) == UNSET)
        return IDLE;

	/* Prepare addresses and masks for operating */
    volatile uint8_t *DA_output = createPinOutputPointer (shift_register->DA);
    volatile uint8_t *ST_CP_output = createPinOutputPointer (shift_register->ST_CP);
    volatile uint8_t *SH_CP_output = createPinOutputPointer (shift_register->SH_CP);

    uint8_t DA_mask = createPinMask (shift_register->DA);
    uint8_t ST_CP_mask = createPinMask (shift_register->ST_CP);
    uint8_t SH_CP_mask = createPinMask (shift_register->SH_CP);

	/* Get data from latch */
    char data = popLatch (&shift_register->latch);

	/* Write it to register */
    for (uint8_t bit = 8; bit > 0; bit --){
        if (data & (1 << bit - 1))
            *DA_output |= DA_mask;
        else
            *DA_output &= ~DA_mask;

        *SH_CP_output |= SH_CP_mask;
        *SH_CP_output &= ~SH_CP_mask;
    }

	/* Commit it */
    *ST_CP_output |= ST_CP_mask;
    *ST_CP_output &= ~ST_CP_mask;

    return GOOD;
}
