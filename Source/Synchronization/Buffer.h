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


#pragma once


/* Set default buffer size */
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 8
#endif

/* Struct for buffer */
typedef struct {
    
    /* Readed position in buffer */
    uint8_t read_position;

    /* Writer position in buffer */
    uint8_t write_position;

    /* Memory for buffer */
    char buffer[BUFFER_SIZE];

} Buffer;

/*
 * Description
 * + This function creating empty buffer and returning it.
 *  
 * Return: 1
 * + Buffer: New empty buffer
 *
 * Params: 0
 * + void
 */
static inline Buffer
    createBuffer ()
{
    /* New empty buffer */
    return (Buffer) {0x00, 0x00, {0x00}};
}

/*
 * Description
 * + Checks that the buffer is readable.
 *  
 * Return: 2
 * + True: Buffer is readable
 * + False: Buffer is not readable
 *
 * Params: 1
 * + Buffer *buffer: Buffer object
 */
static inline bool
    isBufferReadable (Buffer *buffer)
{
    /* If reader is less than writer, buffer is readable */
    return (bool) (buffer->read_position < buffer->write_position);
}

/*
 * Description
 * + Return next char from buffer, must first check if buffer is readable.
 *  
 * Return: 1
 * + char: Char from buffer
 *
 * Params: 1
 * + Buffer *buffer: Buffer object
 */
static char
    readBuffer (Buffer *buffer)
{
    /* Get next char from buffer */
    char data = buffer->buffer[buffer->read_position ++];

    /* If reader == writer, then all was read */
    if (buffer->read_position == buffer->write_position)

        /* Buffer can be reset */
        buffer->read_position = buffer->write_position = 0x00;
    
    /* Return read data */
    return data;
}

/*
 * Description
 * + Write new data to buffer
 *  
 * Return: 2
 * + True: Everything done
 * + False: Buffer is full
 *
 * Params: 1
 * + Buffer *buffer: Buffer object
 * + char data: New data to write
 */
static bool
    writeBuffer (Buffer *buffer, char data)
{
    /* If buffer is full, return false */
    if (buffer->write_position >= BUFFER_SIZE)
        return false;

    /* Write new data */
    buffer->buffer[buffer->write_position ++] = data;

    /* Return true */
    return true;
}