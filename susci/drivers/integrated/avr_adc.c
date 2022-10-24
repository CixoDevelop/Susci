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
 * This file stores code for drivers responsible for managment
 * microcontroller ADC.
 */

#include "../../settings.h"
#include "../../platforms/avr.h"

#ifdef USE_AVR_ADC

#include <avr/io.h>

#include "adc.h"
#include "../../kernel/types.h"

/** \fn setup_adc_reference
 * This setup voltage reference for ADC.
 * @adc_reference Reference switches for ADC
 */
void setup_adc_reference(adc_mux_t adc_reference) {
    ADMUX = adc_reference;

    ADCSRA |= (
        (1 << ADPS2) |
        (1 << ADPS1) | 
        (1 << ADPS0)
    );
}

/** \fn read_from_adc
 * This function return data readed from adc on mux given in parameter.
 * @adc_pin Mux to read from
 */
adc_result_t read_from_adc(adc_mux_t adc_mux) {
    /*
     * Set ADMUX, read data and return it.
     */

     ADMUX &= 0xE0;
     ADMUX |= adc_mux;

     ADCSRA = (
        (1 << ADEN) |
        (1 << ADSC)
     );

     while (ADCSRA & (1 << ADSC)) ;

     return (adc_result_t) (ADC);
}

#endif
