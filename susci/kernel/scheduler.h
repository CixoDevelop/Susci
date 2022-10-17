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

#ifndef KERNEL_SCHEDULER_H_INCLUDED
#define KERNEL_SCHEDULER_H_INCLUDED

/** \var process_heap[]
 * Heap of operating system processes with a size defined statically by the 
 * user or in default settings.
 */
extern process_t process_heap[];

/** \var *current_process
 * Indicates the currently executing process, it is used when the process calls
 * an action on itself during execution.
 */
extern process_t *current_process;

/** \var current_signal
 * Stores the currently occurring signal id. This value is modified by 
 * processes or hardware interrupts, it enables the creation of interrupts
 * in the system.
 */
extern signal_t current_signal;

/** \def MAX_PID
 * Defines the maximum pid_t number available to the operating system.
 */
#define MAX_PID PROCESS_HEAP_SIZE - 1

/** \def FULL_PROCESS_HEAP
 * Define full process heap expection 
 */
#define FULL_PROCESS_HEAP PROCESS_HEAP_SIZE

/** \fn getFirstEmpty
 * This function searching first empty pid_t, and return it. If process heap
 * is full, returned magic number (FULL_PROCESS_HEAP). You can use it if 
 * You do not want to define pid_t yourself.
 */
pid_t get_first_empty(void);

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
);

/** \fn kill_current_process
 * It ends the currently executing process.
 */
static inline void kill_current_process(void) {
    current_process->state = EMPTY_STATE;
}

/** \fn killprocess
 * Ends the process with the pid_t specified in the parameter.
 *  
 * @to_kill pid of process to end
 */
exec_state_t kill_process(pid_t to_kill);

/** \fn scheduler_init
 * The function prepares all system values for work, initializing them with default
 * values. This has to be done only after the platform is initialized.
 */
static inline void scheduler_init(void) {
    pid_t current_pid = MAX_PID;

    while (current_pid--) process_heap[current_pid].state = EMPTY_STATE; 

    current_signal = 0x00;
}

/** \fn scheduler_loop 
 * This function is the system scheduler, responsible for calling the
 * appropriate process. If everything went well, it will return GOOD_STATE_STATE, 
 * but if it was not successful, it will return PANIC_STATE. The loader will
 * then call the susci_panic(void) function.
 */
exec_state_t scheduler_loop(void);

#endif
