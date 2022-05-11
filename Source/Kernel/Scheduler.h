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
 * This file stores the system scheduler, process heap, and other items needed
 * for the running of the system kernel.
 */


#pragma once


/*
 * Defines the maximum PID number available to the operating system.
 */
#define MAX_PID PROCESS_HEAP_SIZE - 1

/*
 * Heap of operating system processes with a size defined statically by the 
 * user or in default settings.
 */
Process process_heap[PROCESS_HEAP_SIZE];

/*
 * Indicates the currently executing process, it is used when the process calls
 * an action on itself during execution.
 */
Process *current_process;

/*
 * Stores the currently occurring signal id. This value is modified by 
 * processes or hardware interrupts, it enables the creation of interrupts
 * in the system.
 */
Signal current_signal_id;

/*
 * Description
 * + This function is responsible for creating new processes in the system.
 * + The function is protected against accidental overwriting of an already 
 * + existing process.
 *  
 * Return: 2
 * + GOOD: The process has been created correctly
 * + PANIC: Something went wrong
 *
 * Params: 3
 * + PID priority: The priority the task will take
 * + ExecState (*worker)(void*): Worker of the process
 * + void *parameter: Parameter for worker
 */
static ExecState 
  createProcess(PID priority, ExecState (*worker)(void*), void *parameter)
{
    /* Priority out of range */
    if(priority > MAX_PID)
        return PANIC;

    /* Occupied priority */
    if(process_heap[priority].state != EMPTY)
        return PANIC;

    /* Create process and return GOOD */
    process_heap[priority].worker = worker;
    process_heap[priority].parameter = parameter;
    process_heap[priority].state = READY;

    return GOOD;
}

/*
 * Description
 * + It ends the currently executing process.
 *  
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static void
  killCurrentProcess(void)
{
    /* Mark current process to EMPTY */
    current_process->state = EMPTY;
}

/*
 * Description
 * + Ends the process with the PID specified in the parameter.
 *  
 * Return: 2
 * + GOOD: All went well
 * + PANIC: Process not exist
 *
 * Params: 1
 * + PID to_kill: PID of process to end
 */
static ExecState
  killProcess(PID to_kill)
{
    /* If process not exist, return PANIC */
    if(process_heap[to_kill].state == EMPTY)
        return PANIC;
    
    /* Mark process to EMPTY */
    process_heap[to_kill].state = EMPTY;
    
    /* Return GOOD */
    return GOOD;
}

/*
 * Description
 * + The function prepares all system values ​​for work, initializing them with default
 * + values. This has to be done only after the platform is initialized.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void 
  schedulerInit(void)
{
    /* Set all process as EMPTY */
    for(uint8_t actual = MAX_PID - 1; actual > 0; actual --)
        process_heap[actual].state = EMPTY;

    /* Clean system signal */
    current_signal_id = 0x00;
}

/*
 * Description
 * + This function is the system scheduler, responsible for calling the
 * + appropriate process. If everything went well, it will return GOOD, but if
 * + it was not successful, it will return PANIC. The loader will then call the
 * + the susciPanic function.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline ExecState 
  schedulerLoop(void)
{   
    /* Set the current process to the one with the highest PID */
    current_process = process_heap + PROCESS_HEAP_SIZE;

    /* If there was any signal */
    if(current_signal_id){

        /* Search the entire heap of processes */
        while(--current_process >= process_heap)

            /* In search of those who are waiting for this signal */
            if(
                current_process->state == SIGNAL &&
                current_process->factor == (Signal) current_signal_id
              )

                /* And then do them */
                if(current_process->worker(current_process->parameter) != GOOD)

                    /* If something went wrong, please return PANIC */
                    return PANIC;

        /* Finally, reset the signal */
        current_signal_id = 0x00;

        /* And return from function */
        return GOOD;
    }

    /* If there was not any signal */
    while(--current_process >= process_heap)

        /* Find first READY process */
        if(current_process->state == READY)

            /* And run it */
            return current_process->worker(current_process->parameter);
}