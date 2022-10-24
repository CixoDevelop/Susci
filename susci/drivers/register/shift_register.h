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
#include "../integrated/pins.h"
#include "../../kernel/process.h"
#include "../../kernel/types.h"
#include "../../synchronization/latch.h"

#ifndef DRIVERS_REGISTER_SHIFT_REGISTER_H_INCLUDED
#define DRIVERS_REGISTER_SHIFT_REGISTER_H_INCLUDED

#ifdef USE_PINS

/** \struct shift_register_t
 * This struct store config of shift register.
 */
typedef struct {

    /* For sending new data to register */
    latch_t latch;
	
    /* For storing pins */
    pin_t da;
    pin_t st_cp;
    pin_t sh_cp;

} shift_register_t;

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
);

/** \fn shift_register_driver
 * This is service to manage shift register hardware.
 * @*shift_register_pointer This is pointer to object
 */
exec_state_t shift_register_driver(void *shift_register_pointer);

/** \struct procedural_shift_register_t
 * This is procedural shift register object struct.
 */
typedef struct {
    pin_t da;
    pin_t st_cp;
    pin_t sh_cp;
} procedural_shift_register_t;

/** \fn create_procedural_shift_register
 * This create object and prepare hardware for working with shift register.
 * @da DA shift register pin
 * @st_cp ST_CP shift register pin
 * @sh_cp SH_CP shift register pin
 */
procedural_shift_register_t create_procedural_shift_register(
    pin_t da, 
    pin_t st_cp, 
    pin_t sh_cp
);

/** \fn procedural_shift_register_driver
 * This function send data to shift register procedural and just in time, no
 * by process like shift_register_driver.
 * @shift_register This is pointer to object
 */
void procedural_shift_register_driver(
    procedural_shift_register_t *shift_register, 
    char data,
    bool commit
);

#endif

#endif
