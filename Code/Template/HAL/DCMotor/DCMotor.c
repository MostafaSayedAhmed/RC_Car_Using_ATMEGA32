
#include "DCMotor.h"

void MotorInit    (void)
{
	unit8 Error;
	DIO_SetPinDir(RIGHTWHEELS_PIN, OUTPUT);
	DIO_SetPinDir(LEFTWHEELS_PIN, OUTPUT);
	Timer0_init();
	Timer2_init();

	DIO_SetPinDir(PORTA_0,OUTPUT);
	DIO_SetPinDir(PORTA_1,OUTPUT);
	DIO_SetPinDir(PORTA_2,OUTPUT);
	DIO_SetPinDir(PORTA_3,OUTPUT);

	DIO_SetPinDir(PORTC_0,OUTPUT);
	DIO_SetPinDir(PORTC_1,OUTPUT);
	DIO_SetPinDir(PORTC_2,OUTPUT);
	DIO_SetPinDir(PORTC_3,OUTPUT);
}

unit8 MoveForward (unit8 speed)
{
	// Left Direction
	DIO_Write(PORTA_0,LOW);


	// Right Direction
	DIO_Write(PORTC_0,LOW);


	PWM_Write(RIGHTWHEELS_PIN,speed);
	PWM_Write(LEFTWHEELS_PIN,speed);
}

unit8 MoveBackward(unit8 speed){
	// Left Direction
	DIO_Write(PORTA_0,HIGH);


	// Right Direction
	DIO_Write(PORTC_0,HIGH);


	PWM_Write(RIGHTWHEELS_PIN,255 - speed);
	PWM_Write(LEFTWHEELS_PIN,255 - speed);
}

unit8 MoveRight   (void)
{
	// Left Direction
	DIO_Write(PORTA_0,HIGH);


	// Right Direction
	DIO_Write(PORTC_0,LOW);


	PWM_Write(RIGHTWHEELS_PIN,255);
	PWM_Write(LEFTWHEELS_PIN,0);
}
unit8 MoveLeft    (void)
{
	// Left Direction
	DIO_Write(PORTA_0,LOW);


	// Right Direction
	DIO_Write(PORTC_0,HIGH);


	PWM_Write(RIGHTWHEELS_PIN,0);
	PWM_Write(LEFTWHEELS_PIN,255);
}


unit8 Stop        (void)
{
	// Left Direction
	DIO_Write(PORTA_0,LOW);


	// Right Direction
	DIO_Write(PORTC_0,LOW);


	PWM_Write(RIGHTWHEELS_PIN,0);
	PWM_Write(LEFTWHEELS_PIN,0);
}
