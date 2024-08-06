/* Documentation Section */
/**
*****************************************************************************
* @file          : main.c
* @version       : 1.0.0
* @author        : Author: Mostafa Sayed
* @brief         : Remote Control Vehicle
* @details       :
* @date          : Created on: Apr 11, 2023
*****************************************************************************
**
/* ******************** Include Section Start ****************************** */

#include <avr/io.h>
#include <util/delay.h>
#include "MCAL/Timer/Timer.h"
#include "HAL/DCMotor/DCMotor.h"
#include "MCAL/USART/USART.h"


/* ******************** Include Section End ******************************** */

/* ******************** Definition Section Start *************************** */

#define F_CPU 16000000UL

#define FORWARD   'A'
#define BACKWARD  'B'
#define RIGHT     'C'
#define LEFT      'D'
#define STOP      'E'

/* ******************** Definition Section End ***************************** */

/* ******************* Global Variables Section Start ********************** */
unit8 USART_Receiver = 0;
/* ******************** Global Variables Section End *********************** */

/* ******************** Global Declaration Section Start ******************* */
// Section to Declare Global Variables
/* ******************** Global Declaration Section End ********************* */

/* ******************** Sub-Program Declaration Section Start ************** */

void USART_RX_ISR(void)
{
	USART_Receiver = Rx_Interrupt();
}
/* ******************** Sub-Program Declaration Section End **************** */

/* Main Program Section */
/* -------------------- */

void main(void)
{
	USART_init();
	MotorInit();

	SetUSARTReceiveCallBack(&USART_RX_ISR);
	while(1)
	{
      if(USART_Receiver == 'A')
      MoveForward(128);

      else if(USART_Receiver == 'B')
    	  MoveBackward(255);

      else if(USART_Receiver == 'C')
    	  MoveRight();

      else if(USART_Receiver == 'D')
    	  MoveLeft();
      else
    	  Stop();

	}

   /* Write your Application here */
}

/* ********************* Sub-Program Section Start ******************** */

/* ********************* Sub-Program Section End ********************** */

/**
*****************************************************************************
   User               Date                      Brief
*****************************************************************************
   Mostafa Sayed      July 30, 2023             Project Creation

**/

/**
 * Features:
 * 		Motors Movements 	 : DC Motors
 * 		Object Avoidance 	 : Ultra-sonic Sensor HC-SR04 and Servo-Motor
 * 		Line Follower		 : IR Sensor
 * 		Blue-tooth Interface : UART Module
 *
 *
 *
**/

