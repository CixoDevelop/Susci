#ifndef SUSCI_SETTINGS_INCLUDED
#define SUSCI_SETTINGS_INCLUDED

/** \def PROCESS_HEAP_SIZE
 * Size of process heap, this determinate how much processes You can use.
 */
#define PROCESS_HEAP_SIZE 4

/** \def BUFFER_SIZE
 * Set default buffer size 
 */
#define BUFFER_SIZE 8

/** \def CIRCULAR_BUFFER_SIZE
 * Set default circular buffer size.
 */
#define CIRCULAR_BUFFER_SIZE 8

/** \def SHARED_MEMORY_SIZE 
 * Shared memory size in bytes.
 */
#define SHARED_MEMORY_SIZE 8

/** \def USE_HARDWARE_UART
 * Uncomment if You want to use hardware uart.
 */
//#define USE_HARDWARE_UART

/** \def USE_PINS
 * Uncomment if You want to use pins.
 */
//#define USE_PINS

/** \def USE_PINCHANGE
 * Uncomment if You want to use pinchane interrrupt.
 */
//#define USE_PINCHANGE

/** \def USE_TWI_SLAVE
 * Uncomment if You want to use pinchane interrrupt.
 */
//#define USE_TWI_SLAVE

/** \def USE_ADC
 * Uncommend if You want to use ADC.
 */
//#define USE_ADC

/** \def TYPE_LAYOUT
 * Your MCU package configuration for PIN_x macros.
 */
#define DIP_LAYOUT

/** \def F_CPU
 * Your MCU F_CPU in Hz.
 */
#define F_CPU 8000000UL

/**
 * Define Your MCU port
 */
#define MCU_ATMEGA_328

#endif
