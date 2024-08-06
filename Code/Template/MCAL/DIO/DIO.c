#include "DIO.h"

// DIO_SetPinDir is function that set a pin direction depending on parameter and return error indicator
unit8 DIO_SetPinDir(channel_type channel,DDR_Direction direction)
{
	unit8 Error = 0;
	if(channel >= PORTA_0 &&  channel <= PORTA_7 )
	{
		if(direction == OUTPUT )
		{
			SET_BIT(DDRA,(channel - PORTA_0));
		}
		else if (direction == INPUT)
		{
			CLR_BIT(DDRA,(channel - PORTA_0));
			CLR_BIT(PORTA,(channel - PORTA_0));
		}
		else if (direction == INPUT_PULLUP)
		{
			CLR_BIT(DDRA,(channel - PORTA_0));
			SET_BIT(PORTA,(channel - PORTA_0));
		}
		else
		{
			Error = 1;
		}

	}
	else if(channel >= PORTB_0 &&  channel <= PORTB_7 )
	{
		if(direction == OUTPUT )
		{
			SET_BIT(DDRB,(channel - PORTB_0));
		}
		else if (direction == INPUT)
		{
			CLR_BIT(DDRB,(channel - PORTB_0));
			CLR_BIT(PORTB,(channel - PORTB_0));
		}
		else if (direction == INPUT_PULLUP)
		{
			CLR_BIT(DDRB,(channel - PORTB_0));
			SET_BIT(PORTB,(channel - PORTB_0));
		}
		else
		{
			Error = 1;
		}
	}
	else if(channel >= PORTC_0 &&  channel <= PORTC_7 )
	{
		if(direction == OUTPUT )
		{
			SET_BIT(DDRC,(channel - PORTC_0));
		}
		else if (direction == INPUT)
		{
			CLR_BIT(DDRC,(channel - PORTC_0));
			CLR_BIT(PORTC,(channel - PORTC_0));
		}
		else if (direction == INPUT_PULLUP)
		{
			CLR_BIT(DDRC,(channel - PORTC_0));
			SET_BIT(PORTC,(channel - PORTC_0));
		}
		else
		{
			Error = 1;
		}
	}
	else if(channel >= PORTD_0 &&  channel <= PORTD_7 )
	{
		if(direction == OUTPUT )
		{
			SET_BIT(DDRD,(channel - PORTD_0));
		}
		else if (direction == INPUT)
		{
			CLR_BIT(DDRD,(channel - PORTD_0));
			CLR_BIT(PORTD,(channel - PORTD_0));
		}
		else if (direction == INPUT_PULLUP)
		{
			CLR_BIT(DDRD,(channel - PORTD_0));
			SET_BIT(PORTD,(channel - PORTD_0));
		}
		else
		{
			Error = 1;
		}
	}
	else
	{
		Error = 1;
	}

	return Error;
}
// Function used to write on Digital Output Pin either HIGH or LOW
void DIO_Write(channel_type channel, DIO_Level level )
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	if(Port == PORT_A)
	{
	if(level == HIGH) SET_BIT(PORTA,Pin);
	else CLR_BIT(PORTA,Pin);
	}
	if(Port == PORT_B)
	{
	if(level == HIGH) SET_BIT(PORTB,Pin);
	else CLR_BIT(PORTB,Pin);
	}
	if(Port == PORT_C)
	{
	if(level == HIGH) SET_BIT(PORTC,Pin);
	else CLR_BIT(PORTC,Pin);
	}
	if(Port == PORT_D)
	{
	if(level == HIGH) SET_BIT(PORTD,Pin);
	else CLR_BIT(PORTD,Pin);
	}
}

// Function used to Read from input pin
DIO_Level DIO_Read(channel_type channel)
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	if      (Port == PORT_A)
	{
		if(GET_BIT(PINA,Pin) == 0) return LOW;
		else                        return HIGH;
	}

	else if (Port == PORT_B)
	{
		if(GET_BIT(PINB,Pin) == 0)  return LOW;
		else                        return HIGH;
	}
	else if (Port == PORT_C)
	{
		if(GET_BIT(PINC,Pin) == 0) return LOW;
		else                        return HIGH;
	}
	else
	{
		if(GET_BIT(PIND,Pin) == 0) return LOW;
		else                        return HIGH;
	}
}

// Function used to toggle Digital Output Pin
void DIO_Flip(channel_type channel)
{
	DIO_Port Port = channel/8;
	DIO_Pin Pin = channel%8;
	if      (Port == PORT_A)
	{
		TOG_BIT(PORTA,Pin);
	}

	else if (Port == PORT_B)
	{
		TOG_BIT(PORTB,Pin);
	}
	else if (Port == PORT_C)
	{
		TOG_BIT(PORTC,Pin);
	}
	else
	{
		TOG_BIT(PORTD,Pin);
	}
}
