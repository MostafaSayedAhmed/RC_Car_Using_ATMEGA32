/*
 * I2C.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Mostafa Sayed
 *      with assist of : https://www.electronicwings.com/avr-atmega/atmega1632-i2c
 */
#include "I2C.h"
#include <util/delay.h>

// ***************************************** I2C *****************************************************
void I2C_init(void){

// Determining Bit Rate
	TWBR = TWBR_VALUE;
#if PRE_VAL == PRE_1
  CLR_BIT(TWSR,TWPS0);
  CLR_BIT(TWSR,TWPS1);
#elif PRE_VAL == PRE_4
  SET_BIT(TWSR,TWPS0);
  CLR_BIT(TWSR,TWPS1);
#elif PRE_VAL == PRE_16
  CLR_BIT(TWSR,TWPS0);
  SET_BIT(TWSR,TWPS1);
#elif PRE_VAL == PRE_64
  CLR_BIT(TWSR,TWPS0);
  SET_BIT(TWSR,TWPS1);
#endif

}

// ************************************ Master Mode **************************************************

// Start Function : Write to Device
unit8 I2C_Start(unit8 address){
	// Variable used to check status
    unit8 status = TWSR & 0xF8 ;

	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWSTA);
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;
	if(status != START_TX ) return CASE_0; // START fail

	// Load TWDR with Slave Address and Write bit
	TWDR = address  ;

	// Re-updating TWCR
    STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;
	if(status == SLA_W_TX_ACK_RX )           return CASE_1;       // ACK Received
	else if (status == SLA_W_TX_NACK_RX )    return CASE_2;       // NACK Received
	else                                     return CASE_3;     // Process Fail

}

// Repeated Start Function : Read from Device
unit8 I2C_RepStart(unit8 address){

	// Variable used to check status
    unit8 status = TWSR & 0xF8 ;

	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWSTA);
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;
	if(status != REP_START ) return CASE_0;     // START fail

	// Load TWDR with Slave Address and Write bit
	TWDR = address ;

	// Re-updating TWCR
    STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;
	if(status == SLA_R_TX_ACK_RX )           return CASE_1;   // ACK Received
	else if (status == SLA_R_TX_NACK_RX )    return CASE_2;   // NACK Received
	else                                     return CASE_3;   // Process Fail

}

// Write data : Write to Device after START
unit8 I2C_Write(unit8 data){
	// Status variable to check status
	unit8 status;

	// Load Data to Register
	TWDR = data;

	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;

	if(status == DATA_TX_ACK_RX )            return CASE_0;    // ACK Received
	else if(status == DATA_TX_NACK_RX )      return CASE_1;    // NACK Received
	else                                     return CASE_2;    // Process Fail


}

// Read data  : Read from Slave after Repeated START

// Read_Ack   : when master want to read data and want to continue reading data
unit8 I2C_Read_Ack (void){
	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	SET_BIT(STA_TEMP,TWEA);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Return Data
	return TWDR;
}

// Read_Nack   : when master want to read data and want to stop reading data
unit8 I2C_Read_Nack (void){
	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Return Data
	return TWDR;
}

// Stop : cease communication
void I2C_Stop(void){
	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWSTO);
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);
}

// *********************************************************************************************************

// ******************************** Notes for Writing Programs using Master Mode ***************************

/*
 * Master in Writing Operation :
 * Initialize I2C.
 * Generate START condition.
 * Send the Slave device to write address (SLA+W) and check for acknowledgment.
 * Write memory location addresses for memory devices to which we want to write.
 * Write data till the last byte.
 * Generate a STOP condition.
 *
 * Master in Reading Operation :
 * Initialize I2C.
 * Generate START condition.
 * Write device Write address (SLA+W) and check for acknowledgment.
 * Write a memory location address for memory devices.
 * Generate REPEATED START condition.
 * Read data and return acknowledgment.
 * Return Not acknowledgment for the last byte.
 * Generate a STOP condition.
 *
 */

// *********************************************************************************************************

//**************************************** Slave Mode ******************************************************

// Initialize Slave with Address
void I2C_SlaveInit(unit8 slaveAddress){
	// Load TWAR with slave address
	TWAR = slaveAddress | GEN_CALL;

	// Initialize TWCR with values
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	SET_BIT(STA_TEMP,TWEA);
	TWCR = STA_TEMP;
}

// Slave must always listen until receive start from Master
unit8 I2C_Slave_Listen(void){
    while(1)
     {
    // status variable to check status
	unit8 status;

	// wait till TWINT is set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check status
	status=TWSR & 0xF8;

	if(status == SLA_W_RX_ACK_RX ||status == SLA_W_RX_ACK_RX_LOSS)  return CASE_0; // ACK Received in Case SLA + W
	if(status == SLA_R_RX_ACK_RX ||status == SLA_R_RX_ACK_RX_LOSS)  return CASE_1; // ACK Received in Case SLA + R
	if(status == GENERAL_CALL ||status == GENERAL_CALL_LOSS)	    return CASE_2; // General Call received
	else
	continue;			/* Else continue */
     }
}

// Slave transmit to master
unit8 I2C_Slave_Transmit(unit8 data){
	// Status variable to check status
	unit8 status;

	// Load Data to Register
	TWDR = data;

	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	SET_BIT(STA_TEMP,TWEA);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;

	// STOP or Repeated Start is received clear interrupt flag
	if(status == STOP_SLAVE){
		SET_BIT(TWCR,TWINT);
		return -1;
	}
	// Data is transmitted and ACK is received
	else if (status == DATA_TWDR_ACK_RX)         return CASE_0;

	// Data is transmitted and NACK is received
	else if (status == DATA_TWDR_ACK_RX_LOSS )   return -2;

    // Last byte transmitted and ACK is received
	else if (status == LAST_BYTE_ACK_RX )        return -3;

	else                                         return -4;
}

// Slave receive from master
unit8 I2C_Slave_Receive(void)
{
	// Status variable to check status
	unit8 status;

	// Load TWCR To send Start Bit
	unsigned char STA_TEMP = 0;
	SET_BIT(STA_TEMP,TWINT);
	SET_BIT(STA_TEMP,TWEN);
	SET_BIT(STA_TEMP,TWEA);
	TWCR = STA_TEMP;

	// Wait till INT Flag is Set
	while(GET_BIT(TWCR,TWINT) == 0);

	// Check Status
	status = TWSR & 0xF8 ;

	// Data Received and ACK Received
    if(status == SLA_W_RX_DATA_RX_ACK || status == GENERAL_CALL_DATA_RX_ACK)
    return TWDR;

    // Data Received and NACK returned & switched to not addressed slave mode
    if(status == SLA_W_RX_DATA_RX_NACK || status == GENERAL_CALL_DATA_RX_NACK)
    return TWDR;

    // Stop or Repeated Start is Received
    if(status == STOP_SLAVE)
     {
	SET_BIT(TWCR,TWINT);
	return -1;
     }
    else return -2;
}

// **********************************************************************************************************

// ******************************** Notes for Writing Programs using Slave Mode *****************************

/*
 * Slave in Reading Operation :
 * Initialize I2C with slave device address.
 * Listen to bus for get addressed by master.
 * While addressed with SLA+W by master device, receive data from master device.
 * Return acknowledgment after each byte received.
 * Clear interrupt flag after REPEATED START/STOP received.
 *
 * Slave in Writing Operation :
 * Initialize I2C with slave device address.
 * listen to bus for get addressed by master.
 * While addressed with SLA+R by master device, transmit data to master device.
 * Transmit data till NACK/REPEATED START/STOP receive from master.
 * Clear interrupt flag after NACK/REPEATED START/STOP received
 *
 */

// *********************************************************************************************************
