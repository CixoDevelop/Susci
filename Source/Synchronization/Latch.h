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
 * This file stores data specific to the AVR ATtiny261 platform.
 */

#pragma once

/* This store current latch state */
typedef enum {
    UNSET = 0,
    SET = 1
} LatchFlag;

/* This is latch object */
typedef struct {
    char data;
    LatchFlag flag;
} Latch;

/*
 * Description
 * + This function create new latch object.
 *
 * Return: 1
 * + Latch: New latch object
 *
 * Params: 0
 * + void
 */
static inline Latch
    createLatch (void)
{
    return (Latch) {0x00, UNSET};
}

/*
 * Description
 * + This function push new data to latch.
 *
 * Return: 1
 * + bool: Operation state, if succes true, if error false
 *
 * Params: 2
 * + Latch *latch: Latch object to operate on
 * + char data: New data to push
 */
static bool
    pushLatch (Latch *latch, char data)
{
    if (latch->flag == SET)
        return false;

    latch->flag = SET;
    latch->data = data;

    return true;
}

/*
 * Description
 * + This function pop data from latch.
 *
 * Return: 1
 * + char: Data from latch
 *
 * Params: 1
 * + Latch *latch: Latch object to operate on
 */
static char
    popLatch (Latch *latch)
{
    latch->flag = UNSET;

    return latch->data;
}

/*
 * Description
 * + This function return latch flag.
 *
 * Return: 1
 * + LatchFlag: Flag of latch
 *
 * Params: 1
 * + Latch *latch: Latch object to operate on
 */
static inline LatchFlag
    getLatchFlag (Latch *latch)
{
    return latch->flag;
}

/*
 * Description
 * + This function return data in latch, but not change flag state.
 *
 * Return: 1
 * + char: Data in latch
 *
 * Params: 1
 * + Latch *latch: Latch object to operate on
 */
static inline char
    getLatchData (Latch *latch)
{
    return latch->data;
}
