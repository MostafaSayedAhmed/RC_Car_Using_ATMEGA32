/*
 * ADC_config.h
 *
 *  Created on: Sep 23, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

// Reference Voltage Selection

#define AREF_ON            0            // Internal Vref is turned off
#define AVCC_CAP_AREF      1            // Use External Capacitor at AREF
#define RESERVED           2            // Not Used (Reserved)
#define IN_2_56V_CAP_AREF  3            // internal Vref with External Capacitor at AREF

#define VOLTAGE_REF AREF_ON

//////////////////////////////////

// Adjustment Selection
// Specify Result arrangement

#define RIGHT_ADJUST 0                 // Start from ADCL to ADCH
#define LEFT_ADJUST  1                 // Start from ADCH to ADCL

#define ADJUST RIGHT_ADJUST

/////////////////////////////////

// Channel Selection refer to table 84 in datasheet


// Prescaler selector refer to table 85 in datasheet
// Prescaler Value can be (2 4 8 16 32 64 128)

#define Prescaler 64

// Auto Triggering Mode ON or OFF
#define AUTOTRIGGED_OFF   0
#define AUTOTRIGGED_ON    1

#define TRIGGER   AUTOTRIGGED_ON

// Auto Triggering Source (Require Enabling Auto Trigger Mode)
#define FREE_RUNNING          0           // Conversion is Done Automatically one after another
#define ANALOG_COMPARATOR     1           // using Pins AIN0 +ve terminal , AIN1 -ve terminal require separate driver
#define EXT_INT_0             2           // External interrupt zero enable triggering
#define TIMER0_COMP_MATCH     3           // Trigger on Timer 0 Compare match
#define TIMER0_OVF            4           // Trigger on Timer 0 Overflow
#define TIMER_COMP_MATCH      5           // Trigger on Timer Compare match
#define TIMER1_OVF            6           // Trigger on Timer 1 Overflow
#define TIMER1_CAP_EVENT      7           // Trigger on Timer 1 Capture Event

#define  TRIGGER_SOURCE TIMER0_OVF
// Data Register is ADC Register

/////////////////////////////////

// Important Documentation
// ADC has 10-bit resolution with GND represent Minimum value and AREF - 1 represent maximum value
// if the result is left adjusted and no more than 8-bit precision is required, it is sufficient to
// read ADCH ADCL must be read first, then ADCH, to ensure that the content
// of the Data Registers belongs to the same conversion. we should read both upper and lower data register
// before doing another conversion
// Note: to get maximum resoulution the input clock need to be from 50 to 200 kHz
// for lower resolution use higher clock than 200 kHz
// to increase noise immunity of reference pin to noise, introduce capacitor between AREF and GND
// to increase accuracy and minimize noise , connect AVCC to VCC through LC Network
// Data Register result = (Vin/Vref) * 1024 , for differential = (Vpos - Vneg /Vref) * GAIN * 512
// The differential input channels are not tested for devices in PDIP Package.
// differential feature is only guaranteed to work for devices in TQFP and MLF Packages
#endif /* MCAL_ADC_ADC_CONFIG_H_ */
