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

#pragma once

/* Alocate memory for interface and its shared memory */
TwiInterface twi_slave;

/*
 * Description
 * + This function set SDA pin to input state
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetInput (void)
{
	SDA_DDR &= ~SDA_MASK;
}

/*
 * Description
 * + This function set SDA pin to output state, but not set PORT from LOW
 * + to HIGH, therefore you CAN NOT send data other than zero
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetOutput (void)
{
	SDA_DDR |= SDA_MASK;
}

/*
 * Description
 * + This function sets the PORT from LOW to HIGH so you can send any data, not
 * + just zero. Since it takes longer than usiTwiSetOutput () and the ACK bit
 * + is zero, there is no need to invoke it when ACK is transmitted.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetDataOutput (void)
{
    SDA_PORT |= SDA_MASK;
}

/*
 * Description
 * + This function restores PORT to the LOW state so that the PULL-UP resistor
 * + does not interfere with the transmission.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetDataInput (void)
{
    SDA_PORT &= ~SDA_MASK;
}

/*
 * Description
 * + Responsible for configuring microcontroller ports to use twi slave.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void
	usiTwiSetPort (void)
{
	SDA_DDR &= ~SDA_MASK;
    SDA_PORT &= ~SDA_MASK;

	SCL_DDR &= ~SCL_MASK;
    SCL_PORT &= ~SCL_MASK;
}

/*
 * Description
 * + This function returns true if there is a current start condition. This is
 * + useful when checking whether there is a start condition or a stop
 * + condition.
 *
 * Return: 2
 * + True: Start condition continues
 * + False: Start condition run out
 *
 * Params: 0
 * + void
 */
inline static bool
    usiTwiWaitForStartStop (void)
{
    return (bool) (SCL_PIN & SCL_MASK) && !(SDA_PIN & SDA_MASK);
}

/*
 * Description
 * + Returns true if a stop condition is met.
 *
 * Return: 2
 * + True: Stop condition met
 * + False: Start condition met
 *
 * Params: 0
 * + void
 */
inline static bool
    usiTwiStopCome (void)
{
    return (bool) (SDA_PIN & SDA_MASK);
}

/*
 * Description
 * + This function configures the USI control register to the state it should
 * + be when a stop condition occurs.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetupControlStop (void)
{
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

/*
 * Description
 * + This function configures the USI control register to the state it should
 * + be when a start condition occurs.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
inline static void
    usiTwiSetupControlStart (void)
{
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

/*
 * Description
 * + This function configures the USI status register to the state it should
 * + be when a start condition occurs.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static inline void
    usiTwiSetupCounterStart (void)
{
    USI_STATUS =
        (1 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x00 << USICNT0);
}

/*
 * Description
 * + This function configures the status register and the USI built-in counter
 * + so that the interrupt is triggered when a byte (8 bits) is received or
 * + sent.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static inline void
    usiTwiSetupCounterByte (void)
{
    USI_STATUS =
        (0 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x00 << USICNT0);
}

/*
 * Description
 * + This function configures the status register and the USI built-in counter
 * + so that the interrupt is triggered when a bit is received or sent.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static inline void
    usiTwiSetupCounterBit (void)
{
    USI_STATUS =
        (0 << USISIF) |
        (1 << USIOIF) |
        (1 << USIPF) |
        (1 << USIDC) |
        (0x0E << USICNT0);
}

/*
 * Description
 * + Configures the USI to send the ack bit.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static inline void
    usiTwiSendConfirmation (void)
{
    /* ACK bit is 0 */
	USI_DATA = 0x00;

    /* Set USI to out one LOW bit */
    usiTwiSetOutput ();
    usiTwiSetupCounterBit ();
}

/*
 * Description
 * + Prepares the microcontroller and USI devices to work in the TWI bus.
 *
 * Return: 0
 *
 * Params: 0
 * + void
 */
static inline void
    usiTwiEnable (void)
{
    /* Setup SDA and SCL to input */
    usiTwiSetPort ();

    /* Setup USI device */
    usiTwiSetupControlStart ();
    usiTwiSetupCounterStart ();

    /* Enable interrupts */
    sei ();
}

/*
 * Description
 * + Sets the TWI pins to input and recognizes whether a start or stop
 * + condition has occurred, then sets up the USI to receive data.
 *
 * ISR
 * + USI_START_INTERRUPT:
 * +++ Dispatched when the USI device detects a start or stop condition.
 */
ISR (USI_START_INTERRUPT) {
    /* Set input just in case */
    usiTwiSetInput ();

    /* Wait for end of start condition */
    while (usiTwiWaitForStartStop ()) ;

    /* Check if there is a start or stop condition */
    if (usiTwiStopCome ())
        usiTwiSetupControlStop ();
    else
        usiTwiSetupControlStart ();

    /* Prepare to receive byte with the address of device and the access mode */
    usiTwiSetupCounterStart ();
    twi_slave.state = VERYFI_POLLED_ADDRESS;
}

/*
 * Description
 * + It processes the current state of the bus, then configures the USI to
 * + perform the next step, verify the address of the device being polled,
 * + send or receive data, or acknowledge.
 *
 * ISR
 * + USI_OVERFLOW_INTERRUPT:
 * +++ It is called every time the USI counter becomes full, which is when
 * +++ the set amount of data (8 bits or 1 bit) is received or sent.
 */
ISR (USI_OVERFLOW_INTERRUPT) {
    /* Save received data for processing */
    TwiFrame buffer = USI_DATA;

    /* The mode of operation depends on the state of the bus */
    switch (twi_slave.state) {

        /* Bus is turned off or other device was being polled */
        case BUS_OFF: ;
            /* Do nothing */
        break;

        /* Master device polled some slave device, and you have to check it */
        case VERYFI_POLLED_ADDRESS: ;

            /*
             * If polled address is not this device address, turn off
             * processing data, and come back
             */
            if (getTwiControlAddress (buffer) != twi_slave.address) {
                twi_slave.state = BUS_OFF;
                break;
            }

            /* If polled address is correct, send ACK for master */
            usiTwiSendConfirmation ();

            /*
             * If master want to write data to slave, prepare USI device to
             * to receive data, if master want to receive data, prepare to
             * send data.
             */
            if (getTwiTransmissionMode (buffer) == WRITE) {
                twi_slave.state = RECEIVE_DATA_FROM_MASTER;
                resetSharedMemoryPointer (&twi_slave.shared);
		    } else {
                twi_slave.state = SEND_DATA_TO_MASTER;
			}

        break;

        /* Setup USI to send confirmation after received data from master */
        case SEND_CONFIRMATION_TO_MASTER: ;

            /* Setup USI to send ACK */
            usiTwiSendConfirmation ();

            /* Set next step */
            twi_slave.state = RECEIVE_DATA_FROM_MASTER;

            /* Process received data */

            /*
             * If pointer in memory has been set, write received data to
             *  memory and trigger signal, else received data is pointer.
             */
            if (isSetSharedMemoryPointer (&twi_slave.shared)){
                writeSharedMemory (&twi_slave.shared, buffer);
                makeSignal (TWI_SLAVE_RECEIVED_SIGNAL);
	        }else{
	            setSharedMemoryPointer (&twi_slave.shared, buffer);
            }

        break;

        /* Setup USI to receive byte after send ACK */
        case RECEIVE_CONFIRMATION_FROM_MASTER: ;

            /* Setup as input for receiving */
			usiTwiSetInput ();
			usiTwiSetDataInput ();

            /* Clean data register */
			USI_DATA = 0x00;

			/* Setup counter for byte */
			usiTwiSetupCounterBit ();

            /* Set next step */
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

            /* Read new data from memory and prepare USI to send it */

            /* Set PORT as LOW and HIGH (no ACK only) output and */
			usiTwiSetOutput ();
			usiTwiSetDataOutput ();

            /* Read data from shared memory and write it to USI device */
			USI_DATA = readSharedMemory (&twi_slave.shared);

			/* Set counter to count byte */
			usiTwiSetupCounterByte ();

            /* Set next step */
			twi_slave.state = RECEIVE_CONFIRMATION_FROM_MASTER;

			/* Trigger signal */
			makeSignal (TWI_SLAVE_SEND_SIGNAL);

		break;

        /* Setup USI device to receive byte from master */
        case RECEIVE_DATA_FROM_MASTER: ;

            /* Setup PORT as input */
			usiTwiSetInput ();

			/* Set counter to count byte */
            usiTwiSetupCounterByte ();

            /* Set next step */
            twi_slave.state = SEND_CONFIRMATION_TO_MASTER;

        break;

        /* For possible errors */
        default: ;
            /* Do nothing */
        break;
    }
}
