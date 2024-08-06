/*
 * DIO.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include <avr/io.h>
#include "DIO_Types.h"
#include "../../Units.h"
#include "../../BIT_Math.h"

unit8 DIO_SetPinDir(channel_type channel,DDR_Direction direction);
void DIO_Write(channel_type channel , DIO_Level Level );
DIO_Level DIO_Read(channel_type channel);
void DIO_Flip(channel_type channel);


#endif /* MCAL_DIO_DIO_H_ */
