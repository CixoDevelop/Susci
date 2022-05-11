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
 * Params: 2
 * + SystemTick open_time: Time of opening the time slot
 * + SystemTick close_time: Time of closing the time slot
 */
static inline void
  periodicWakeUp(SystemTick open_time, SystemTick close_time)
{
    /* On all processes in the system */
    for(
        Process *to_wake_up = process_heap + MAX_PID;
        to_wake_up >= process_heap;
        to_wake_up --
       )
        if(
            /* If process is suspend and If the process is in suspend state */
            to_wake_up->state == TIMER &&

            /* And the time it waits for is in the time slot */
            to_wake_up->factor >= open_time &&
            to_wake_up->factor <= close_time
          )

            /* Then wake up process */
            to_wake_up->state = READY;
}