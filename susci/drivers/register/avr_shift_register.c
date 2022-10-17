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
 * This file stores driver who is responsible for managment shift registers. 
 * This has driver that is standard Susci service for sending data to 
 * register hardware.
 */

#include "../../settings.h"
#include "../../platforms/avr.h"
#include "../../kernel/types.h"
#include "../integrated/pins.h"
#include "../integrated/avr_pins.h"
#include "shift_register.h"

#ifdef USE_AVR_PINS

/** \fn create_shift_register
 * This prepare shift register object in in memory.
 * @da DA shift register pin
 * @st_cp ST_CP shift register pin
 * @sh_cp SH_CP shift register pin
 */
shift_register_t create_shift_register(
    pin_t da, 
    pin_t st_cp, 
    pin_t sh_cp
) {
	/* Set pins as outputs and low state */
    uint8_t da_mask = create_pin_mask(da);
    uint8_t st_cp_mask = create_pin_mask(st_cp);
    uint8_t sh_cp_mask = create_pin_mask(sh_cp);

    *create_pin_output_pointer(da) &= ~da_mask;
    *create_pin_output_pointer(st_cp) &= ~st_cp_mask;
    *create_pin_output_pointer(sh_cp) &= ~sh_cp_mask;

    *create_pin_direction_pointer(da) |= da_mask;
    *create_pin_direction_pointer(st_cp) |= st_cp_mask;
    *create_pin_direction_pointer(sh_cp) |= sh_cp_mask;

	/* New object */
    return (shift_register_t) {create_latch(), da, st_cp, sh_cp};
}

/** \fn shift_register_driver
 * This is service to manage shift register hardware.
 * @*shift_register_pointer This is pointer to object
 */
exec_state_t shift_register_driver(void *shift_register_pointer) {
    /*
     * First check data in latch, if data is empty, return idle state, next
     * send all 8 bits to shift register. On end commit on latch.
     */
    shift_register_t *shift_register = shift_register_pointer;

    if (get_latch_busy_flag(&shift_register->latch) == EMPTY_FLAG) {
        return IDLE_STATE;
    }

    volatile uint8_t *da_output = create_pin_output_pointer(
        shift_register->da
    );
    volatile uint8_t *st_cp_output = create_pin_output_pointer(
        shift_register->st_cp
    );
    volatile uint8_t *sh_cp_output = create_pin_output_pointer(
        shift_register->sh_cp
    );

    uint8_t da_mask = create_pin_mask(shift_register->da);
    uint8_t st_cp_mask = create_pin_mask(shift_register->st_cp);
    uint8_t sh_cp_mask = create_pin_mask(shift_register->sh_cp);

    char to_send = pop_latch(&shift_register->latch);

    for (uint8_t bit = 8; bit > 0; -- bit) {
        if (to_send & (1 << (bit - 1))) *da_output |= da_mask;
        else *da_output &= ~da_mask;

        *sh_cp_output |= sh_cp_mask;
        *sh_cp_output &= ~sh_cp_mask;
    }

    *st_cp_output |= st_cp_mask;
    *st_cp_output &= ~st_cp_mask;

    return GOOD_STATE;
}

#endif
