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
 * This file stores all the functions needed to maintain system time, with the 
 * exception of the getTime function which is platform dependent.
 */

#include "types.h"

#ifndef KERNEL_TIME_H_INCLUDED
#define KERNEL_TIME_H_INCLUDED

/** \def MAX_SYSTEM_TIME
 * Max value of system timer.
 */
#define MAX_SYSTEM_TIME 65535

/** \typedef system_tick_t
 * System time type.
 */
typedef uint16_t system_tick_t;

/** \fn wait
 * Will suspend the process for the time specified in the parameter, returns
 * nothing as the suspension will always succeed.
 */
void wait(system_tick_t how_long_wait);

/** \fn check_timer_processes
 * A function that should only be called by the system loader is responsible
 * for waking up dormant processes for a certain amount of time if that time
 * has already expired.
 */
void check_timer_processes(void);

#endif
