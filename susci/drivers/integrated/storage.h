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
 * This file stores driver that is responsible for storing data in eeprom.
 */

#include "../../settings.h"
#include "../../kernel/types.h"
#include "../../platforms/avr.h"

#ifndef DRIVERS_INTEGRATED_STORAGE_H_INCLUDED
#define DRIVERS_INTEGRATED_STORAGE_H_INCLUDED

#ifdef USE_AVR_STORAGE

/** \typedef address_t
 * Define address size. This id dependent on eeprom size, in
 * small devices 1 byte, in bigger devices 2 bytes 
 */

#ifndef BYTE_EEPROM_ADDRESS
typedef uint16_t address_t;
#else
typedef uint8_t address_t;
#endif

/** \fn storage_write
 * This write given byte to memory on specified address.
 * @address: Address to write data
 * @data: Data to write
 */
void storage_write(address_t address, char data);

/** \fn storage_read
 * This read data from eeprom from address specified in 
 * parameter.
 * @address Address to read data from 
 */
char storage_read(address_t address);

#endif

#endif
