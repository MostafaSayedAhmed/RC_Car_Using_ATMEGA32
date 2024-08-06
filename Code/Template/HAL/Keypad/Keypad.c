/*
 * Keypad.c
 *
 *  Created on: Sep 17, 2022
 *      Author: Mostafa Sayed
 */

#include "Keypad.h"

unit8 KeysTable [4][4] ={
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'C','0','=','+'}
};

static unit8 COL_Check()
{
	unit8 checker = NO_KEY ;
	if(!DIO_Read(C0)) checker = 0;
	else if (!DIO_Read(C1)) checker = 1;
	else if (!DIO_Read(C2)) checker = 2;
	else if (!DIO_Read(C3)) checker = 3;
	return checker;
}

unit8 Keypad_Read()
{
   unit8 key = NO_KEY;
   unit8 value = NO_KEY ;

   DIO_Write(R0,LOW);
   DIO_Write(R1,HIGH);
   DIO_Write(R2,HIGH);
   DIO_Write(R3,HIGH);
   key = COL_Check();
   if(key != NO_KEY){
	   value = KeysTable[0][key];
   }

   DIO_Write(R0,HIGH);
   DIO_Write(R1,LOW);
   DIO_Write(R2,HIGH);
   DIO_Write(R3,HIGH);
   key = COL_Check();
   if(key != NO_KEY){
	   value = KeysTable[1][key];
   }

   DIO_Write(R0,HIGH);
   DIO_Write(R1,HIGH);
   DIO_Write(R2,LOW);
   DIO_Write(R3,HIGH);
   key = COL_Check();
   if(key != NO_KEY){
	   value = KeysTable[2][key];
   }

   DIO_Write(R0,HIGH);
   DIO_Write(R1,HIGH);
   DIO_Write(R2,HIGH);
   DIO_Write(R3,LOW);
   key = COL_Check();
   if(key != NO_KEY){
	   value = KeysTable[3][key];
   }

   return value;
}
