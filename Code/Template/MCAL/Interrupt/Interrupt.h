/*
 * Interrupt.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_H_
#define MCAL_INTERRUPT_INTERRUPT_H_

#include "../../BIT_Math.h"
#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Interrupt_Config.h"

void Interrupt_Enable();

void SetCallbackFunction_INT0(void (*fun)());
void SetCallbackFunction_INT1(void (*fun)());
void SetCallbackFunction_INT2(void (*fun)());

#endif /* MCAL_INTERRUPT_INTERRUPT_H_ */
