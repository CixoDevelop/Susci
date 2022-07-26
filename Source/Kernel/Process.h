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
 

#pragma once


/* This enum is responsible for storing the state of the process */
typedef enum{

    /* No process */
    EMPTY,

    /* Ready to execution */
    READY,

    /* Waiting for time */
    TIMER,

    /* Waiting for interaction from other process */
    WAITING,

    /* Waiting for system signal */
    SIGNAL

} ProcessState;

/* This enum is responsible for transmission function exec state */
typedef enum{

    /* All went well */
    GOOD,

    /* Nothing was done */
    IDLE,

    /* Something went bad */
    PANIC

} ExecState;

/* This struct storing process data in system */
typedef struct{

    /* Actual process state */
    ProcessState state;

    /* Process attribute for scheduler */
    uint16_t factor;

    /* Parameter for worker */
    void *parameter;

    /* Process worker */
    ExecState (*worker)(void*);

} Process;