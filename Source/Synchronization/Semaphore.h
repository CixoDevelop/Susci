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


#pragma once


/* Type for Semaphore */
typedef struct {

    /* Current semaphore state */
    uint8_t state;

    /* Max semaphore state */
    uint8_t max_state;

} Semaphore;

/*
 * Description
 * + This function creating semaphore with max state, given in parameter.
 *  
 * Return: 1
 * + Semaphore: New empty semaphore
 *
 * Params: 1
 * + uint8_t max_state: Max semaphore state
 */
static inline Semaphore
    createSemaphore (uint8_t max_state)
{
    /* Semaphore is default in max state and counting down */
    return (Semaphore) {max_state, max_state};
}

/*
 * Description
 * + This function cound down semaphore given in parameter. If can and 
 * + semaphore counted down, return true, if not return false. Semaphores
 * + counting to down, default state is max state.
 *  
 * Return: 2
 * + True: Everything went well
 * + False: Semaphore is zero, can not count down
 *
 * Params: 1
 * + Semaphore *semaphore: Semaphore object
 */
static bool 
    downSemaphore (Semaphore *semaphore)
{
    /* If semaphore is zero, can not count down */
    if (semaphore->state == 0)

        /* Return false */
        return false;

    /* Count down semaphore */
    semaphore->state --;

    /* Return true */
    return true;
}

/*
 * Description
 * + This function cound up semaphore given in parameter. If can and semaphore 
 * + counted up, return true, if not return false. Semaphorescounting to down, 
 * + default state is max state.
 *  
 * Return: 2
 * + True: Everything went well
 * + False: Semaphore is in max state, can not count up
 *
 * Params: 1
 * + Semaphore *semaphore: Semaphore object
 */
static bool 
    upSemaphore (Semaphore *semaphore)
{
    /* If semaphore is in max state, can not count up */
    if (semaphore->state >= semaphore->max_state)

        /* Return false */
        return false;
    
    /* Count up */
    semaphore->state ++;

    /* Return true */
    return true;
}

/*
 * Description
 * + This function return current semaphore state.
 *  
 * Return: 1
 * + uint8_t: Current semaphote state
 *
 * Params: 1
 * + Semaphore *semaphore: Semaphore object
 */
static inline uint8_t
    getSemaphoreState (Semaphore *semaphore)
{
    /* Return semaphore state */
    return semaphore->state;
}

/*
 * Description
 * + This function reset semaphore.
 *  
 * Return: 0
 * + void
 *
 * Params: 1
 * + Semaphore *semaphore: Semaphore object
 */
static inline void
    resetSemaphore (Semaphore *semaphore)
{
    /* Reset semaphore */
    semaphore->state = semaphore->max_state;
}
