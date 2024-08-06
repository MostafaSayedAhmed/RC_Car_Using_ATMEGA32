/*
 * SPI.c
 *
 *  Created on: Apr 16, 2023
 *      Author: Mostafa Sayed
 */

#include "SPI.h"

typedef enum{
	Master,
	Slave
}mode;
static void SPI_init(mode type){
	   // Configuring register SPCR
	   unit8 SPCR_temp = 0;
	   // Enable SPI Operation
	   SET_BIT(SPCR_temp,SPE);
	   // Setting Interrupt
	#if   INT == DIS
	   CLR_BIT(SPCR_temp,SPIE);
	#else
	   SET_BIT(SPCR_temp,SPIE);
	#endif
	   // Setting Data Direction
	#if DATA_ORD == MSB
	   CLR_BIT(SPCR_temp,DORD);
	#else
	   SET_BIT(SPCR_temp,DORD);
	#endif

	   // Selecting Master/Slave Mode
	   if(type == Master) SET_BIT(SPCR_temp,MSTR);
	   else               CLR_BIT(SPCR_temp,MSTR);

	  // Setting CLK Polarity
	#if CLK_POL == RIS_FAL
	   CLR_BIT(SPCR_temp,CPOL);
	#else
	   SET_BIT(SPCR_temp,CPOL);
	#endif

	   // Selecting Phase at which sample is taken
	#if   SAMPLE == LEAD
	   CLR_BIT(SPCR_temp,CPHA);
	#else
	   SET_BIT(SPCR_temp,CPHA);
	#endif

	   // Clock Speed Setting
	// Setting 4 Power
	#if   SPR_POWER == POWER_1
	   CLR_BIT(SPCR_temp,SPR0);
	   CLR_BIT(SPCR_temp,SPR1);
	#elif SPR_POWER == POWER_2
	   SET_BIT(SPCR_temp,SPR0);
	   CLR_BIT(SPCR_temp,SPR1);
	#elif SPR_POWER == POWER_3
	   CLR_BIT(SPCR_temp,SPR0);
	   SET_BIT(SPCR_temp,SPR1);
	#else SPR_POWER == POWER_4
	   SET_BIT(SPCR_temp,SPR0);
	   SET_BIT(SPCR_temp,SPR1);
	#endif
	// Setting Double Speed
	#if X2_SPEED == DIS
	   CLR_BIT(SPSR,SPI2X);
	#else
	   SET_BIT(SPSR,SPI2X);
	#endif

	// Loading The Value SPCR_temp to Register
	   SPCR = SPCR_temp;
}

// ********************************************** Master Mode *******************************************

void SPI_MasterInit(void){
   // Configure Port Pins Master Mode
   CLR_BIT(DDRB,SS);
   SET_BIT(DDRB,MOSI);
   CLR_BIT(DDRB,MISO);
   SET_BIT(DDRB,SCK);

   // Initializing according to configuration
   SPI_init(Master);

}

void SPI_MasterTransmit(unit8 data){
	// Load SPDR with data
	SPDR = data;

	// Wait till Transmission is finished
	while(GET_BIT(SPSR,SPIF) == 0);
}

unit8 SPI_MasterReceive(void){
	// Transmitting Garbage data
	SPDR = 0xAF;

	// Wait till Transmission is finished
	while(GET_BIT(SPSR,SPIF) == 0);

	return SPDR;
}

// *********************************************** Slave Mode ********************************************

// ********************************************* Slave Mode *********************************************
void SPI_SlaveInit(void){
   // Configure Port Pins Master Mode
   CLR_BIT(DDRB,SS);
   CLR_BIT(DDRB,MOSI);
   SET_BIT(DDRB,MISO);
   CLR_BIT(DDRB,SCK);

   // Initializing according to configuration
   SPI_init(Slave);

}


unit8 SPI_SlaveReceive(void){
	// Wait till Transmission is finished
	while(GET_BIT(SPSR,SPIF) == 0);

	// Return Data
	return SPDR;
}

void SPI_SlaveTransmit(unit8 data){
	// Load SPDR with data
	SPDR = data;

	// Wait till Transmission is finished
	while(GET_BIT(SPSR,SPIF) == 0);
}

// ******************************************************************************************************
