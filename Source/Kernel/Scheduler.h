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
 * Define full process heap expection 
 */
#define FULL_PROCESS_HEAP PROCESS_HEAP_SIZE

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
 * + This function searching first empty PID, and return it. If process heap
 * + is full, returned magic number (FULL_PROCESS_HEAP)
 *  
 * Return: 2
 * + FULL_PROCESS_HEAP: Process heap is full, can't found empty
 * + PID: Empty PID for new process
 *
 * Params: 0
 * + void
 */
static PID
	getFirstEmpty (void)
{
	/* Set PID for top of process list */
	PID empty = PROCESS_HEAP_SIZE;

	/* File not on bottom */
	while (empty --) 

		/* If PID is empty, return it */
		if (process_heap[empty].state == EMPTY)
			return empty;

	/* If heap is full, return exception */
	return FULL_PROCESS_HEAP;
}

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
	createProcess (PID priority, ExecState (*worker)(void*), void *parameter)
{
    /* Priority out of range */
    if (priority > MAX_PID)
        return PANIC;

    /* Occupied priority */
    if (process_heap[priority].state != EMPTY)
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
	killCurrentProcess (void)
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
	killProcess (PID to_kill)
{
    /* If process not exist, return PANIC */
    if (process_heap[to_kill].state == EMPTY)
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
	schedulerInit (void)
{
    /* Set all process as EMPTY */
    for (uint8_t actual = MAX_PID - 1; actual > 0; actual --)
        process_heap[actual].state = EMPTY;

    /* Clean system signal */
    current_signal_id = 0x00;
}

/*
 * Description
 * + This function is the signal system scheduler, if system signal flag is 
 * + set, then searching processes with SIGNAL state with same signal id, 
 * + then run it, and return it state.
 *
 * Return: 2 
 * + GOOD: Everything went well
 * + IDLE: Not did anything
 * + PANIC: Any process return PANIC 
 *
 * Params: 0
 * + void
 */
static inline ExecState
	signalScheduler (void)
{
	/* Check signal, if off, return */
	if (current_signal_id == 0x00)
		return IDLE;

	/* Create local signal copy, and remove original */
	Signal signal = current_signal_id;
	current_signal_id = 0x00;

	/* Set current process for loop */
	current_process = process_heap + PROCESS_HEAP_SIZE;

	/* Run on all processes */
	while (current_process -- > process_heap) {
		
		/* If process is not in signal state, skip it */
		if (current_process->state != SIGNAL)
			continue;

		/* If process signal is not same, skip it */
		if (current_process->factor != signal)
			continue;
		
		/* Run process and save result */
		ExecState return_state 
			= current_process->worker (current_process->parameter);

		/* If process not did anything, check next */
		if (return_state == IDLE)
			continue;
		
		/* Return process state */
		return return_state;
	}

	/* If all processes not did anythong, return GOOD */
	return GOOD;
}

/*
 * Description
 * + This function is the system standard scheduler, searching any process in 
 * + READY state, if exist, run it and returns result, if any process does not
 * + have READY state, return GOOD.
 *
 * Return: 2 
 * + GOOD: Everything went well
 * + PANIC: Any process return PANIC 
 *
 * Params: 0
 * + void
 */
static inline ExecState
	standardScheduler (void)
{
	/* Set process for loop */
	current_process = process_heap + PROCESS_HEAP_SIZE;

	/* Run on all processes */
	while (current_process -- > process_heap) {

		/* If process is not ready, go to next */
		if (current_process->state != READY)
			continue;

		/* If ready, run them and save state */
		ExecState process_state = 
			current_process->worker (current_process->parameter);

		/* If process not did anything, check next */
		if (process_state == IDLE)
			continue;

		/* Return state of process */
		return process_state;
	}

	/* If any process not be ready, return good state */
	return GOOD;
}

/*
 * Description
 * + This function is the system scheduler, responsible for calling the
 * + appropriate process. If everything went well, it will return GOOD, but if
 * + it was not successful, it will return PANIC. The loader will then call the
 * + the susciPanic function.
 *
 * Return: 2 
 * + GOOD: Everything went well
 * + PANIC: Any process return PANIC 
 *
 * Params: 0
 * + void
 */
static inline ExecState 
  schedulerLoop (void)
{   
	/* Check signals first */
    ExecState signal = signalScheduler ();

	/* If signals not did anything */
	if (signal != IDLE)
		return signal;

	/* Run something from standard heap */
	return standardScheduler ();
}