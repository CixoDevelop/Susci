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


#pragma once


/* Set default circular buffer size */
#ifndef CIRCULAR_BUFFER_SIZE
    #define CIRCULAR_BUFFER_SIZE 8
#endif

/* Struct for circular buffer */
typedef struct {

    /* Reader position */
    uint8_t read_position;
    
    /* Writer position */
    uint8_t write_position;

    /* Alocate memory for circular buffer */
    char buffer[CIRCULAR_BUFFER_SIZE];

} CircularBuffer;

/*
 * Description
 * + This function creating empty circular buffer and returning it.
 *  
 * Return: 1
 * + CircularBuffer: New empty circular buffer
 *
 * Params: 0
 * + void
 */
static inline CircularBuffer
    createCircularBuffer ()
{
    /* Empty circular buffer */
    return (CircularBuffer) {0x00, 0x00, {0x00}};
}

/*
 * Description
 * + Write new data to circular buffer.
 *  
 * Return: 0
 * + void
 *
 * Params: 2
 * + CircularBuffer *buffer: CircularBuffer object
 * + char data: New data for buffer
 */
static void
    writeCircularBuffer (CircularBuffer *buffer, char data)
{
    /* Save data to buffer */
    buffer->buffer[buffer->write_position ++] = data;

    /* Correct for overflow */
    buffer->write_position %= CIRCULAR_BUFFER_SIZE;
}

/*
 * Description
 * + Return data from buffer.
 *  
 * Return: 2
 * + char: Data from buffer
 *
 * Params: 1
 * + CircularBuffer *buffer: CircularBuffer object
 */
static char
    readCircularBuffer (CircularBuffer *buffer)
{
    /* Get data from buffer */
    char data = buffer->buffer[buffer->read_position ++];

    /* Correct for overflow */
    buffer->read_position %= CIRCULAR_BUFFER_SIZE;

    /* Return read data */
    return data;
}