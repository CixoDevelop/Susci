/*
 * Hello in Susci system!
 * This is you application main file (core.c).
 * You must read config options below, and select good for your project.
 * Your project files, headers, etc would be write into project/
 * If you use doxygen syntax in your files, you can create docs who will be 
 * saved into docs/ with doxygen doxygen. That will include this file, 
 * project/ and susci/.
 * Good luck, and write to cixolaptop@gmail.com or on CixoDevelop github 
 * if you want help!
 *
 * PS: After config you can remove this comment!
 */

/** \def CHIP_LAYOUT 
 * Define for using PIN_x macro. 
 * You can use DIP or SOP or QFP.
 */
#define DIP_LAYOUT

/** \def USE_TWI_SLAVE
 * Uncomment if you want to use twi as slave.
 */
//#define USE_TWI_SLAVE

/** \def USE_PINCHANGE_INTERRUPT
 * Uncomment if you want to use pinchange interrupt.
 */
//#define USE_PINCHANGE_INTERRUPT


/** \def PROSESS_HEAP_SIZE
 * Size of process heap, that determinate how many process you can use.
 * Default (if you remove it): 4
 */
#define PROCESS_HEAP_SIZE 4

/** \def BUFFER_SIZE
 * Size of buffer_t in bytes
 * Default (if you remove it): 8
 */
#define BUFFER_SIZE 8

/** \def CIRCULAR_BUFFER_SIZE
 * Size of circular_buffer_t in bytes
 * Default (if you remove it): 8
 */
#define CIRCULAR_BUFFER_SIZE 8

/** \def SHARED_MEMORY_SIZE
 * Size of buffer_t in bytes
 * Default (if you remove it): 8
 */
#define SHARED_MEMORY_SIZE 8

/* Change for Your platform */
#include "susci/platforms/attiny261.h"
#include "susci/kernel.h"

static inline void susci_boot(void) {
    /* Insert Your init here */
}

static inline void susci_panic(void) {
    /* Insert Your panic here */
}
