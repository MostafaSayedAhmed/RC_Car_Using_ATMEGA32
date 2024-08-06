/*
 * 7Seg.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Mostafa Sayed
 */
#include "7Seg.h"

void Seg7_init()
{
	if(seg7Port == PORT_A)
	{
		for(int i=0 ; i<7;i++) SET_BIT(DDRA,i);
	}
	else if(seg7Port == PORT_B)
	{
		for(int i=0 ; i<7;i++) SET_BIT(DDRB,i);
	}
	else if(seg7Port == PORT_C)
		{
		for(int i=0 ; i<7;i++) SET_BIT(DDRC,i);
		}
	else if(seg7Port == PORT_D)
		{
		for(int i=0 ; i<7;i++) SET_BIT(DDRD,i);
		}

}

void Seg7_Write(unit8 Num)
{
	GET_BIT(Num,0) ? DIO_Write(a,HIGH) : DIO_Write(a,LOW);
	GET_BIT(Num,1) ? DIO_Write(b,HIGH) : DIO_Write(b,LOW);
	GET_BIT(Num,2) ? DIO_Write(c,HIGH) : DIO_Write(c,LOW);
	GET_BIT(Num,3) ? DIO_Write(d,HIGH) : DIO_Write(d,LOW);
	GET_BIT(Num,4) ? DIO_Write(e,HIGH) : DIO_Write(e,LOW);
	GET_BIT(Num,5) ? DIO_Write(f,HIGH) : DIO_Write(f,LOW);
	GET_BIT(Num,6) ? DIO_Write(g,HIGH) : DIO_Write(g,LOW);
	GET_BIT(Num,7) ? DIO_Write(EN,HIGH) : DIO_Write(EN,LOW);
}
