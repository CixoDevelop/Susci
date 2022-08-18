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

#pragma once

#ifndef SHARED_MEMORY_SIZE
	#define SHARED_MEMORY_SIZE 8
#endif

#define SHARED_MEMORY_NULLPTR SHARED_MEMORY_SIZE


/*
 * This structure allows you to store Shared Memory, it stores the pointer
 * and just the shared memory.
 */
typedef struct {

    /* Pointer used when accessing in sequence */
	volatile uint8_t pointer;

	/* Memory space that is shared */
	volatile char area[SHARED_MEMORY_SIZE];

} SharedMemory;

/*
 * Description
 * + This function create and return new SharedMemory with pointer set to null.
 *
 * Return: 1
 * + SharedMemory: New SharedMemory with pointer set to null
 *
 * Params: 0
 * + void
 */
static inline SharedMemory
	createSharedMemory (void)
{
	return (SharedMemory) {SHARED_MEMORY_NULLPTR};
}

/*
 * Description
 * + This function set all shared memory area to 0x00 and set pointer to null.
 *
 * Return: 0
 * + void
 *
 * Params: 1
 * + SharedMemory *shared: Pointer to shared memory for work on it
 */
static void
	resetSharedMemoryArea (SharedMemory *shared)
{
	for (uint8_t pointer = 0; pointer < SHARED_MEMORY_SIZE; pointer ++)
		shared->area[pointer] = 0x00;
}

/*
 * Description
 * + This function set shared memory pointer to null.
 *
 * Return: 0
 * + void
 *
 * Params: 1
 * + SharedMemory *shared: Pointer to shared memory for work on it
 */
static void
	resetSharedMemoryPointer (SharedMemory *shared)
{
	shared->pointer = SHARED_MEMORY_NULLPTR;
}

/*
 * Description
 * + This function check shared memory pointer and return true if it is set or
 * + false when it is set to null.
 *
 * Return: 2
 * + False: Shared memory pointer is set to null
 * + True: Shared memory pointer is set to value in shared area
 *
 * Params: 1
 * + SharedMemory *shared: Pointer to shared memory for work on it
 */
static bool
	isSetSharedMemoryPointer (SharedMemory *shared)
{
	return (bool) (shared->pointer != SHARED_MEMORY_NULLPTR);
}

/*
 * Description
 * + This function set shared memory pointer to given address in shared area.
 *
 * Return: 0
 * + void
 *
 * Params: 2
 * + SharedMemory *shared: Pointer to shared memory for work on it
 * + uint8_t address: Address to set
 */
static void
	setSharedMemoryPointer (SharedMemory *shared, uint8_t address)
{
	shared->pointer = address % SHARED_MEMORY_SIZE;
}

/*
 * Description
 * + This function return value from shared memory from given address.
 *
 * Return: 1
 * + char: Value in shared memory from given address
 *
 * Params: 2
 * + SharedMemory *shared: Pointer to shared memory for work on it
 * + uint8_t address: Address in shared area to read from
 */
static char
	readSharedMemoryArea (SharedMemory *shared, uint8_t address)
{
	return shared->area[address % SHARED_MEMORY_SIZE];
}

/*
 * Description
 * + This function set given value to given address in shared area
 *
 * Return: 0
 * + void
 *
 * Params: 3
 * + SharedMemory *shared: Pointer to shared memory for work on it
 * + uint8_t address: Address in shared area to write to
 * + char data: New data to write
 */
static void
	writeSharedMemoryArea (SharedMemory *shared, uint8_t address, char data)
{
	shared->area[address % SHARED_MEMORY_SIZE] = data;
}

/*
 * Description
 * + This function read sequence values from shared memory using pointer as
 * + address and increment it after read.
 *
 * Return: 1
 * + char: Value from shared area
 *
 * Params: 1
 * + SharedMemory *shared: Pointer to shared memory for work on it
 */
static char
	readSharedMemory (SharedMemory *shared)
{
	shared->pointer = shared->pointer % SHARED_MEMORY_SIZE;

	return shared->area[shared->pointer ++];
}

/*
 * Description
 * + This function write sequence values from shared memory using pointer as
 * + address and increment it after read.
 *
 * Return: 0
 * + void
 *
 * Params: 2
 * + SharedMemory *shared: Pointer to shared memory for work on it
 * + char data: New data to write
 */
static void
	writeSharedMemory (SharedMemory *shared, char data)
{
	shared->pointer = shared->pointer % SHARED_MEMORY_SIZE;

	shared->area[shared->pointer ++] = data;
}
