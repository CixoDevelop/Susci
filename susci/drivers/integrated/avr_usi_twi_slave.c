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
 * Inspired by the CalcProgrammer1 project:
 * + https://instructables.com/ATTiny-USI-I2C-The-detailed-in-depth-and-infor
 *
 *
 * This file stores the TwiSlave driver running via the USI device available
 * instead of the hardware TWI in the smaller AtTiny microcontrollers. During
 * development, I used the CalcProgrammer1 project and the AVR312 document.
 * The code is heavily based on the CalcProgrammer1 project, but I decided to
 * redesign it a bit to better fit Susci.
 */

#include "../../settings.h"
#include "../../platforms/avr.h"
#include "../../kernel/interface.h"
#include "avr_usi_twi_slave.h"

#ifdef USE_AVR_USI_TWI_SLAVE

#include <avr/io.h>
#include <avr/interrupt.h>

#define USI_ACK_DATA 0x00

/** \var twi_slave
 * Handler to hardware twi slave device.
 */
twi_interface_t twi_slave;

/** \fn usi_twi_set_input
 * This function set SDA pin to input state
 */
static inline void usi_twi_set_input(void) {
	SDA_DDR &= ~SDA_MASK;
}

/** \fn usi_twi_set_output
 * This function set SDA pin to output state, but not set PORT from LOW
 * to HIGH, therefore you CAN NOT send data other than zero
 */
static inline void usi_twi_set_output(void) {
	SDA_DDR |= SDA_MASK;
}

/** \fn usi_twi_set_data_output
 * This function sets the PORT from LOW to HIGH so you can send any data, not
 * just zero. Since it takes longer than usiTwiSetOutput () and the ACK bit
 * is zero, there is no need to invoke it when ACK is transmitted.
 */
static inline void usi_twi_set_data_output(void) {
    SDA_PORT |= SDA_MASK;
}

/** \fn usi_twi_set_data_input 
 * This function restores PORT to the LOW state so that the PULL-UP resistor
 * does not interfere with the transmission.
 */
static inline void usi_twi_set_data_input(void) {
    SDA_PORT &= ~SDA_MASK;
}

/** \fn usi_twi_set_port 
 * + Responsible for configuring microcontroller ports to use twi slave.
 */
static inline void usi_twi_set_port(void) {
	SDA_DDR &= ~SDA_MASK;
    SDA_PORT &= ~SDA_MASK;

	SCL_DDR &= ~SCL_MASK;
    SCL_PORT &= ~SCL_MASK;
}

/** \fn usi_twi_wait_for_start_stop
 * This function returns true if there is a current start condition. This is
 * useful when checking whether there is a start condition or a stop
 * condition.
 */
static inline bool usi_twi_wait_for_start_stop(void) {
    return (bool) (SCL_PIN & SCL_MASK) && !(SDA_PIN & SDA_MASK);
}

/** \fn usi_two_stop_come
 * Returns true if a stop condition is met.
 */
static inline bool usi_twi_stop_come(void) {
    return (bool) (SDA_PIN & SDA_MASK);
}

/** \fn usi_twi_setup_control_stop
 * This function configures the USI control register to the state it should
 * be when a stop condition occurs.
 */
static inline void usi_twi_setup_control_stop(void) {
    USI_CONTROL =
            (1 << USISIE) |
        	(0 << USIOIE) |
        	(1 << USIWM1) |
        	(1 << USIWM0) |
        	(1 << USICS1) |
        	(0 << USICS0) |
        	(0 << USICLK) |
        	(0 << USITC);
}

/** \fn usi_twi_setup_control_start
 * This function configures the USI control register to the state it should
 * be when a start condition occurs.
 */
static inline void usi_twi_setup_control_start(void) {
    USI_CONTROL =
        	(1 << USISIE) |
        	(1 << USIOIE) |
        	(1 << USIWM1) |
        	(0 << USIWM0) |
        	(1 << USICS1) |
        	(0 << USICS0) |
        	(0 << USICLK) |
        	(0 << USITC);
}

/** \fn usi_twi_setup_counter_start
 * This function configures the USI status register to the state it should
 * be when a start condition occurs.
 */
static inline void usi_twi_setup_counter_start(void) {
    USI_STATUS =
        (1 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x00 << USICNT0);
}

/** \fn usi_twi_setup_counter_byte
 * This function configures the status register and the USI built-in counter
 * so that the interrupt is triggered when a byte (8 bits) is received or
 * sent.
 */
static inline void usi_twi_setup_counter_byte(void) {
    USI_STATUS =
        (0 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x00 << USICNT0);
}

/** \fn usi_twi_setup_counter_byte
 * This function configures the status register and the USI built-in counter
 * so that the interrupt is triggered when a bit is received or sent.
 */
static inline void usi_twi_setup_counter_bit(void) {
    USI_STATUS =
        (0 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x0E << USICNT0);
}

/** \fn usi_twi_send_confirmation
 * Configures the USI to send the ack bit.
 */
static inline void usi_twi_send_confirmation(void) {
	USI_DATA = USI_ACK_DATA;
    
    usi_twi_set_output();
    usi_twi_setup_counter_bit();
}

/** \fn usi_twi_enable
 * Prepares the microcontroller and USI devices to work in the TWI bus.
 */
void usi_twi_enable(void) {
    usi_twi_set_port();

    usi_twi_setup_control_start();
    usi_twi_setup_counter_start();

    sei();
}

/** \fn ISR (USI_START_INTERRUPT)
 * Sets the TWI pins to input and recognizes whether a start or stop
 * condition has occurred, then sets up the USI to receive data.
 */
ISR (USI_START_INTERRUPT) {
    usi_twi_set_input();

    while (usi_twi_wait_for_start_stop()) ;

    if (usi_twi_stop_come()) usi_twi_setup_control_stop();
    else usi_twi_setup_control_start();

    usi_twi_setup_counter_start();
    twi_slave.state = VERYFI_POLLED_ADDRESS;
}

/** \fn ISR (USI_OVERFLOW_INTERRUPT)
 * It processes the current state of the bus, then configures the USI to
 * perform the next step, verify the address of the device being polled,
 * send or receive data, or acknowledge.
 */
ISR (USI_OVERFLOW_INTERRUPT) {
    twi_frame_t buffer = USI_DATA;

    switch (twi_slave.state) {

        case BUS_OFF: ;
        break;

        case VERYFI_POLLED_ADDRESS: ;

            /*
             * If polled address is not this device address, turn off
             * processing data, and come back
             */
            if (get_twi_control_address(buffer) != twi_slave.address) {
                twi_slave.state = BUS_OFF;
                break;
            }

            usi_twi_send_confirmation();

            /*
             * If master want to write data to slave, prepare USI device to
             * to receive data, if master want to receive data, prepare to
             * send data.
             */
            if (get_twi_transmission_mode(buffer) == WRITE_MODE) {
                twi_slave.state = RECEIVE_DATA_FROM_MASTER;
                reset_shared_memory_pointer(&twi_slave.shared);
		    } else {
                twi_slave.state = SEND_DATA_TO_MASTER;
			}

        break;

        case SEND_CONFIRMATION_TO_MASTER: ;

            usi_twi_send_confirmation();

            twi_slave.state = RECEIVE_DATA_FROM_MASTER;

            /*
             * If pointer in memory has been set, write received data to
             *  memory and trigger signal, else received data is pointer.
             */
            if (is_set_shared_memory_pointer(&twi_slave.shared)){
                write_shared_memory(&twi_slave.shared, buffer);
                make_signal(TWI_SLAVE_RECEIVED_SIGNAL);
	        }else{
	            set_shared_memory_pointer(&twi_slave.shared, buffer);
            }

        break;

        case RECEIVE_CONFIRMATION_FROM_MASTER: ;

			usi_twi_set_input();
			usi_twi_set_data_input();

			USI_DATA = 0x00;

			usi_twi_setup_counter_bit();

			twi_slave.state = SEND_DATA_TO_MASTER;

		break;

        case SEND_DATA_TO_MASTER: ;

            /*
             * Check received confirmation. If master send NACK this is end of
             * transmission, turn off bus and come back.
             */
			if (buffer != 0x00) {
				twi_slave.state = BUS_OFF;
				break;
			}

			usi_twi_set_output();
			usi_twi_set_data_output();

			USI_DATA = read_shared_memory(&twi_slave.shared);

			usi_twi_setup_counter_byte();

			twi_slave.state = RECEIVE_CONFIRMATION_FROM_MASTER;

			make_signal(TWI_SLAVE_SEND_SIGNAL);

		break;

        case RECEIVE_DATA_FROM_MASTER: ;

			usi_twi_set_input();

            usi_twi_setup_counter_byte();

            twi_slave.state = SEND_CONFIRMATION_TO_MASTER;

        break;

        default: ;
        break;
    }
}

#endif
