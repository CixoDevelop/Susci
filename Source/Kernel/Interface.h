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
 * This file stores all the interfaces needed by processes to communicate with
 * the system and with each other.
 */


#pragma once


/*
 * Description
 * + It causes the transition of the currently executed process to the state
 * + of waiting for a signal from a parameter.
 *  
 * Return: 0
 * + void
 *
 * Params: 1
 * + Signal id: The signal that the process will be waiting for
 */
static void 
  waitForSignal(Signal id)
{
    /* Suspend process */
    current_process->state = SIGNAL;

    /* Set expected signal */
    current_process->factor = (Signal) id;
}

/*
 * Description
 * + It sets a process with a given PID waiting for a given signal.
 *
 * Return: 2
 * + GOOD: Everything went well
 * + PANIC: A process with this PID does not exist
 *
 * Params: 1
 * + PID to_wait: PID of process to set
 * + Signal id: The signal that the process will be waiting for
 */
static ExecState
  toWaitForSignal(PID to_wait, Signal id)
{
    /* If process does not exist, return PANIC*/
    if(process_heap[to_wait].state == EMPTY)
        return PANIC;

    /* Suspend it */
    process_heap[to_wait].state = SIGNAL;

    /* Set expected signal */
    process_heap[to_wait].factor = (Signal) id;

    /* Return GOOD */
    return GOOD;
}

/*
 * Description
 * + Creates a signal on the system.
 *
 * Return: 0
 * + void
 *
 * Params: 1
 * + Signal id: Signal to be called
 */
static void 
  makeSignal(Signal id)
{
    /* Call signal */
    current_signal_id = id;
}

/*
 * Description
 * + It puts the currently running process to sleep.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static void 
  sleep(void)
{
    /* Suspend current process */
    current_process->state = WAITING;
}

/*
 * Description
 * + It puts the process to sleep with the PID specified in the parameter.
 *
 * Return: 2
 * + GOOD: Everything went well
 * + PANIC: A process with this PID does not exist
 *
 * Params: 1
 * + PID to_sleep: PID of process to set
 */
static ExecState 
  toSleep(PID to_sleep)
{
    /* If process not exist, return PANIC */
    if(process_heap[to_sleep].state == EMPTY)
        return PANIC;
    
    /* Suspend process */
    process_heap[to_sleep].state = WAITING;
    
    /* Return GOOD */
    return GOOD;
}

/*
 * Description
 * + Resumes the process with the set PID from sleep.
 *
 * Return: 2
 * + GOOD: Everything went well
 * + PANIC: A process with this PID does not sleep
 *
 * Params: 1
 * + PID to_wake_up: PID of process to set
 */
static ExecState
  wakeUp(PID to_wake_up)
{
    /* If process is not suspend, return PANIC */
    if(process_heap[to_wake_up].state != WAITING)
        return PANIC;

    /* Set process to READY */
    process_heap[to_wake_up].state = READY;

    /* Return GOOD */
    return GOOD;
}