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
 * This file is the system bootloader, it is responsible for the initialization
 * of the platform and then the operation of the system. You should override 
 * the functions susciBoot and susciPanic which are individual for the project.
 */

#include "../settings.h"
#include "process.h"
#include "scheduler.h"
#include "time.h"
#include "loader.h"
#include "platform.h"

/** \fn main 
 * Overwriting the function with the main system bootloader.
 */
int main(void) {
    /* Init all modules */
    platform_init();
    scheduler_init();
    susci_boot();

    /* Run scheduler and timer */
    while (scheduler_loop() == GOOD_STATE) check_timer_processes();

    /* Any process return PANIC_STATE, handle error */
    susci_panic();
    while (true);
}
