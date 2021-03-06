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


#pragma once


/* If platform has not been included, abort compilation */
#ifndef PLATFORM_INCLUDE_FLAG
    #error You must include your platform port file, before You include kernel!
    #include <CRITICAL_ERROR>
#endif

/* Define system version and revision */
#define SUSCI_VERSION 22.7
#define SUSCI_REVISION 26

/* Include all system header files */
#include "Kernel/Types.h"
#include "Kernel/Process.h"
#include "Kernel/DefaultSettings.h"
#include "Kernel/Scheduler.h"
#include "Kernel/Interface.h"
#include "Kernel/Time.h"
#include "Kernel/Loader.h"

/* Include synchronization files */
#include "Synchronization/Buffer.h"
#include "Synchronization/Semaphore.h"
#include "Synchronization/CircularBuffer.h"