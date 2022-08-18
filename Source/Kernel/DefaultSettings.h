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
 * This file sets the settings for the system, if they have not been 
 * overwritten previously in the project.
 */


#pragma once


/* 
 * This value tells about the size of the process heap, this heap limits the
 * number of processes on the system.
 *
 * Default: 4
 */
#ifndef PROCESS_HEAP_SIZE
    #define PROCESS_HEAP_SIZE 4
#endif