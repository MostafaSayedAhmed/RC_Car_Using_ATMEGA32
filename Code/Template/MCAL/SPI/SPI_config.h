/*
 * SPI_config.h
 *
 *  Created on: Apr 16, 2023
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_SPI_SPI_CONFIG_H_
#define MCAL_SPI_SPI_CONFIG_H_

// Prescaler Setting

#define PRE_VALUE

// Direction Specifying
#define MSB      0
#define LSB      1

#define DATA_ORD  MSB

// Setting Enable/Disable
#define DIS      0
#define EN       1

// Selecting Clock Polarity
#define RIS_FAL   0
#define FAL_RIS   1

#define CLK_POL RIS_FAL

// Clock Phase
#define LEAD      0
#define TRAIL     1

#define SAMPLE    LEAD

// Clock Rate SCK = (fosc*2(^SPI2X))/4^(SPR)
#define POWER_1        0
#define POWER_2        1
#define POWER_3        2
#define POWER_4        3

#define SPR_POWER     POWER_1

#define X2_SPEED      DIS
// Interrupt Setting
#define INT      DIS

/*
 * Notes:
 * To ensure proper operation of SPI , SCK = F_CPU/4 at least
 *   SPCR : SPI Control Register
 * SPIE : Enable Interrupt when set if it is set and i bit in SREG
 * SPE  : Enable SPI operation must be set during operation of SPI
 * DORD : Determine Data Order 1 -> LSB First , 0 -> MSB First
 * MSTR : Select Master and Slave mode 1 -> Master , 0 -> Slave
 * CPOL : Select Clock Polarity 0 -> Rising to Falling , 1 -> Falling to Rising
 * CPHA : Select Phase for Sampling 0 -> Lead , 1 -> Trail
 * SPR1,SPR0 : Set SCK Speed
 *   SPRS : SPI Status Register
 * SPIF : Interrupt Flag set when Transmission/Reception is completed
 * WCOL : Write Collision Flag  1 -> SPDR is Written during Transfer cleared by first reading
 * SPI2X : Double clock Speed
 *    SPDR : SPI Data Register
 */
#endif /* MCAL_SPI_SPI_CONFIG_H_ */
