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

#ifndef KERNEL_TYPES_H_INCLUDED
#define KERNEL_TYPES_H_INCLUDED

/** \typedef uint8_t
 * 8 bit numbers 
 */
#ifndef uint8_t
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
#endif

/** \typedef
 * 16 bit numbers 
 */
#ifndef uint16_t
typedef unsigned int uint16_t __attribute__((__mode__(__HI__)));
#endif

/** \enum bool
 * Logical 
 */
#ifndef bool
typedef enum {
	true = 1,
	false = 0
} bool;
#endif

/** \def nullptr
 * Pointer to null 
 */
#ifndef nullptr
#define nullptr 0x00
#endif

/** \typedef pid_t
 * System process id
 */
typedef uint8_t pid_t;

/** \typedef signal_t
 * System signal 
 */
typedef uint8_t signal_t;

#endif
