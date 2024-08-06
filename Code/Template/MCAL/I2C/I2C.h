/*
 * I2C.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_

#include "I2C_config.h"
#include <avr/io.h>
#include "../../BIT_Math.h"
#include "../../Units.h"

////////////////////////// Every function is explained in details at its section ///////////////////////////

// I2C_init is used to initialize Register according to I2C_config.h
void I2C_init(void);

// Master Mode
unit8 I2C_Start(unit8 address);
unit8 I2C_RepStart(unit8 address);
unit8 I2C_Write(unit8 data);
unit8 I2C_Read_Ack (void);
unit8 I2C_Read_Nack (void);
void I2C_Stop(void);

// Slave Mode
void I2C_SlaveInit(unit8 slaveAddress);
unit8 I2C_Slave_Listen(void);
unit8 I2C_Slave_Transmit(unit8 data);
unit8 I2C_Slave_Receive(void);

// Status Determining
#define CASE_0                          0
#define CASE_1                          1
#define CASE_2                          2
#define CASE_3                          3

// Status Value in Register

	// Master Transmitter Mode
#define	START_TX                     0x08
#define	REP_START                    0x10
#define	SLA_W_TX_ACK_RX              0x18
#define	SLA_W_TX_NACK_RX             0x20
#define	DATA_TX_ACK_RX               0x28
#define	DATA_TX_NACK_RX              0x30
	// Master Receiver Mode
#define	SLA_R_TX_ACK_RX              0x40
#define	SLA_R_TX_NACK_RX             0x48
#define	DATA_RX_ACK_RX               0x50
#define	DATA_RX_NACK_RX              0x58
	// Slave Receiver Mode
#define	SLA_W_RX_ACK_RX              0x60
#define SLA_W_RX_ACK_RX_LOSS         0x68
#define	GENERAL_CALL                 0x70
#define	GENERAL_CALL_LOSS            0x78
#define	SLA_W_RX_DATA_RX_ACK         0x80
#define	SLA_W_RX_DATA_RX_NACK        0x88
#define	GENERAL_CALL_DATA_RX_ACK     0x90
#define	GENERAL_CALL_DATA_RX_NACK    0x98
	// Slave Transmitter Mode
#define	SLA_R_RX_ACK_RX              0xA8
#define	SLA_R_RX_ACK_RX_LOSS         0xB0
#define	DATA_TWDR_ACK_RX             0xB8
#define	DATA_TWDR_ACK_RX_LOSS        0xC0
#define	LAST_BYTE_ACK_RX             0xC8
	// Others
#define	LOSS_MASTER                  0x38
#define	STOP_SLAVE                   0xA0
#define	IRR_INFO                     0xF8
#define	BUS_ERROR                    0x00

// General Call Address
#define GEN_ADR                      0x00

/*
 * Research more about :
 * 1- open drain (or open collector in case of BJT)
 * 2- Arbitration Process
 * 3- Slew Rate Control
 * 4- Spike Filter
 *
 * Important Notes :
 * Address is 7 bit long so it can connect 128 Devices
 * Require Pull-Up Resistor for two lines (SDA and SCL) or enable pull up using GPIO Driver in some machines
 * data size transmitted is 8 bit with 1 READ/WRITE Control bit (1 -> Read , 0 -> Write)
 * ACK bit is ninth bit and it is low at 9th SCL Cycle
 * Address is transmitted where MSB is first till LSB (Address 0000 000 is General Call)
 * General Call send data to all connected devices at once (Write is allowed , Read is Prohibited)
 * Address 1111 xxx is reserved for future use
 * Spike Suppression Remove Spikes less than 50 ns
 * TWBR : Control SCL Period using Prescaler bits in TWSR
 * CPU clock of slave must be at least 16 times higher than SCL Frequency (refer to page 173 in datasheet)
 * TWDR : Contain Address and Data Bytes
 * ACK can be determined using TWSR
 * TWAR : Contain address of the device (respond to General Call if TWGCE is enabled only)
 * TWDR : TWI Data Register , In TX contain next byte to be transmitted , In RX contain Received Byte
 * TWAR : Contain 7 Bit address of the slave and General call Enable bit
 * TWAR contain Address in Most significant 7 bits
 */

#endif /* MCAL_I2C_I2C_H_ */
