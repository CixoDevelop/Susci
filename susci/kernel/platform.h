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
 * This file stores declarations of functions that must be overwritten by the
 * port file for a given platform. It also sets the PLATFORM_INCLUDE_FLAG flag
 * without which the kernel will stop compiling because it needs to define an
 * platform dependent types.
 */

#include "time.h"

#ifndef KERNEL_PLATFORM_H_INCLUDED
#define KERNEL_PLATFORM_H_INCLUDED


/** \fn platform_init
 * This function is responsible for preparing the platform for the operating
 * system to work, for example starting the system timer.
 */
void platform_init(void);

/** \fn get_time
 * This function takes the current state of the system timer and then returns
 * it. Note, it pauses interrupts while it is running!
 */
system_tick_t get_time(void);

/** \def PLATFORM_INCLUDE_FLAG
 * Sets a flag indicating that the platform file has been included.
 */

#define PLATFORM_INCLUDE_FLAG

#endif
