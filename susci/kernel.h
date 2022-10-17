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

/* Your project settings */
#include "settings.h"

/* Define system version and revision */
#define SUSCI_VERSION 22.10
#define SUSCI_REVISION 17

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

/* Include ports */
#include "platforms/avr.h"

/* Include drivers */
#include "communication/twi_slave.h"
#include "drivers/register/shift_register.h"
#include "drivers/integrated/pinchange.h"
#include "drivers/integrated/pins.h"
#include "drivers/integrated/hardware_uart.h"
#include "drivers/integrated/avr_usi_twi_slave.h"
#include "drivers/integrated/avr_pins.h"

/* If platform has not been included, abort compilation */
#ifndef PLATFORM_INCLUDE_FLAG
#error You must include your platform port file in settings.h
#endif

#endif
