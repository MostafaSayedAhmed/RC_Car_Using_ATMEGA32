/*
 * Timer.h
 *
 *  Created on: Sep 24, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include"../../BIT_Math.h"
#include"../../MCAL/DIO/DIO.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer_Config.h"

// Initializing Section
void Timer0_init();
void Timer1_init();
void Timer2_init();

// Timer Mode
unit8 CheckTimer0();
unit8 CheckTimer1();
unit8 CheckTimer2();

// Counter Mode
unit8 Counter0();
unit16 Counter1();
unit8 Counter2();

// Set Call Back Function
void SetCallBackTimer0OVF(void (*ptr)());
void SetCallBackTimer0CMP(void (*ptr)());
void SetCallBackTimer1OVF(void (*ptr)());
void SetCallBackTimer1COMPA(void (*ptr)());
void SetCallBackTimer1COMPB(void (*ptr)());
void SetCallBackTimer2OVF(void (*ptr)());
void SetCallBackTimer2CMP(void (*ptr)());

// PWM

unit8 PWM_Write(channel_type channel,unit8 PWM);

#endif /* MCAL_TIMER_TIMER_H_ */
