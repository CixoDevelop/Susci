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
 * This file stores declarations of data structures responsible for storing
 * processes in the system.
 */

#ifndef KERNEL_PROCESS_H_INCLUDED
#define KERNEL_PROCESS_H_INCLUDED

/** \enum process_state_t
 * This enum is responsible for storing the state of the process 
 */
typedef enum{

    /* No process */
    EMPTY_STATE,

    /* Ready to execution */
    READY_STATE,

    /* Waiting for time */
    TIMER_STATE,

    /* Waiting for interaction from other process */
    WAITING_STATE,

    /* Waiting for system signal */
    SIGNAL_STATE

} process_state_t;

/** \enum exec_state_t
 * This enum is responsible for transmission function exec state 
 */
typedef enum{

    /* All went well */
    GOOD_STATE,

    /* Nothing was done */
    IDLE_STATE,

    /* Something went bad */
    PANIC_STATE

} exec_state_t;

/** \struct process_t
 * This struct storing process data in system 
 */
typedef struct{

    /* Actual process state */
    process_state_t state;

    /* Process attribute for scheduler */
    uint16_t scheduler_context;

    /* Parameter for worker */
    void *parameter;

    /* Process worker */
    exec_state_t (*worker)(void*);

} process_t;

#endif
