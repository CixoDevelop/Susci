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
 * This file is responsible for including all the header files required by the
 * system with one include in project.
 */

#ifndef SUSCI_INCLUDED
#define SUSCI_INCLUDED

/* If platform has not been included, abort compilation */
#ifndef PLATFORM_INCLUDE_FLAG
#error You must include your platform port file, before You include kernel!
#include <CRITICAL_ERROR>
#endif

/* Define system version and revision */
#define SUSCI_VERSION 22.10
#define SUSCI_REVISION 12

/* Include all system header files */
#include "kernel/types.h"
#include "kernel/process.h"
#include "kernel/scheduler.h"
#include "kernel/interface.h"
#include "kernel/time.h"
#include "kernel/loader.h"

/* Include synchronization files */
#include "synchronization/buffer.h"
#include "synchronization/semaphore.h"
#include "synchronization/circular_buffer.h"
#include "synchronization/shared_memory.h"
#include "synchronization/latch.h"

/* Include devices drivers */
#include "drivers/register/shift_register.h"

/* Include interrupts */
#ifdef PINCHANGE_INTERRUPT_AVR
#include "drivers/integrated/avr_pinchange.h"
#endif

/* Include Communication bus files */

/* Files for support TWI bus */
#ifdef USE_TWI_SLAVE

#include "communication/twi_slave.h"

/* Platform file specifies implementation of TWI to use */
#ifdef USE_TWI_SLAVE_TINY_IMPLEMENTATION
#include "drivers/integrated/tiny_twi_slave.h"
#endif

#endif

#endif
