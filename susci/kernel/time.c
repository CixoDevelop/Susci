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

#include "../settings.h"
#include "time.h"
#include "scheduler.h"
#include "process.h"
#include "platform.h"

extern process_t process_heap[];
extern process_t *current_process;

/** \fn wait
 * Will suspend the process for the time specified in the parameter, returns
 * nothing as the suspension will always succeed.
 */
void wait(system_tick_t how_long_wait) {
    current_process->state = TIMER_STATE;

    system_tick_t actual_time = get_time();
    system_tick_t left_to_rewind = MAX_SYSTEM_TIME - actual_time;
    
    if (left_to_rewind < how_long_wait) {
        current_process->scheduler_context = how_long_wait - left_to_rewind;
    } else {
        current_process->scheduler_context = actual_time + how_long_wait;
    }
}

/** \fn check_timer_processes
 * A function that should only be called by the system loader is responsible
 * for waking up dormant processes for a certain amount of time if that time
 * has already expired.
 */
void check_timer_processes(void) {
	static system_tick_t latest_loop = 0x0;
	
	system_tick_t recent_loop = latest_loop;
	latest_loop = get_time();

	if (recent_loop == MAX_SYSTEM_TIME && recent_loop > latest_loop) {
        recent_loop = 0;
    }

	if (recent_loop > latest_loop) {
        latest_loop = MAX_SYSTEM_TIME;
    }

    process_t *to_wake_up = process_heap + PROCESS_HEAP_SIZE;

	while (to_wake_up-- > process_heap) {
		if (to_wake_up->state != TIMER_STATE) continue;

		if (
            to_wake_up->scheduler_context >= recent_loop 
            && to_wake_up->scheduler_context <= latest_loop
        ) to_wake_up->state = READY_STATE;
	}
}
