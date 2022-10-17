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
 * This file stores driver responsible for hardware uart managment on avr MCU.
 */

#include "../../settings.h"
#include "../../kernel/types.h"
#include "../../kernel/process.h"
#include "../../synchronization/buffer.h"
#include "../../platforms/avr.h"

#ifndef DRIVERS_INTEGRATED_HARDWARE_UART_H_INCLUDED
#define DRIVERS_INTEGRATED_HARDWARE_UART_H_INCLUDED

#ifdef USE_AVR_HARDWARE_UART

extern buffer_t hardware_uart_sender;
extern buffer_t hardware_uart_receiver;

#define print_buffer (&hardware_uart_sender)
#define input_buffer (&hardware_uart_receiver)

/** \fn hardware_uart_sender_service
 * This is service for hardware uart. If any data is in buffer, it send one
 * char from it to uart device. It use hardware_uart_sender aka print_buffer
 * that is global var, you must set nullptr as param for this process.
 */
exec_state_t hardware_uart_sender_service(void *param);

/** \fn enable_hardware_uart
 * This function setup uart device to work in system. This create new process
 * in system for uart_sender and turn on interrupts.
 * @speed uart buadrate
 */
void enable_hardware_uart(long speed);

#endif

#endif
