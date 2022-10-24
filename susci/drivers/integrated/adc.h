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
 * This file stores headers for drivers responsible for managment
 * microcontroller ADC.
 */
 
#ifndef DRIVERS_INTEGRATED_ADC_H_INCLUDED
#define DRIVERS_INTEGRATED_ADC_H_INCLUDED

/** \typedef adc_t
 * This is type for adc mux selector
 */
typedef uint8_t adc_mux_t;

/** \typedef adc_result_t
 * This is type for result received from adc.
 */
typedef uint16_t adc_result_t;

/** \fn setup_adc_reference
 * This setup voltage reference for ADC.
 * @adc_reference Reference switches for ADC
 */
void setup_adc_reference(adc_mux_t adc_reference);

/** \fn read_from_adc
 * This function return data readed from adc on mux given in parameter.
 * @adc_pin Mux to read from
 */
adc_result_t read_from_adc(adc_mux_t adc_mux);

#endif
