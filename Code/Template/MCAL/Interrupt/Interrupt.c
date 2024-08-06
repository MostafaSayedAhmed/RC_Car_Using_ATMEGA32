/*
 * Interrupt.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Mostafa Sayed
 */


#include "Interrupt.h"
#include <avr/io.h>

static void (*p2fun_INT0)() = 0 ;
static void (*p2fun_INT1)() = 0 ;
static void (*p2fun_INT2)() = 0 ;

void Interrupt_Enable()
{
	SET_BIT(SREG,7);
     #if INT_0 == ENABLE
	    SET_BIT(GICR,INT0);
       #if INT0_CONTROL == LOW_LEVEL
	      CLR_BIT(MCUCR,ISC00);
	      CLR_BIT(MCUCR,ISC01);
       #elif INT0_CONTROL == ANY_CHANGE
	      SET_BIT(MCUCR,ISC00);
	      CLR_BIT(MCUCR,ISC01);
       #elif INT0_CONTROL == FALL_EDGE
	      CLR_BIT(MCUCR,ISC00);
	      SET_BIT(MCUCR,ISC01);
       #elif INT0_CONTROL == RISE_EDGE
          SET_BIT(MCUCR,ISC00);
	      SET_BIT(MCUCR,ISC01);
       #endif
      #else
	      CLR_BIT(GICR,INT0);
     #endif

       #if INT_1 == ENABLE
         SET_BIT(GICR,INT1);
        #if INT1_CONTROL == LOW_LEVEL
          CLR_BIT(MCUCR,ISC10);
          CLR_BIT(MCUCR,ISC11);
        #elif INT1_CONTROL == ANY_CHANGE
            SET_BIT(MCUCR,ISC10);
            CLR_BIT(MCUCR,ISC11);
        #elif INT1_CONTROL == FALL_EDGE
            CLR_BIT(MCUCR,ISC10);
            SET_BIT(MCUCR,ISC11);
        #elif INT1_CONTROL == RISE_EDGE
            SET_BIT(MCUCR,ISC10);
            SET_BIT(MCUCR,ISC11);
       #endif
       #else
           CLR_BIT(GICR,INT1);
     #endif

       #if INT_2 == ENABLE
          SET_BIT(GICR,INT2);
        #if INT2_CONTROL == FALL_EDGE_INT2
           CLR_BIT(MCUCSR,ISC2);
        #elif INT2_CONTROL == RISE_EDGE_INT2
           SET_BIT(MCUCSR,ISC2);
        #endif
       #else
           CLR_BIT(GICR,INT2);
       #endif


}

void SetCallbackFunction_INT0(void (*fun)()){
	p2fun_INT0 = fun;
}

void SetCallbackFunction_INT1(void (*fun)()){
	p2fun_INT1 = fun;
}

void SetCallbackFunction_INT2(void (*fun)()){
	p2fun_INT2 = fun;
}

ISR(INT0_vect)
{
	if(p2fun_INT0 != 0) p2fun_INT0();


}
ISR(INT1_vect)
{
	if(p2fun_INT1 != 0) p2fun_INT1();

}
ISR(INT2_vect)
{
	if(p2fun_INT2 != 0) p2fun_INT2();
}
