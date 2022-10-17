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

#ifndef SYNCHRONIZATION_LATCH_H_INCLUDED
#define SYNCHRONIZATION_LATCH_H_INCLUDED

/** \enum latch_flag_t
 * This store state of latch, empty or set
 */
typedef enum {
 
    /* Latch is empty, you can insert data to it */
    EMPTY_FLAG = 0,

    /* Latch is set, you can not insert data into it */
    SET_FLAG = 1

} latch_flag_t;

/** \struct latch_t
 * This is latch object.
 */
typedef struct {
 
    /* Data in latch */
    char data;

    /* Latch flag */
    latch_flag_t flag;

} latch_t;

/** \fn create_latch
 * This function create new latch object.
 */
static inline latch_t create_latch(void) {
    return (latch_t) {0x00, EMPTY_FLAG};
}

/** \fn push_latch 
 * This function push new data to latch.
 * @*latch Latch object to operate on
 * @data New data to push
 */
bool push_latch(latch_t *latch, char data);

/*
 * This function pop data from latch.
 * @*latch Latch object to operate on
 */
char pop_latch(latch_t *latch);

/** \fn get_latch_busy_flag
 * This function return latch flag.
 * @*latch: Latch object to operate on
 */
static inline latch_flag_t get_latch_busy_flag(latch_t *latch) {
    return latch->flag;
}

/** \fn get_latch_data
 * This function return data in latch, but not change flag state.
 * @*latch Latch object to operate on
 */
static inline char get_latch_data(latch_t *latch) {
    return latch->data;
}

#endif
