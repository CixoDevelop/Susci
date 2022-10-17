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
 * functions responsibles for working with standard system Buffer.
 */

#include "../settings.h"
#include "../kernel/types.h"
#include "buffer.h"

/** \fn read_buffer
 * Return next char from buffer, must first check if buffer is readable.
 * @*buffer: Buffer object
 */
char read_buffer(buffer_t *buffer) {
    char data = buffer->buffer[buffer->read_position++];

    if (all_data_read_from_buffer(buffer)) reset_buffer(buffer);

    return data;
}

/** \fn write_buffer
 * Write new data to buffer.
 * @*buffer: Buffer object
 * @data: New data to write
 */
bool write_buffer(buffer_t *buffer, char data) {
    if (!is_buffer_writable(buffer)) return false;
    
    buffer->buffer[buffer->write_position++] = data;
    
    return true;
}
