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
 * This file stores the structures and functions needed for the operation of
 * SharedMemory. SharedMemory is a structure that allows you to share a
 * memory area. It has a pointer to simplify data transfer from common memory
 * space via UART, TWI or SPI. Unlike the cache, it doesn't require the use of
 * a pointer, it's optional.
 */

#include "../settings.h"
#include "../kernel/types.h"
#include "shared_memory.h"

/** \fn reset_shared_memory_area
 * This function set all shared memory area to 0x00 and set pointer to null.
 * @*shared Pointer to shared memory for work on it
 */
void reset_shared_memory_area(shared_memory_t *shared) {
	for (uint8_t pointer = 0; pointer < SHARED_MEMORY_SIZE; ++ pointer){
		shared->area[pointer] = 0x00;
    }
}

/** \fn read_shared_memory
 * This function read sequence values from shared memory using pointer as
 * address and increment it after read.
 * @*shared Pointer to shared memory for work on it
 */
char read_shared_memory(shared_memory_t *shared) {
	shared->pointer = shared->pointer % SHARED_MEMORY_SIZE;

	return shared->area[shared->pointer++];
}

/** \fn write_shared_memory
 * This function write sequence values from shared memory using pointer as
 * address and increment it after read.
 * @*shared Pointer to shared memory for work on it
 * @data New data to write
 */
void write_shared_memory(shared_memory_t *shared, char data) {
	shared->pointer = shared->pointer % SHARED_MEMORY_SIZE;

	shared->area[shared->pointer++] = data;
}
