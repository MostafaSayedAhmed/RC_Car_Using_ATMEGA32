/*
 * USART_config.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_

#include "USART.h"

// Character Size
#define BIT_5 0
#define BIT_6 1
#define BIT_7 2
#define BIT_8 3
#define BIT_9 7

#define CHAR_SIZE BIT_8

// USART Mode Select
#define ASYNC 0
#define SYNC  1

#define MODE_SEL ASYNC

// Selecting Double or Single Speed (ASYNC Mode)
#define SINGLE_SPEED 0
#define DOUBLE_SPEED 1

#define SPEED SINGLE_SPEED

// Selecting Clock Polarity (SYNC Mode)


// Parity Mode
#define OFF   0
#define EVEN  2
#define ODD   3

#define PARITY OFF

// Stop Bit Mode
#define BIT_1   0
#define BIT_2   1

#define STOP_BIT BIT_1

//  Clock Polarity (Sync Mode only)
#define R_TX_F_RX 0
#define F_TX_R_RX 1

#define CLK_POL   F_TX_R_RX

// Interrupt Setting
#define DIS       0
#define EN        1

#define EMPTY_INT    DIS
#define TX_INT       DIS
#define RX_INT       EN
#define TX_EN        EN
#define RX_EN        EN
// Clock Speed

#define BAUD_RATE 9600

#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * (16UL/(1+SPEED))))) - 1)
#define BAUD_PRE_SYNC ((F_CPU/BAUD_RATE*2) - 1)

/*
 * Notes:
 * Status Bits need to be read first before reading Data Register
 * Four Mode of Operation : Normal Speed Async , Double Speed Async , Master Mode , Slave Mode
 * In Sync Mode : Fxcx < F_CPU / 4
 *
 */

#endif /* MCAL_USART_USART_CONFIG_H_ */
