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

#include "../kernel/types.h"
#include "latch.h"

/** \fn push_latch 
 * This function push new data to latch.
 * @*latch Latch object to operate on
 * @data New data to push
 */
bool push_latch(latch_t *latch, char data) {
    if (latch->flag == SET_FLAG) return false;

    latch->flag = SET_FLAG;
    latch->data = data;

    return true;
}

/*
 * This function pop data from latch.
 * @*latch Latch object to operate on
 */
char pop_latch(latch_t *latch) {
    latch->flag = EMPTY_FLAG;

    return latch->data;
}
