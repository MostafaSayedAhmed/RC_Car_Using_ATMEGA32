/*
 * Interrupt_Config.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_CONFIG_H_
#define MCAL_INTERRUPT_INTERRUPT_CONFIG_H_

typedef enum{
	DISABLE,
	ENABLE
};

// Sense Control for INT0 and INT1
#define LOW_LEVEL   0
#define ANY_CHANGE  1
#define FALL_EDGE   2
#define RISE_EDGE   3

// SREG
#define EXT_INT ENABLE

// GICR
#define INT_0 DISABLE
#define INT_1 ENABLE
#define INT_2 DISABLE



// MCUCR
//Interrupt 0  and 1 Sense Control

#define INT0_CONTROL RISE_EDGE
#define INT1_CONTROL RISE_EDGE

// Sense Control for INT2
#define FALL_EDGE_INT2 0
#define RISE_EDGE_INT2 1

// MCUCSR
// Interrupt 2 Sense Control
#define INT2_CONTROL RISE_EDGE_INT2

// PAGE 214: ADC Interrupt

#endif /* MCAL_INTERRUPT_INTERRUPT_CONFIG_H_ */
