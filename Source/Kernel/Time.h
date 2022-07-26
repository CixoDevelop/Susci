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


#pragma once


/*
 * Description
 * + Will suspend the process for the time specified in the parameter, returns
 * + nothing as the suspension will always succeed.
 *  
 * Return: 0
 * + void
 *
 * Params: 1
 * + SystemTick how_long: Indicates how long the process is to be suspended
 */
static void 
  wait(SystemTick how_long)
{
    /* Suspend current process */
    current_process->state = TIMER;

    /* Get system time and how much is left to rewind */
    SystemTick actual_time = getTime();
    SystemTick rewind = MAX_SYSTEM_TIME - actual_time;
    
    /* Calculate the moment in time when the quest can be suspended */
    if(rewind < how_long)
        current_process->factor = how_long - rewind;
    else
        current_process->factor = actual_time + how_long;
}

/*
 * Description
 * + A function that should only be called by the system loader is responsible
 * + for waking up dormant processes for a certain amount of time if that time
 * + has already expired.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void
  periodicWakeUp(void)
{
	/* Variable for storing timestamp */
	static SystemTick latest = 0x0000;
	
	/* Create timestamp */
	SystemTick recent = latest;
	latest = getTime ();

	/* If recent time is max, then revers */
	if (recent == 0xFFFF && recent > latest)
		recent = 0x0000;

	/* If timer has run out, correct */
	if (recent > latest)
		latest = 0xFFFF;

	/* Set process pointer for loop */
    Process *to_wake_up = process_heap + PROCESS_HEAP_SIZE;

	/* Check all processes */
	while (to_wake_up -- > process_heap) {

		/* If process is not in TIMER state, skip */
		if (to_wake_up->state != TIMER)
			continue;

		/* If process timestamp is in current timestamp, mark READY */
		if (to_wake_up->factor >= recent && to_wake_up->factor <= latest)
			to_wake_up->state = READY;
	}
}