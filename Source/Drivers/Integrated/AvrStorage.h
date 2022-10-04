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

#pragma once

/* Define address size. This id dependent on eeprom size, in
 * small devices 1 byte, in bigger devices 2 bytes */
#ifndef BYTE_EEPROM_ADDRESS
    typedef uint16_t Address;
#else
    typedef uint8_t Address;
#endif

/*
 * Description
 * + This write given byte to memory on specified address.
 *
 * Return: 0
 *
 * Params: 2
 * + Address address: Address to write data
 * + char data: Data to write
 */
static void
    storageWrite (Address address, char data)
{
	/* Wait for eeprom ready */
    while (EECR & (1 << EEPE)) ;

	/* Write data */
    EECR = (0 << EEPM1) | (0 << EEPM0);

    EEAR = address;
    EEDR = data;

    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
}

/*
 * Description
 * + This read data from eeprom from address specified in 
 * + parameter.
 *
 * Return: 1
 * + char: Data from memory
 *
 * Params: 1
 * + Address address: Address to read data from 
 */
static char
    storageRead (Address address)
{
	/* Wait for eeprom ready */
    while (EECR & (1 << EEPE)) ;

	/* Read dayat */
    EEAR = address;
    EECR |= (1 << EERE);

    return EEDR;
}
