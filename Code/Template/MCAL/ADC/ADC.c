/*
 * ADC.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Mostafa Sayed
 */

#include"ADC.h"

// Configure ADC according to content of ADC_config.h File
void ADC_init(){

// Enable ADC
	SET_BIT(ADCSRA,ADEN);

// Select Prescaler

#if Prescaler == 2
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif Prescaler == 4
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif Prescaler == 8
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
#elif Prescaler == 16
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif Prescaler == 32
	SET_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif Prescaler == 64
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#elif Prescaler == 128
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#endif

// Select Reference Voltage

#if VOLTAGE_REF == AREF_ON
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif VOLTAGE_REF == AVCC_CAP_AREF
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif VOLTAGE_REF == RESERVED
	CLR_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#elif VOLTAGE_REF == IN_AVREF_CAP_AREF
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#endif



// Enable Triggering MODE
#if TRIGGER == AUTOTRIGGED_OFF
	CLR_BIT(ADCSRA,ADATE);
#else
	SET_BIT(ADCSRA,ADATE);
	// Select Triggering Source
	#if TRIGGER_SOURCE == FREE_RUNNING
	   CLR_BIT(SFIOR,ADTS0);
	   CLR_BIT(SFIOR,ADTS1);
	   CLR_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == ANALOG_COMPARATOR
	   SET_BIT(SFIOR,ADTS0);
	   CLR_BIT(SFIOR,ADTS1);
	   CLR_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == EXT_INT_0
	   CLR_BIT(SFIOR,ADTS0);
	   SET_BIT(SFIOR,ADTS1);
	   CLR_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == TIMER0_COMP_MATCH
	   SET_BIT(SFIOR,ADTS0);
	   SET_BIT(SFIOR,ADTS1);
	   CLR_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == TIMER0_OVF
	   CLR_BIT(SFIOR,ADTS0);
	   CLR_BIT(SFIOR,ADTS1);
	   SET_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == TIMER_COMP_MATCH
	   SET_BIT(SFIOR,ADTS0);
	   CLR_BIT(SFIOR,ADTS1);
	   SET_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == TIMER1_OVF
	   CLR_BIT(SFIOR,ADTS0);
	   SET_BIT(SFIOR,ADTS1);
	   SET_BIT(SFIOR,ADTS2);
	#elif TRIGGER_SOURCE == TIMER1_CAP_EVENT
	   SET_BIT(SFIOR,ADTS0);
	   SET_BIT(SFIOR,ADTS1);
	   SET_BIT(SFIOR,ADTS2);
	#endif
#endif
}

// Function to read Data Register of ADC (Single Conversion)
unit16 ADC_Read(ADC_Num Channel){

	// Select Channel
	switch(Channel)
	{
	case ADC_0:
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_1:
		SET_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_2:
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_3:
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_4:
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_5:
		SET_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_6:
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	case ADC_7:
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		break;
	}
  // For Single Conversion Mode
  if(!TRIGGER){
		// Start Conversion
		SET_BIT(ADCSRA,ADSC);
   }

	// Wait till interrupt flag is cleared then reset it for the next conversion
	while(GET_BIT(ADCSRA,ADIF) == 0);
	SET_BIT(ADCSRA,ADIF);
	unit16 result = ADC;
    return result;
}
