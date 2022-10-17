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

#ifndef COMMUNICATION_SHARED_MEMORY_H_INCLUDED
#define COMMUNICATION_SHARED_MEMORY_H_INCLUDED

/** \def SHARED_MEMORY_NULLPTR
 * NULLPTR in shared memory.
 */
#define SHARED_MEMORY_NULLPTR SHARED_MEMORY_SIZE

/** \struct shared_memory_t
 * This structure allows you to store Shared Memory, it stores the pointer
 * and just the shared memory.
 */
typedef struct {

    /* Pointer used when accessing in sequence */
	volatile uint8_t pointer;

	/* Memory space that is shared */
	volatile char area[SHARED_MEMORY_SIZE];

} shared_memory_t;

/** \fn create_shared_memory
 * This function create and return new SharedMemory with pointer set to null.
 */
static inline shared_memory_t create_shared_memory(void) {
	return (shared_memory_t) {SHARED_MEMORY_NULLPTR, {0x00}};
}

/** \fn reset_shared_memory_area
 * This function set all shared memory area to 0x00 and set pointer to null.
 * @*shared Pointer to shared memory for work on it
 */
void reset_shared_memory_area(shared_memory_t *shared);


/** \fn reset_shared_memory_pointer
 * This function set shared memory pointer to null.
 * @*shared Pointer to shared memory for work on it
 */
static inline void reset_shared_memory_pointer(shared_memory_t *shared) {
	shared->pointer = SHARED_MEMORY_NULLPTR;
}

/** \fn is_set_shared_memory_pointer
 * This function check shared memory pointer and return true if it is set or
 * false when it is set to null.
 * @*shared Pointer to shared memory for work on it
 */
static inline bool is_set_shared_memory_pointer(shared_memory_t *shared) {
	return (bool) (shared->pointer != SHARED_MEMORY_NULLPTR);
}

/** \fn set_shared_memory_pointer
 * This function set shared memory pointer to given address in shared area.
 * @*shared Pointer to shared memory for work on it
 * @address Address to set
 */
static inline void set_shared_memory_pointer(
    shared_memory_t *shared, 
    uint8_t address
) {
	shared->pointer = address % SHARED_MEMORY_SIZE;
}

/** \fn read_shared_memory_area
 * This function return value from shared memory from given address.
 * @*shared Pointer to shared memory for work on it
 * @address Address in shared area to read from
 */
static inline char read_shared_memory_area(
    shared_memory_t *shared, 
    uint8_t address
) {
	return shared->area[address % SHARED_MEMORY_SIZE];
}

/** \fn write_shared_memory_area
 * This function set given value to given address in shared area
 * @*shared Pointer to shared memory for work on it
 * @address Address in shared area to write to
 * @data: New data to write
 */
static inline void write_shared_memory_area(
    shared_memory_t *shared, 
    uint8_t address, 
    char data
) {
	shared->area[address % SHARED_MEMORY_SIZE] = data;
}

/** \fn read_shared_memory
 * This function read sequence values from shared memory using pointer as
 * address and increment it after read.
 * @*shared Pointer to shared memory for work on it
 */
char read_shared_memory(shared_memory_t *shared);

/** \fn write_shared_memory
 * This function write sequence values from shared memory using pointer as
 * address and increment it after read.
 * @*shared Pointer to shared memory for work on it
 * @data New data to write
 */
void write_shared_memory(shared_memory_t *shared, char data);

#endif
