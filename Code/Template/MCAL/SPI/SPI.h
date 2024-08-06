/*
 * SPI.h
 *
 *  Created on: Apr 16, 2023
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include <avr/io.h>
#include "../../BIT_Math.h"
#include "../../Units.h"
#include "../DIO/DIO_Types.h"
#include "SPI_config.h"

// Master Mode
void SPI_MasterInit(void);
void SPI_MasterTransmit(unit8 data);
unit8 SPI_MasterReceive(void);

// Slave Mode
void SPI_SlaveInit(void);
unit8 SPI_SlaveReceive(void);
void SPI_SlaveTransmit(unit8 data);

#define SS   PIN_4
#define MOSI PIN_5
#define MISO PIN_6
#define SCK  PIN_7


#endif /* MCAL_SPI_SPI_H_ */
