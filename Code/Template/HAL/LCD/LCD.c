/*
 * LCD.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Mostafa Sayed
 */
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include <util/delay.h>
#include "../../Units.h"

static void Trigger()
{
	  DIO_Write(E,HIGH);
	  _delay_ms(2);
	  DIO_Write(E,LOW);
	  _delay_us(20);
}

void LCD_init()
{
	//DIO_init();
	LCD_SendCMD(BIT4MODE);
	LCD_SendCMD(CURSOR_BLINK_ON);
	LCD_SendCMD(CURSOR_MOVE_RIGHT);
	LCD_SendCMD(CLEAR_DISPLAY);

}
void LCD_SendCMD(unit8 cmd)
{
	  DIO_Write(RS,LOW);
	  DIO_Write(RW,LOW);
	  GET_BIT(cmd,7) ? DIO_Write(D7,HIGH) : DIO_Write(D7,LOW);
	  GET_BIT(cmd,6) ? DIO_Write(D6,HIGH) : DIO_Write(D6,LOW);
	  GET_BIT(cmd,5) ? DIO_Write(D5,HIGH) : DIO_Write(D5,LOW);
	  GET_BIT(cmd,4) ? DIO_Write(D4,HIGH) : DIO_Write(D4,LOW);
	  Trigger();
	  GET_BIT(cmd,3) ? DIO_Write(D7,HIGH) : DIO_Write(D7,LOW);
	  GET_BIT(cmd,2) ? DIO_Write(D6,HIGH) : DIO_Write(D6,LOW);
	  GET_BIT(cmd,1) ? DIO_Write(D5,HIGH) : DIO_Write(D5,LOW);
	  GET_BIT(cmd,0) ? DIO_Write(D4,HIGH) : DIO_Write(D4,LOW);
	  Trigger();
	  _delay_us(20);
}
void LCD_SendData(unit8 data)
{
	  DIO_Write(RS,HIGH);
	  DIO_Write(RW,LOW);
	  GET_BIT(data,7) ? DIO_Write(D7,HIGH) : DIO_Write(D7,LOW);
	  GET_BIT(data,6) ? DIO_Write(D6,HIGH) : DIO_Write(D6,LOW);
	  GET_BIT(data,5) ? DIO_Write(D5,HIGH) : DIO_Write(D5,LOW);
	  GET_BIT(data,4) ? DIO_Write(D4,HIGH) : DIO_Write(D4,LOW);
	  Trigger();
	  GET_BIT(data,3) ? DIO_Write(D7,HIGH) : DIO_Write(D7,LOW);
	  GET_BIT(data,2) ? DIO_Write(D6,HIGH) : DIO_Write(D6,LOW);
	  GET_BIT(data,1) ? DIO_Write(D5,HIGH) : DIO_Write(D5,LOW);
	  GET_BIT(data,0) ? DIO_Write(D4,HIGH) : DIO_Write(D4,LOW);
	  Trigger();
	  _delay_us(20);
}

void LCD_SendString(char* data)
{
	for(;*data!='\0';data++) LCD_SendData(*data);
}
void LCD_SendStringxy(char* data,unit8 x,unit8 y)
{
	LCD_SendCMD(0x02); // Return Cursor to it's Original Position
	LCD_SendCMD(0x2c); // Set DL to 4-bit Mode and 2-line display Mode with 5x11 dot format display mode
	for(int i=0;i<cal(x,y);i++) LCD_SendCMD(0x14);
	LCD_SendString(data);

}

void LCD_SetCursor(unit8 x , unit8 y)
{
	LCD_SendCMD(0x02); // Return Cursor to it's Original Position
	LCD_SendCMD(0x2c); // Set DL to 4-bit Mode and 2-line display Mode with 5x11 dot format display mode
	for(int i=0;i<cal(x,y);i++) LCD_SendCMD(0x14);
}
