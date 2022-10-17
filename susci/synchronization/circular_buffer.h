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
 * This file stores declarations and definitions of data structures and
 * functions responsibles for CircularBuffer in system.
 */

#include "../settings.h"
#include "../kernel/types.h"

#ifndef SYNCHRONIZATION_CIRCULAR_BUFFER_H_INCLUDED
#define SYNCHRONIZATION_CIRCULAR_BUFFER_H_INCLUDED

/** \struct circular_buffer_t
 * Struct for circular buffer.
 */
typedef struct {

    /* Reader position */
    uint8_t read_position;

    /* Writer position */
    uint8_t write_position;

    /* Alocate memory for circular buffer */
    char buffer[CIRCULAR_BUFFER_SIZE];

} circular_buffer_t;

/** \fn create_circular_buffer
 * This function creating empty circular buffer and returning it.
 */
static inline circular_buffer_t create_circular_buffer(void) {
    return (circular_buffer_t) {0x00, 0x00, {0x00}};
}

/** \fn write_circular_buffer
 * Write new data to circular buffer.
 * @*buffer: CircularBuffer object
 * @data: New data for buffer
 */
void write_circular_buffer(circular_buffer_t *buffer, char data);

/** \fn read_circulat_buffer
 * Return data from buffer.
 * @*buffer: CircularBuffer object
 */
char read_circular_buffer(circular_buffer_t *buffer);

#endif
