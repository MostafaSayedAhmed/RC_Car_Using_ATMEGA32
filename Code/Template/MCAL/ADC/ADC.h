/*
 * ADC.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../Units.h"
#include "../../BIT_Math.h"
#include <avr/io.h>
#include  "ADC_config.h"


// Enumeration Type used to specify channel according to input of ADC_Read Function
typedef enum{
	ADC_0,
	ADC_1,
	ADC_2,
	ADC_3,
	ADC_4,
	ADC_5,
	ADC_6,
	ADC_7,
}ADC_Num;

void ADC_init();

unit16 ADC_Read(ADC_Num Channel);

#endif /* MCAL_ADC_ADC_H_ */
