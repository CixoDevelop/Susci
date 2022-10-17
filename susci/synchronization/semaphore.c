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
 * This file stores declarations and definitions of data structures and 
 * functions responsibles for standard Semaphore in system.
 */

#include "../kernel/types.h"
#include "semaphore.h"

/** \fn down_semaphore
 * This function cound down semaphore given in parameter. If can and 
 * semaphore counted down, return true, if not return false. Semaphores
 * counting to down, default state is max state.
 * @*semaphore Semaphore object
 */
bool down_semaphore(semaphore_t *semaphore) {
    if (semaphore->state == 0) return false;

    semaphore->state --;

    return true;
}

/** \fn up_semaphore
 * This function cound up semaphore given in parameter. If can and semaphore 
 * counted up, return true, if not return false. Semaphorescounting to down, 
 * default state is max state.
 * @*semaphore Semaphore object
 */
bool up_semaphore(semaphore_t *semaphore) {
    if (semaphore->state >= semaphore->max_state) return false;
    
    semaphore->state ++;

    return true;
}
