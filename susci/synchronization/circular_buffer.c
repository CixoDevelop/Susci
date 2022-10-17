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
#include "circular_buffer.h"

/** \fn write_circular_buffer
 * Write new data to circular buffer.
 * @*buffer: CircularBuffer object
 * @data: New data for buffer
 */
void write_circular_buffer(circular_buffer_t *buffer, char data) {
    buffer->buffer[buffer->write_position++] = data;
    buffer->write_position %= CIRCULAR_BUFFER_SIZE;
}

/** \fn read_circulat_buffer
 * Return data from buffer.
 * @*buffer: CircularBuffer object
 */
char read_circular_buffer(circular_buffer_t *buffer) {
    char data = buffer->buffer[buffer->read_position++];
    
    buffer->read_position %= CIRCULAR_BUFFER_SIZE;

    return data;
}
