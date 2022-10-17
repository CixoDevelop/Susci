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
#include "../../platforms/avr.h"
#include "../../kernel/types.h"
#include "../../kernel/process.h"
#include "../../kernel/scheduler.h"
#include "../../synchronization/buffer.h"
#include "hardware_uart.h"

#ifdef USE_AVR_HARDWARE_UART

#include <avr/io.h>
#include <avr/interrupt.h>

buffer_t hardware_uart_sender;
buffer_t hardware_uart_receiver;

/** \fn hardware_uart_sender_service
 * This is service for hardware uart. If any data is in buffer, it send one
 * char from it to uart device. It use hardware_uart_sender aka print_buffer
 * that is global var, you must set nullptr as param for this process.
 */
exec_state_t hardware_uart_sender_service(void *param) {
	if (!is_buffer_readable(&hardware_uart_sender)) return IDLE_STATE;

	while (!(UCSRA & (1 << UDRE)));

	UDR = read_buffer(&hardware_uart_sender);

	return GOOD_STATE;
}

/** \fn ISR
 * This is responsible for inserting new received data to buffer.
 */
ISR(USART_RXC_vect) {
    write_buffer(&hardware_uart_receiver, UDR);
}

/** \fn enable_hardware_uart
 * This function setup uart device to work in system. This create new process
 * in system for uart_sender and turn on interrupts.
 * @speed uart buadrate
 */
void enable_hardware_uart(long speed) {
    speed = ((F_CPU / (speed * 16UL)) - 1);

    UBRRH = (uint8_t) (speed >> 8);
    UBRRL = (uint8_t) (speed);

    UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

    hardware_uart_receiver = create_buffer();
    hardware_uart_sender = create_buffer();

    create_process(get_first_empty(), hardware_uart_sender_service, nullptr);

    sei();
}

#endif
