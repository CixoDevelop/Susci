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

#pragma once

/* Signals to trigger from implementation after operations */

/* After slave device send data to master */
#define TWI_SLAVE_SEND_SIGNAL 0x52

/* After slave device receive data from master */
#define TWI_SLAVE_RECEIVED_SIGNAL 0x53

/* This type store frame from TWI interface */
typedef uint8_t TwiFrame;

/* This type store device address */
typedef uint8_t TwiAddress;

/* This enum store access mode */
typedef enum {

    /* If master want to send data to slave */
    WRITE = 0,

    /* If master want to receive data from slave */
    READ = 1

} TwiTransmissionMode;

/* Current TWI bus state, implementation does not have to use everyone */
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

} TwiState;

/* This structure store data required for TWI slave interface */
typedef struct {

    /* This is current bus state */
    volatile TwiState state;

    /* This is device address */
    TwiAddress address;

    /* This is memory shared by slave device */
    SharedMemory shared;

} TwiInterface;

/*
 * Description
 * + This function create new TWI slave interface with new shared memory and
 * + device address from given parameter.
 *
 * Return: 1
 * + TwiInterface: New TWI interface
 *
 * Params: 1
 * + TwiAddress address: Address of slave device in new bus
 */
static inline TwiInterface
    createTwiInterface (TwiAddress address)
{
    return (TwiInterface) {
    	BUS_OFF,
    	address,
    	createSharedMemory ()
    };
}

/*
 * Description
 * + This function return transmission mode from first frame received from
 * + master device.
 *
 * Return: 1
 * + TwiTransmissionMode: Mode read from given frame
 *
 * Params: 1
 * + TwiFrame frame: Frame to read
 */
static inline TwiTransmissionMode
    getTwiTransmissionMode (TwiFrame frame)
{
    return frame & 0b00000001;
}

/*
 * Description
 * + This function get polled device address from first frame send by master.
 *
 * Return: 1
 * + TwiAddress: Polled device address
 *
 * Params: 1
 * + TwiFrame frame: Frame to read
 */
static inline TwiAddress
    getTwiControlAddress (TwiFrame frame)
{
    return (TwiAddress) (frame >> 1);
}

