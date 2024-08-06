/*
 * USART.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Mostafa Sayed
 */
#include "USART.h"

void (*ptr_RXC) (void);
void (*ptr_TXC) (void);

void USART_init()
{
//
	unsigned char UCSRA_temp = 0;
	unsigned char UCSRB_temp = 0;
	unsigned char UCSRC_temp = 0;
// Selecting Baud rate Register
    CLR_BIT(UCSRC,URSEL);
	UBRRL = (unsigned char) BAUD_PRESCALE;
	UBRRH = (unsigned char) (BAUD_PRESCALE >> 8);

// Important Bits to Clear
	CLR_BIT(UCSRA_temp,DOR);
	CLR_BIT(UCSRA_temp,PE);
	CLR_BIT(UCSRA_temp,FE);

// Selecting UCSRC Register
	SET_BIT(UCSRC_temp,URSEL);

// Character Size
	#if   CHAR_SIZE ==  BIT_5
		CLR_BIT(UCSRC_temp,UCSZ0);
		CLR_BIT(UCSRC_temp,UCSZ1);
		CLR_BIT(UCSRB_temp,UCSZ2);
	#elif CHAR_SIZE == 	BIT_6
		SET_BIT(UCSRC_temp,UCSZ0);
		CLR_BIT(UCSRC_temp,UCSZ1);
		CLR_BIT(UCSRB_temp,UCSZ2);
	#elif CHAR_SIZE == 	BIT_7
		CLR_BIT(UCSRC_temp,UCSZ0);
		SET_BIT(UCSRC_temp,UCSZ1);
		CLR_BIT(UCSRB_temp,UCSZ2);
	#elif CHAR_SIZE == 	BIT_8
		SET_BIT(UCSRC_temp,UCSZ0);
		SET_BIT(UCSRC_temp,UCSZ1);
		CLR_BIT(UCSRB_temp,UCSZ2);
	#elif CHAR_SIZE == 	BIT_9
		SET_BIT(UCSRC_temp,UCSZ0);
		SET_BIT(UCSRC_temp,UCSZ1);
		SET_BIT(UCSRB_temp,UCSZ2);
	#endif

// Mode Select
	#if   MODE_SEL == ASYNC
		CLR_BIT(UCSRC_temp,UMSEL);
		// Selecting Speed
		#if   SPEED == SINGLE_SPEED
			CLR_BIT(UCSRA_temp,U2X);
		#elif SPEED == DOUBLE_SPEED
			SET_BIT(UCSRA_temp,U2X);
		#endif
	#elif MODE_SEL == SYNC
		SET_BIT(UCSRC_temp,UMSEL);
		// Clock Polarity (Sync Mode only)
		#if    CLK_POL == R_TX_F_RX
			   CLR_BIT(UCSRC_temp,UCPOL);
		#elif  CLK_POL == F_TX_R_RX
			   SET_BIT(UCSRC_temp,UCPOL);
		#endif
	#endif

// Parity Mode
	#if   PARITY == OFF
		CLR_BIT(UCSRC_temp,UPM0);
		CLR_BIT(UCSRC_temp,UPM1);
	#elif PARITY == EVEN
		CLR_BIT(UCSRC_temp,UPM0);
		SET_BIT(UCSRC_temp,UPM1);
	#elif PARITY == ODD
		SET_BIT(UCSRC_temp,UPM0);
		SET_BIT(UCSRC_temp,UPM1);
	#endif

// Stop Bit Mode
	#if   STOP_BIT == BIT_1
		CLR_BIT(UCSRC_temp,USBS);
	#elif STOP_BIT == BIT_2
		SET_BIT(UCSRC_temp,USBS);
	#endif

// Empty Interrupt Setting
	#if   EMPTY_INT == DIS
		CLR_BIT(UCSRB_temp,UDRIE);
	#else
		SET_BIT(UCSRB_temp,UDRIE);
		SET_BIT(SREG,7);
	#endif

// TX Interrupt Setting
	#if   TX_INT == DIS
		CLR_BIT(UCSRB_temp,TXCIE);
	#else
		SET_BIT(UCSRB_temp,TXCIE);
		SET_BIT(SREG,7);
	#endif

// RX Interrupt Setting
	#if   RX_INT == DIS
		CLR_BIT(UCSRB_temp,RXCIE);
	#else
		SET_BIT(UCSRB_temp,RXCIE);
		SET_BIT(SREG,7);
	#endif


// Enabling Transmitter and Receiver
// Transmitter
	#if   TX_EN == DIS
		CLR_BIT(UCSRB_temp,TXEN);
	#else
		SET_BIT(UCSRB_temp,TXEN);
	#endif

// Receiver
	#if   RX_EN == DIS
		CLR_BIT(UCSRB_temp,RXEN);
	#else
		SET_BIT(UCSRB_temp,RXEN);
	#endif

// Loading UCSRC with Configured value
	UCSRA = UCSRA_temp;
	UCSRB = UCSRB_temp;
	UCSRC = UCSRC_temp;

// Pin Configuration
	DIO_SetPinDir(PORTD_0,INPUT);
	DIO_SetPinDir(PORTD_1,OUTPUT);

}

void USART_Write(unit16 Data)
{
  // Wait till Buffer is Empty
   while(GET_BIT(UCSRA,UDRE) == 0);

#if CHAR_SIZE == 	BIT_9
   // Load Data in Case of 9 Bit
   if(GET_BIT(Data,8)) SET_BIT(UCSRB,TXB8);
   else                CLR_BIT(UCSRB,TXB8);
#endif

  // Load UDR with Data
  UDR = (unit8) Data;

  // Wait Till Transmission is complete
  while(GET_BIT(UCSRA,TXC) == 0);

  // Clear Transmission Flag (Optional)
  SET_BIT(UCSRA,TXC);
}

unit16 USART_Read()
{
   // Variable to store Received data
   unit16 data = 0;

   // Status Checking Variable
   unit8 status = 0;

   // Wait till reception is completed
  while(GET_BIT(UCSRA,RXC) == 0);

  // Reading Status
   status = UCSRA;

   // Generate error in case of Frame Error , Parity Error and Data Over-Run
   if(GET_BIT(status,FE) | GET_BIT(status,PE) | GET_BIT(status,DOR))  return -1;

#if CHAR_SIZE == 	BIT_9
   // Get Data in Case of 9 Bit
   data = GET_BIT(UCSRB,RXB8) << 8;
#endif
  data |= (unit16)UDR;

  // Return data
  return data;

}

// Function used to Flush UDR Buffer in case of Error to Empty Register to be ready for another Reception
void USART_Flush(void){
	// Read Data till UDR is empty
	unit8 dummy;
	while(GET_BIT(UCSRA,RXC) == 1) dummy = UDR;
}

unit8 Rx_Interrupt(void)
{

	USART_Read();
}
void SetUSARTReceiveCallBack(void (*ptr)())
{
	if(ptr != 0LL)
	{
		ptr_RXC = ptr;
	}
}

void SetUSARTTransmitCallBack(void (*ptr)())
{
	if(ptr != 0LL)
	{
		ptr_TXC = ptr;
	}
}

ISR(USART_RXC_vect)
{
	if(ptr_RXC != 0LL) ptr_RXC();
}

ISR(USART_TXC_vect)
{
	if(ptr_TXC != 0LL) ptr_TXC();
}

// Data Register
// UDR: USART I/O Data Register (Read in Rx mode, Write in Tx mode there are two registers with common address)


// Flags
// UCSRA : USART Control and Status Register A
// UCSRA : RXC TXC UDRE FE DOR PE U2X MPCM
// RXC   : Receiver Complete Flag : 1 -> uncompleted , 0 -> completed
// TXC   : Transmitter Complete Flag : 1 -> completed , 0 -> interrupt is executed
// UDRE  : USART Data Register Empty : 1 -> Ready to write in transmitter buffer, 0 buffer is full
// FE    : Frame Error : Set when write to UCSRA
// DOR   : Data Over Run : Clear when write to UCSRA
// PE    : Parity Error : Clear when write to UCSRA
// U2X   : Double the USART Transmission Speed : Clear when using Synchronous
// MPCM  : Used in Multi-Processor Communication Mode (Later)

// USART Interrupt Register
// UCSRB : USART Control and Status Register B
// UCSRB : RXCIE TXCIE UDRIE RXEN TXEN UCSZ2 RXB8 TXB8
// RXCIE : Receive Complete interrupt enable : 1 -> Enable interrupt
// TXCIE : Transmitter Complete interrupt enable : 1 -> Enable interrupt
// UDRIE : USART Data Register Empty Interrupt Enable : 1 -> enables interrupt on the UDRE Flag
// RXEN  : Receiver Enable : 1 -> enables the USART Receiver
// TXEN  : Transmitter Enable : 1 -> enables the USART Transmitter
// UCSZ2 : Character Size : The UCSZ2 bits combined with the UCSZ1:0 bit in UCSRC sets the number of data bits
// RXB8  : Receive Data Bit 8 : the ninth data bit of the received character
// TXB8  : Transmitter Data Bit 8 : the ninth data bit of the transmitted character

// UCSRC : USART Control and Status Register C
// UCSRC : URSEL UMSEL UPM1 UPM0 USBS UCSZ1 UCSZ0 UCPOL
// URSEL : Register Select : This bit selects between accessing the UCSRC or the UBRRH Register. 1 -> UCSRC
// UMSEL : USART Mode Select : 0 -> Asynchronous Operation , 1 -> Synchronous
// UPM1:0 : Parity Mode : 0 -> Disabled , 1 -> reserved , 2 -> Even , 3 -> odd
// USBS  : Stop Bit Select : 0 -> 1-bit , 1 -> 2-bit
// UCSZ1:0 : Character Size : 0 -> 5-bit , 1 -> 6-bit , 2 -> 7-bit , 3 -> 8-bit , 7 -> 9-bit (rest is reserved)
// UCPOL  : Clock Polarity : 0 -> Rising TX Falling RX , 1 -> Falling TX Rising RX

// UBRRL and UBRRH :USART Baud Rate Registers : refer to Page No. 162 - 166 in ATMEGA32 Datasheet

// Multi-Processor Communication Mode (Skipped)

