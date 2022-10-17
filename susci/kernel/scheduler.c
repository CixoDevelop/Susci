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

#include "../settings.h"
#include "types.h"
#include "process.h"
#include "scheduler.h"

/** \def MAX_PRIORITY_pid_t
 * Define process who have highest priority
 */
#define MAX_PRIORITY_PROCESS process_heap + MAX_PID

/** \def MIN_PRIORITY_PROCESS
 * Define process who have lowest priority
 */
#define MIN_PRIORITY_PROCESS process_heap

/** \var process_heap[]
 * Heap of operating system processes with a size defined statically by the 
 * user or in default settings.
 */
process_t process_heap[PROCESS_HEAP_SIZE];

/** \var *current_process
 * Indicates the currently executing process, it is used when the process calls
 * an action on itself during execution.
 */
process_t *current_process;

/** \var current_signal
 * Stores the currently occurring signal id. This value is modified by 
 * processes or hardware interrupts, it enables the creation of interrupts
 * in the system.
 */
signal_t current_signal;

/** \fn getFirstEmpty
 * This function searching first empty pid_t, and return it. If process heap
 * is full, returned magic number (FULL_PROCESS_HEAP). You can use it if 
 * You do not want to define pid_t yourself.
 */
pid_t get_first_empty(void) {
    pid_t empty_process_pid = PROCESS_HEAP_SIZE;
	
    while (empty_process_pid--) { 
        if (process_heap[empty_process_pid].state == EMPTY_STATE) {
		    return empty_process_pid;
        }
    }

    return FULL_PROCESS_HEAP;
}

/** \fn createprocess_t
 * This function is responsible for creating new processes in the system.
 * The function is protected against accidental overwriting of an already 
 * existing process.
 *  
 * @priority The priority the task will take
 * @(*worker)(void*) Worker of the process
 * @*parameter Parameter for worker
 */
exec_state_t create_process(
    pid_t process_pid,
    exec_state_t (*worker)(void*), 
    void *parameter
) {
    if (process_pid > MAX_PID) return PANIC_STATE;

    if (process_heap[process_pid].state != EMPTY_STATE) return PANIC_STATE;

    process_heap[process_pid].worker = worker;
    process_heap[process_pid].parameter = parameter;
    process_heap[process_pid].state = READY_STATE;

    return GOOD_STATE;
}

/** \fn killprocess
 * Ends the process with the pid_t specified in the parameter.
 *  
 * @to_kill pid of process to end
 */
exec_state_t kill_process(pid_t to_kill) {
    if (process_heap[to_kill].state == EMPTY_STATE) return PANIC_STATE;
    
    process_heap[to_kill].state = EMPTY_STATE;

    return GOOD_STATE;
}

/** \fn signal_scheduler
 * This function is the signal system scheduler, if system signal flag is 
 * set, then searching processes with SIGNAL_STATE with same signal, then 
 * run it, and return it state.
 */
static inline exec_state_t signal_scheduler(void) {
    if (current_signal == 0x00) return IDLE_STATE;

    /* 
     * This make local copy of signal, bacause when signal ia processing, any 
     * interrupt can change global signal flag
     */
    signal_t signal = current_signal;
    current_signal = 0x00;

    /*
     * This check all processes, all of it who has SIGNAL state had been
     * checked and these who had been marked for same signal will be executed
     */
	current_process = MAX_PRIORITY_PROCESS + 1;

	while (current_process-- > process_heap) {
		if (current_process->state != SIGNAL_STATE) continue;

		if (current_process->scheduler_context != signal) continue;
		
		exec_state_t return_state 
		= current_process->worker(current_process->parameter);

		if (return_state == IDLE_STATE) continue;
		
		return return_state;
	}

	return GOOD_STATE;
}

/** \fn standard_scheduler
 * This function is the system standard scheduler, searching any process in 
 * READY_STATE_STATE, if exist, run it and return result, if any process does 
 * not have READY_STATE_STATE, return GOOD_STATE_STATE.
 */
static inline exec_state_t standard_scheduler(void) {
    current_process = MAX_PRIORITY_PROCESS + 1;

	while (current_process-- > MIN_PRIORITY_PROCESS) {
		if (current_process->state != READY_STATE) continue;

		exec_state_t process_state  
		= current_process->worker(current_process->parameter);

		if (process_state == IDLE_STATE) continue;

		return process_state;
	}

	return GOOD_STATE;
}

/** \fn scheduler_loop 
 * This function is the system scheduler, responsible for calling the
 * appropriate process. If everything went well, it will return GOOD_STATE_STATE, 
 * but if it was not successful, it will return PANIC_STATE. The loader will
 * then call the susci_panic(void) function.
 */
exec_state_t scheduler_loop(void) {   
    exec_state_t signal = signal_scheduler();

	if (signal != IDLE_STATE) return signal;

    return standard_scheduler();
}
