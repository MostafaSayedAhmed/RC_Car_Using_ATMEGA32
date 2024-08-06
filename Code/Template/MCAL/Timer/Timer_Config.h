/*
 * Timer_Config.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

#define DIS 0
#define EN  1

// Waveform Generation Mode
#define NORMAL_MODE   0
#define PHASE_PWM     1
#define CTC           2
#define FAST_PWM      3

#define WAVEFORM_Timer0 FAST_PWM
#define WAVEFORM_Timer2 FAST_PWM

// Compare Match Output Mode
//     Compare Match                Fast PWM                               Fast PWM Phase Correct
#define NORMAL_PORT     0      //  Normal Port                              Normal Port
#define TOG_OC          1      //  Reserved                                  Reserved
#define CLR_OC          2      //  Clear On CM and Set at TOP                Clear CM up and Set CM down
#define SET_OC          3      //  Set   On CM and Clear at TOP              Set CM up and Clear CM down

#define COMPARE_MATCH_Timer0    CLR_OC
#define COMPARE_MATCH_Timer1A   NORMAL_PORT
#define COMPARE_MATCH_Timer1B   NORMAL_PORT
#define COMPARE_MATCH_Timer2    CLR_OC

// Clock Select Prescaler
#define NO_CLK             0
#define NO_PRE             1
#define PRE_8              2
#define PRE_64             3
#define PRE_256            4
#define PRE_1024           5
// This Two Modes used for counter     Pins:   Timer 0   Timer 1     Timer 2
#define EX_CLK_FALL_EDGE   6                //  T0         T1          T2
#define EX_CLK_RISE_EDGE   7

#define CLK_SEL_Timer0         PRE_1024
#define CLK_SEL_Timer1         NO_PRE
#define CLK_SEL_Timer2         PRE_1024

// Waveform Generation Mode For Timer1
#define NORMAL_MODE           0
#define PHASE_PWM_8           1
#define PHASE_PWM_9           2
#define PHASE_PWM_10          3
#define CTC_OCR1A             4
#define FAST_PWM_8            5
#define FAST_PWM_9            6
#define FAST_PWM_10           7
#define PHASE_PWM_Freq_ICR1   8
#define PHASE_PWM_Freq_OCR1A  9
#define PHASE_PWM_ICR1       10
#define PHASE_PWM_OCR1A      11
#define CTC_ICR1             12
#define RESERVED             13
#define FAST_PWM_ICR1        14
#define FAST_PWM_OCR1A       15

#define WAVEFORM_Timer1 NORMAL_MODE

// Timer 2 Asynchronous Mode
#define ASYNC_MODE     DIS   // (EN/DIS)


// Timer Overflow Interrupt
#define Tim0_OV_INT  DIS
#define Tim1_OV_INT  DIS
#define Tim2_OV_INT  DIS

// Timer Compare Interrupt
#define Tim0_CMP_INT  DIS
#define Tim1_CMP_INT  DIS
#define Tim2_CMP_INT  DIS

// Timer Compare Initial Value (0 - 255)
#define Tim0_CTC       128
#define Tim1_CTC       255
#define Tim2_CTC       128

// Pins Name
#define OC0     3
#define OC1A    5
#define OC1B    4
#define OC2     7
/*
 * Notes:
 * Don't change value of TOP in middle of operation to be close to BOTTOM as compare may be missed
 * As CTC mode isn't double buffered so changing value of OCRn will take effect Instantly
 * Freq of waveform = f_clk/(2*N*(1 + OCRn))      N is prescaler value
 * Fast PWM has higher frequency than phase PWM as Fast is Single Slope Operation while Phase is Dual Slope
 * Fast PWM used for Power Regulation, Rectification , DAC Application and Small Size Components
 * Fast PWM Frequency = F_clk/(N*256)
 * Phase Correct PWM Provide High Resolution waveform , Preferred for Motor Control Applications (Why?)
 * Fast PWM Frequency = F_clk/(N*510)
 * Note: n can be 0,1,2
 * for Timer 1 , to write in 16 bit register high byte then low byte , to read , low byte then high byte
 *                          TCCRn : Timer/Counter Control Register
 *                  TCCRn : FOCn WGMn0 COMn1 COMn0 WGMn1 CSn2 CSn1 CSn0
 * FOCn  : only non PWM Mode and used as strobe to perform instant compare doesn't generate interrupt or clear timer
 * WGMn1:0 : specify waveform mode either normal , CTC , Fast PWM , Phase PWM
 * COMn1:0 : Control Output compare pin (OCn)
 * CSn2:0  : Select Clock Source used by Timer
 *                          TCNTn : Timer/Counter Register
 *                          Contain value of Timer
 *                          OCCRn : Output Compare Register
 *                          its content is continuously compared with Timer value
 *                          TIMSK : Timer/Counter Interrupt Mask Register
 *                          TIMSK : OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0
 * OCIEn (n = 0 ,2) : Output Compare Match Interrupt Setting , 1 -> interrupt (Together with I-bit in SREG)
 * TOIEn (n = 0 ,2) : Timer Overflow Interrupt Setting       , 1 -> interrupt (Together with I-bit in SREG)
 *                          TIFR : Timer/Counter Flag Register
 *                          TIFR : OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0
 * OCFn (n = 0 ,2) : Output Compare Match Flag , cleared by hardware and it is cleared by writing 1 to it
 * TOVn (n = 0 ,2) : Timer Overflow Interrupt Setting ,cleared by hardware and it is cleared by writing 1 to it
 *                          SFIOR : Special Function IO Register
 *                          SFIOR : ADTS2 ADTS1 ADTS0 - ACME PUD PSR2 PSR10
 * PSR10 : Prescaler Reset used to reset operation by writing 1 to it , writing zero to it is pointless
 * PSR2 : Prescaler Reset used to reset operation by writing 1 to it , writing zero to it is pointless
 * For Timer 2 Only
 *                          ASSR : Asynchronous Status Register
 *                          ASSR : - - - - AS2 TCN2UB OCR2UB TCR2UB
 * AS2 : 1 -> Enable Asynchronous mode and 0 -> disable it , in Async is clked from Crystal at TOSC1
 * TCN2UB : indicate whether TCNT2 is written (HIGH) or it is ready to be updated with new value (LOW)
 * OCR2UB : indicate whether OCR2 is written (HIGH) or it is ready to be updated with new value (LOW)
 * TCR2UB : indicate whether TCCR2 is written (HIGH) or it is ready to be updated with new value (LOW)
 * CPU main Clock must be more than four times the oscillator frequency (External Source)
 *
 * for Timer 1
 * f_OC_PWM = f_CPU / (N * TOP)
 * f_OC_Phase_Correct = f_CPU/(2 * N * TOP)
 *                          TCCR1A : Timer/Counter 1 Control Register
 *                          TCCR1A : COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10
 *                          TCCR1B : Timer/Counter 1 Control Register
 *                          TCCR1B : COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10
 */

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
