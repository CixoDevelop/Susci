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


#pragma once


/*
 * Description
 * + This function is called when the system is ready to create processes and
 * + the platform is properly initialized. So write your own project 
 * + initiation here.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void 
  susciBoot (void);

/*
 * Description
 * + This function is run just before the processor freezes at the time of the
 * + system failure, or if any of the processes returns a fatal error.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
static inline void 
  susciPanic (void);

/*
 * Description
 * + Overwriting the function with the main system bootloader.
 *
 * Return: 0
 * + void
 *
 * Params: 0
 * + void
 */
int 
	main(void)
{
    /* Init all modules */
    platformInit ();
    schedulerInit ();
    susciBoot ();

    /* Run scheduler */
    while (schedulerLoop () == GOOD)
        
        /* Wake up functions if time has elapsed */ 
        periodicWakeUp ();

    /* If scheduler return error, run panic function */
    susciPanic ();

    /* And freezee */
    while (true);
}