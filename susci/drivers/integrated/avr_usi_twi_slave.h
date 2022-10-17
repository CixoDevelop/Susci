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
 * Inspired by the CalcProgrammer1 project:
 * + https://instructables.com/ATTiny-USI-I2C-The-detailed-in-depth-and-infor
 *
 *
 * This file stores the TwiSlave driver running via the USI device available
 * instead of the hardware TWI in the smaller AtTiny microcontrollers. During
 * development, I used the CalcProgrammer1 project and the AVR312 document.
 * The code is heavily based on the CalcProgrammer1 project, but I decided to
 * redesign it a bit to better fit Susci.
 */

#include "../../communication/twi_slave.h"

#ifndef DRIVERS_INTEGRATED_TINY_TWI_SLAVE_H_INCLUDED
#define DRIVERS_INTEGRATED_TINY_TWI_SLAVE_H_INCLUDED

#ifdef USE_AVR_USI_TWI_SLAVE

extern twi_interface_t twi_slave;

/** \fn usi_twi_enable
 * Prepares the microcontroller and USI devices to work in the TWI bus.
 */
void usi_twi_enable(void);

#endif

#endif
