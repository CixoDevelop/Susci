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

#ifndef COMMUNICATION_SEMAPHORE_H_INCLUDED
#define COMMUNICATION_SEMAPHORE_H_INCLUDED

/** \struct semaphore_t
 * Type for Semaphore.
 */
typedef struct {

    /* Current semaphore state */
    uint8_t state;

    /* Max semaphore state */
    uint8_t max_state;

} semaphore_t;

/** \fn create_semaphore
 * This function creating semaphore with max state, given in parameter.
 * @max_state Max semaphore state
 */
static inline semaphore_t create_semaphore(uint8_t max_state) {
    return (semaphore_t) {max_state, max_state};
}

/** \fn down_semaphore
 * This function cound down semaphore given in parameter. If can and 
 * semaphore counted down, return true, if not return false. Semaphores
 * counting to down, default state is max state.
 * @*semaphore Semaphore object
 */
static bool down_semaphore(semaphore_t *semaphore) {
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
static bool up_semaphore(semaphore_t *semaphore) {
    if (semaphore->state >= semaphore->max_state) return false;
    
    semaphore->state ++;

    return true;
}

/** \fn get_semaphore_state
 * This function return current semaphore state.
 * @*semaphore Semaphore object
 */
static inline uint8_t get_semaphore_state(semaphore_t *semaphore) {
    return semaphore->state;
}

/** \fn reset_semaphore
 * This function reset semaphore.
 * @*semaphore Semaphore object
 */
static inline void reset_semaphore(semaphore_t *semaphore) {
    semaphore->state = semaphore->max_state;
}

#endif
