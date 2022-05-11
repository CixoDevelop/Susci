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
 * This file stores declarations of the base types used on the system, which
 * makes it independent of the base libraries of the different platforms.
 */
 

#pragma once


/* 8 bit numbers */
#ifndef uint8_t
	typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
#endif

/* 16 bit numbers */
#ifndef uint16_t
	typedef unsigned int uint16_t __attribute__((__mode__(__HI__)));
#endif

/* Logical */
#ifndef bool
	typedef enum{
		true = 1,
		false = 0
	} bool;
#endif

/* Pointers */
#ifndef nullptr
	#define nullptr 0x00
#endif

/* System */
typedef uint8_t PID;
typedef uint8_t Signal;