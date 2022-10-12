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

#ifndef SYNCHRONIZATION_BUFFER_H_INCLUDED
#define SYNCHRONIZATION_BUFFER_H_INCLUDED

/** \def BUFFER_SIZE
 * Set default buffer size 
 */
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 8
#endif

/** \fn buffer_t
 * Struct for buffer.
 */
typedef struct {
    
    /* Readed position in buffer */
    uint8_t read_position;

    /* Writer position in buffer */
    uint8_t write_position;

    /* Memory for buffer */
    char buffer[BUFFER_SIZE];

} buffer_t;

/** \fn create_buffer
 * This function creating empty buffer and returning it.
 */
static inline buffer_t create_buffer() {
    return (buffer_t) {0x00, 0x00, {0x00}};
}

/** \fn is_buffer_readable
 * Checks that the buffer is readable.
 * @*buffer Buffer object
 */
static inline bool is_buffer_readable(buffer_t *buffer) {
    return (bool) (buffer->read_position < buffer->write_position);
}

/** \fn is_buffer_writable
 * Check that the buffer is writable.
 * @*buffer Buffer object
 */
static inline bool is_buffer_writable(buffer_t *buffer) {
    return (bool) (buffer->write_position <= BUFFER_SIZE);
}

/** \fn all_data_read_from_buffer
 * Return true if user read all data from buffer and it can be reset.
 */
static inline bool all_data_read_from_buffer(buffer_t *buffer) {
    return (bool) (buffer->read_position == buffer->write_position);
}

/** \fn reset_buffer
 * This reset buffer for writing new data.
 */
static inline void reset_buffer(buffer_t *buffer) {
    buffer->read_position = buffer->write_position = 0x00;
}

/** \fn read_buffer
 * Return next char from buffer, must first check if buffer is readable.
 * @*buffer: Buffer object
 */
static char read_buffer(buffer_t *buffer) {
    char data = buffer->buffer[buffer->read_position ++];

    if (all_data_read_from_buffer(buffer)) reset_buffer(buffer);

    return data;
}

/** \fn write_buffer
 * Write new data to buffer.
 * @*buffer: Buffer object
 * @data: New data to write
 */
static bool write_buffer(buffer_t *buffer, char data) {
    if (!is_buffer_writable(buffer)) return false;
    
    buffer->buffer[buffer->write_position ++] = data;
    
    return true;
}

#endif
