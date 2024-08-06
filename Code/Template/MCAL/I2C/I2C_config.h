/*
 * I2C_config.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

// Bit Rate Calculation (Page 173) : SCL_Freq = CPU_ClK /(16 + 2*(TWBR)*4^TWPS)
// TWBR value from 0 to 255 (8 Bit Register)
#define TWBR_VALUE  0

// Prescaler value (TWPS)
#define PRE_1    0
#define PRE_4    1
#define PRE_16   2
#define PRE_64   3

#define PRE_VAL  PRE_4

/////////////////////////////////////////////// Unused Section /////////////////////////////////////////////
// Address As Slave
// Address from 1 to 128
#define SLAVE_ADR     1

// General Call Setting
#define DIS   0
#define EN    1

#define GEN_CALL EN

// Setting Acknowledgment
#define ACK      EN

// Setting Interrupt
#define INT_SETTING DIS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * TWBR : Two Wire Interface Bit Rate Register
 * used to determine bit rate according to equation in page 173
 *
 * TWCR : TWI Control Register
 * TWINT : flag indicate completion of process , require I-bit in SREG and TWIE in TWCR to enable interrupt
 * TWINT must be cleared by software after using data in TWDR
 * TWEA  : Enable Acknowledge Bit, 1 to generate ACK Bit 0 to virtually disconnect device temporarily
 * TWSTA : Start Condition Bit , 1 if master is desired, must be cleared by SW after transmission
 * TWSTO : Stop Condition Bit , 1 to Stop Transmission in Master , Cleared Automatically
 * TWWC : indicate collision (Attempting to write to Data Register while TWINT is HIGH)
 * TWEN : Enable TWI , 1 Enable TWI , 0 Disable TWI
 * TWIE : Enable Interrupt. Request is executed as long as TWINT is High
 *
 * TWSR : TWI Status Register
 * TWS (7 to 4 bit) indicate status of TWI
 * TWPS : Prescaler bits
 */
#endif /* MCAL_I2C_I2C_CONFIG_H_ */
