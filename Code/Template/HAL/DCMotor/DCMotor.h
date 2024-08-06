

#ifndef _DC_MOTOR_H_
#define _DC_MOTOR_H_

#include "../../Units.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/Timer.h"

/* DC Motor Initiation */
void MotorInit    (void);

/* DC Motor Move Function */
unit8 MoveForward (unit8 speed);
unit8 MoveBackward(unit8 speed);
unit8 MoveRight   (void);
unit8 MoveLeft    (void);
unit8 Stop        (void);

/* DC Motor Pins */

/**
 * PB3 : Port B - Pin 3 -- Timer 0
 * PD4 : Port D - Pin 4 -- Timer 1A
 * PD5 : Port D - Pin 5 -- Timer 1B
 * PD7 : Port D - Pin 7 -- Timer 2
 */

// Assume PB3 and PD7

#define RIGHTWHEELS_PIN   PORTD_7
#define LEFTWHEELS_PIN    PORTB_3


#endif
