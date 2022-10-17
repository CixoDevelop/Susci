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
 * This file stores the general data structures and functions needed by each
 * TWI slave implementation for each platform. The elements contained therein
 * constitute the basis on which the TWI slave implementation is then placed.
 */

#include "../settings.h"
#include "../synchronization/shared_memory.h"
#include "../kernel/types.h"

#ifndef COMMUNICATION_TWI_SLAVE_H_INCLUDED 
#define COMMUNICATION_TWI_SLAVE_H_INCLUDED 

#ifdef USE_TWI_SLAVE

/** \def TWI_SLAVE_SEND_SIGNAL
 * This signal is handling when twi device send any data to master.
 */
#define TWI_SLAVE_SEND_SIGNAL 0x52

/** \def TWI_SLAVE_RECEIVED_SIGNAL
 * This signal is handling when twi device received any data.
 */
#define TWI_SLAVE_RECEIVED_SIGNAL 0x53

/** \typedef twi_frame_t
 * This type store frame from TWI interface.
 */
typedef uint8_t twi_frame_t;

/** \typedef twi_address_t
 * This type store device address.
 */
typedef uint8_t twi_address_t;

/** \enum twi_transmission_mode_t 
 * This enum store access mode 
 */
typedef enum {

    /* If master want to send data to slave */
    WRITE_MODE = 0,

    /* If master want to receive data from slave */
    READ_MODE = 1

} twi_transmission_mode_t;

/** \enum twi_state_t
 * Current TWI bus state, implementation does not have to use everyone 
 */
typedef enum {

    /* If TWI bas is off, or other device polled */
    BUS_OFF = 0,

    /* If TWI master polled device */
    VERYFI_POLLED_ADDRESS = 1,

    /* If slave device sending ACK to master */
    SEND_CONFIRMATION_TO_MASTER = 2,

    /* If slave device receiving ACK or NACK from master */
    RECEIVE_CONFIRMATION_FROM_MASTER = 3,

    /* If slave device sending data to master */
    SEND_DATA_TO_MASTER = 4,

    /* If slave device receiving data from master */
    RECEIVE_DATA_FROM_MASTER = 5

} twi_state_t;

/** \struct twi_interface_t
 * This structure store data required for TWI slave interface. 
 */
typedef struct {

    /* This is current bus state */
    volatile twi_state_t state;

    /* This is device address */
    twi_address_t address;

    /* This is memory shared by slave device */
    shared_memory_t shared;

} twi_interface_t;

/** \fn create_twi_interface
 * This function create new TWI slave interface with new shared memory and
 * device address from given parameter.
 * @address Address of slave device in new bus
 */
static inline twi_interface_t create_twi_interface(twi_address_t address) {
    return (twi_interface_t) {
    	BUS_OFF,
    	address,
    	create_shared_memory ()
    };
}

/** \fn get_twi_transmission_mode
 * This function return transmission mode from first frame received from
 * master device.
 * @frame Frame to read from
 */
static inline twi_transmission_mode_t get_twi_transmission_mode(
    twi_frame_t frame
) {
    return frame & 0x01;
}

/** \fn get_twi_control_address
 * This function get polled device address from first frame send by master.
 * @frame Frame to read from
 */
static inline twi_address_t get_twi_control_address (twi_frame_t frame) {
    return (twi_address_t) (frame >> 1);
}

#endif

#endif
