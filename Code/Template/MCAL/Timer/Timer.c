/*
 * Timer.c
 *
 *  Created on: Sep 24, 2022
 *      Author: Mostafa Sayed
 */

#include "Timer.h"

static void (*ptr2fun0OVF) ();
static void (*ptr2fun0CMP) ();
static void (*ptr2fun1OVF) ();
static void (*ptr2fun1CMPA) ();
static void (*ptr2fun1CMPB) ();
static void (*ptr2fun2OVF) ();
static void (*ptr2fun2CMP) ();

// Initializing Section
void Timer0_init()
{

// Selecting Waveform Mode for Timer 0
#if WAVEFORM_Timer0 == NORMAL_MODE
	  CLR_BIT(TCCR0,WGM00);
	  CLR_BIT(TCCR0,WGM01);
#elif WAVEFORM_Timer0 == PHASE_PWM
	  SET_BIT(TCCR0,WGM00);
	  CLR_BIT(TCCR0,WGM01);
	  CLR_BIT(TCCR0,FOC0);
#elif WAVEFORM_Timer0 == CTC
	  CLR_BIT(TCCR0,WGM00);
	  SET_BIT(TCCR0,WGM01);
	  // Load Compare Match Register with Compare Value
	  	  OCR0 = Tim0_CTC ;
#elif WAVEFORM_Timer0 == FAST_PWM
	  SET_BIT(TCCR0,WGM00);
	  SET_BIT(TCCR0,WGM01);
	  CLR_BIT(TCCR0,FOC0);
#endif

// Select Prescaler for Timer 0
#if   CLK_SEL_Timer0 == NO_CLK
	  CLR_BIT(TCCR0,CS00);
	  CLR_BIT(TCCR0,CS01);
	  CLR_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == NO_PRE
	  SET_BIT(TCCR0,CS00);
	  CLR_BIT(TCCR0,CS01);
	  CLR_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == PRE_8
	  CLR_BIT(TCCR0,CS00);
	  SET_BIT(TCCR0,CS01);
	  CLR_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == PRE_64
	  SET_BIT(TCCR0,CS00);
	  SET_BIT(TCCR0,CS01);
	  CLR_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == PRE_256
	  CLR_BIT(TCCR0,CS00);
	  CLR_BIT(TCCR0,CS01);
	  SET_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == PRE_1024
	  SET_BIT(TCCR0,CS00);
	  CLR_BIT(TCCR0,CS01);
	  SET_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == EX_CLK_FALL_EDGE
	  CLR_BIT(TCCR0,CS00);
	  SET_BIT(TCCR0,CS01);
	  SET_BIT(TCCR0,CS02);
#elif CLK_SEL_Timer0 == EX_CLK_RISE_EDGE
	  SET_BIT(TCCR0,CS00);
	  SET_BIT(TCCR0,CS01);
	  SET_BIT(TCCR0,CS02);
#endif

// Compare Match Mode
//     Compare Match                            Fast PWM                     Fast PWM Phase Correct
#if    COMPARE_MATCH_Timer0 == NORMAL_PORT   //  Normal Port                      Normal Port
	  CLR_BIT(TCCR0,COM00);
	  CLR_BIT(TCCR0,COM01);
#elif  COMPARE_MATCH_Timer0 == TOG_OC         //  Reserved                          Reserved
	  SET_BIT(TCCR0,COM00);
	  CLR_BIT(TCCR0,COM01);
	  // Configure Pin OC0 as Output
	  SET_BIT(DDRB,OC0);
#elif  COMPARE_MATCH_Timer0 == CLR_OC        //  Clear On CM and Set at TOP     Clear CM up and Set CM down
	  CLR_BIT(TCCR0,COM00);
	  SET_BIT(TCCR0,COM01);
	  // Configure Pin OC0 as Output
	  SET_BIT(DDRB,OC0);
#elif  COMPARE_MATCH_Timer0 == SET_OC       //  Set   On CM and Clear at TOP    Set CM up and Clear CM down
	  SET_BIT(TCCR0,COM00);
	  SET_BIT(TCCR0,COM01);
	  // Configure Pin OC0 as Output
	  SET_BIT(DDRB,OC0);
#endif
// Initializing Timer0
  TCNT0 = 0;

// Enable Timer0 Overflow Interrupt
#if Tim0_OV_INT == DISABLE
  CLR_BIT(TIMSK,TOIE0);
#else
  SET_BIT(TIMSK,TOIE0);
#endif

// Enable Timer0 Compare Match Interrupt
#if Tim0_CMP_INT == DISABLE
  CLR_BIT(TIMSK,OCIE0);
#else
  SET_BIT(TIMSK,OCIE0);
#endif

}

void Timer1_init()
{
	// Selecting Mode for Timer 1
#if     WAVEFORM_Timer1 == NORMAL_MODE
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_8
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_9
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_10
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == CTC_OCR1A
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == FAST_PWM_8
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == FAST_PWM_9
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == FAST_PWM_10
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_Freq_ICR1
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_Freq_OCR1A
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_ICR1
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == PHASE_PWM_OCR1A
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == CTC_ICR1
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == RESERVED
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == FAST_PWM_OCR1A
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif    WAVEFORM_Timer1 == FAST_PWM_OCR1A
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#endif

	// Compare Match Mode For Timer1A
	#if    COMPARE_MATCH_Timer1A == NORMAL_PORT
		  CLR_BIT(TCCR1A,COM1A0);
		  CLR_BIT(TCCR1A,COM1A1);
	#elif  COMPARE_MATCH_Timer1A == TOG_OC
		  CLR_BIT(TCCR1A,COM1A0);
		  CLR_BIT(TCCR1A,COM1A1);
	#elif  COMPARE_MATCH_Timer1A == CLR_OC
		  CLR_BIT(TCCR1A,COM1A0);
		  CLR_BIT(TCCR1A,COM1A1);
	#elif  COMPARE_MATCH_Timer1A == SET_OC
		  CLR_BIT(TCCR1A,COM1A0);
		  CLR_BIT(TCCR1A,COM1A1);
	#endif

	// CompBre Match Mode For Timer1B
	#if    COMPBRE_MBTCH_Timer1B == NORMBL_PORT
		   CLR_BIT(TCCR1A,COM1B0);
		   CLR_BIT(TCCR1A,COM1B1);
	#elif  COMPBRE_MBTCH_Timer1B == TOG_OC
		   CLR_BIT(TCCR1A,COM1B0);
		   CLR_BIT(TCCR1A,COM1B1);
	#elif  COMPBRE_MBTCH_Timer1B == CLR_OC
		   CLR_BIT(TCCR1A,COM1B0);
		   CLR_BIT(TCCR1A,COM1B1);
	#elif  COMPBRE_MBTCH_Timer1B == SET_OC
		   CLR_BIT(TCCR1A,COM1B0);
		   CLR_BIT(TCCR1A,COM1B1);
	#endif


}

void Timer2_init()
{
	// Selecting Mode for Timer 2
	#if WAVEFORM_Timer2 == NORMAL_MODE
		  CLR_BIT(TCCR2,WGM20);
		  CLR_BIT(TCCR2,WGM21);
	#elif WAVEFORM_Timer2 == PHASE_PWM
		  SET_BIT(TCCR2,WGM20);
		  CLR_BIT(TCCR2,WGM21);
		  CLR_BIT(TCCR2,FOC2);
	#elif WAVEFORM_Timer2 == CTC
		  CLR_BIT(TCCR2,WGM20);
		  SET_BIT(TCCR2,WGM21);
		  // Load Compare Match Register with Compare Value
		  	  OCR2 = Tim2_CTC ;
	#elif WAVEFORM_Timer2 == FAST_PWM
		  SET_BIT(TCCR2,WGM20);
		  SET_BIT(TCCR2,WGM21);
		  CLR_BIT(TCCR2,FOC2);
	#endif

	// Select Prescaler for Timer 2
	#if   CLK_SEL_Timer2 == NO_CLK
		  CLR_BIT(TCCR2,CS20);
		  CLR_BIT(TCCR2,CS21);
		  CLR_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == NO_PRE
		  SET_BIT(TCCR2,CS20);
		  CLR_BIT(TCCR2,CS21);
		  CLR_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == PRE_8
		  CLR_BIT(TCCR2,CS20);
		  SET_BIT(TCCR2,CS21);
		  CLR_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == PRE_64
		  SET_BIT(TCCR2,CS20);
		  SET_BIT(TCCR2,CS21);
		  CLR_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == PRE_256
		  CLR_BIT(TCCR2,CS20);
		  CLR_BIT(TCCR2,CS21);
		  SET_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == PRE_1024
		  SET_BIT(TCCR2,CS20);
		  CLR_BIT(TCCR2,CS21);
		  SET_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == EX_CLK_FALL_EDGE
		  CLR_BIT(TCCR2,CS20);
		  SET_BIT(TCCR2,CS21);
		  SET_BIT(TCCR2,CS22);
	#elif CLK_SEL_Timer2 == EX_CLK_RISE_EDGE
		  SET_BIT(TCCR2,CS20);
		  SET_BIT(TCCR2,CS21);
		  SET_BIT(TCCR2,CS22);
	#endif

	// Compare Match Mode
	#if    COMPARE_MATCH_Timer2 == NORMAL_PORT
		  CLR_BIT(TCCR2,COM20);
		  CLR_BIT(TCCR2,COM21);
	#elif  COMPARE_MATCH_Timer2 == TOG_OC
		  SET_BIT(TCCR2,COM20);
		  CLR_BIT(TCCR2,COM21);
		  // Configure Pin OC2 as Output
		  SET_BIT(DDRD,OC2);
	#elif  COMPARE_MATCH_Timer2 == CLR_OC
		  CLR_BIT(TCCR2,COM20);
		  SET_BIT(TCCR2,COM21);
		  // Configure Pin OC2 as Output
		  SET_BIT(DDRD,OC2);
	#elif  COMPARE_MATCH_Timer2 == SET_OC
		  SET_BIT(TCCR2,COM20);
		  SET_BIT(TCCR2,COM21);
		  // Configure Pin OC2 as Output
		  SET_BIT(DDRD,OC2);
	#endif
	// Initializing Timer2
	  TCNT2 = 0;

	// Enable Timer2 Overflow Interrupt
	#if Tim2_OV_INT == DISABLE
	  CLR_BIT(TIMSK,TOIE2);
	#else
	  SET_BIT(TIMSK,TOIE2);
	#endif

	// Disable Timer2 Overflow Interrupt
	#if Tim2_CMP_INT == DISABLE
	  CLR_BIT(TIMSK,OCIE2);
	#else
	  SET_BIT(TIMSK,OCIE2);
	#endif
}

// Timer Check Section
unit8 CheckTimer0()
{
   // Variable used to store Value of Timer
   unit8 counter = 0;
   // Wait until Timer Overflow occurs
   while(GET_BIT(TIFR,TOV0) == 0);
   // Clear Timer Overflow flag by writing one to TOV0 Bit
   SET_BIT(TIFR,TOV0);
   // Counter used as indicator that overflow occurred
   counter = 1;
   return counter;
}

unit8 CheckTimer1()
{
	   unit8 counter = 0;
	   while(GET_BIT(TIFR,TOV1) == 0);
	   CLR_BIT(TIFR,TOV1);
	   counter = 1;
	   return counter;
}

unit8 CheckTimer2()
{
	  // Variable used to store Value of Timer
	   unit8 counter = 0;
	   // Wait until Timer Overflow occurs
	   while(GET_BIT(TIFR,TOV2) == 0);
	   // Clear Timer Overflow flag by writing one to TOV0 Bit
	   SET_BIT(TIFR,TOV2);
	   // Counter used as indicator that overflow occurred
	   counter = 1;
	   return counter;
}

// Counter Value Section
unit8 Counter0(){
	unit8 counter = TCNT0;
	return counter;
}

unit16 Counter1(){
	unit16 counter = TCNT1;
	return counter;
}

unit8 Counter2(){
	unit8 counter = TCNT2;
	return counter;
}

// Interrupt Call Back function Section
void SetCallBackTimer0OVF(void (*ptr)())
{
	ptr2fun0OVF = ptr;
}

void SetCallBackTimer0CMP(void (*ptr)())
{
	ptr2fun0CMP = ptr;
}

void SetCallBackTimer1OVF(void (*ptr)()){
	ptr2fun1OVF = ptr;

}

void SetCallBackTimer1COMPA(void (*ptr)()){
	ptr2fun1CMPA = ptr;
}

void SetCallBackTimer1COMPB(void (*ptr)()){
	ptr2fun1CMPA = ptr;
}

void SetCallBackTimer2OVF(void (*ptr)())
{
	ptr2fun2OVF = ptr;
}

void SetCallBackTimer2CMP(void (*ptr)())
{
	ptr2fun2CMP = ptr;
}

// ISR Setting Section
ISR(TIMER0_OVF_vect)
{
	if(ptr2fun0OVF != 0) ptr2fun0OVF();
}

ISR(TIMER0_COMP_vect)
{
	if(ptr2fun0CMP != 0) ptr2fun0CMP();
}

ISR(TIMER1_OVF_vect)
{
	if(ptr2fun1OVF != 0) ptr2fun1OVF();
}

ISR(TIMER1_COMPA_vect)
{
	if(ptr2fun1CMPA != 0) ptr2fun1CMPA();
}

ISR(TIMER1_COMPB_vect)
{
	if(ptr2fun1CMPB != 0) ptr2fun1CMPB();
}

ISR(TIMER2_OVF_vect)
{
	if(ptr2fun2OVF != 0) ptr2fun2OVF();
}

ISR(TIMER2_COMP_vect)
{
	if(ptr2fun0CMP != 0) ptr2fun0CMP();
}

// PWM function

unit8 PWM_Write(channel_type channel,unit8 PWM)
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	unit8 x = 0;
	switch(Port)
	{
	case PORT_B:
		OCR0 = PWM;
		break;
	case PORT_D:

	switch(Pin)
		{
			case PIN_4:
				OCR1A = PWM;
				break;
			case PIN_5:
				OCR1B = PWM;
				break;
			case PIN_7:
				OCR2 = PWM;
				break;
			default:
				break;
		}
	break;
	default:
		break;
	}
	return x;
}
