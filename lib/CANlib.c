
/******************************************************************************/
/*                                                                            */
/* Description: CAN library (source)                                          */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "CANlib.h"

#include <p30f4011.h>

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

/*
 * 100 = Set Configurationmode
 * 000 = Set Normal Operationmode
 * 010 = Set Loopbackmode
 * 011 = Set Listen Onlymode
 * 001 = Set Disablemode
 */

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

void CANinit(unsigned char mode, unsigned int mask, unsigned int filter)
{
	// Set configuration mode
	C1CTRLbits.REQOP = 0b100;
	// Wait until configuration mode
	while(C1CTRLbits.OPMODE != 0b100);

	C1CTRLbits.CANCKS = 1; // FCAN = FCY

	// BTR - BTR1
	C1CFG1bits.BRP = 1; // 1Mbps
	C1CFG1bits.SJW = 1; // 1 TQ
	// BTR - BTR2
	C1CFG2bits.PRSEG  = 1; // 1 TQs
	C1CFG2bits.SEG1PH = 4; // 4 TQs
	C1CFG2bits.SEG2PH = 2; // 2 TQs

	// Txbuffer 0
	C1TX0CONbits.TXREQ = 0; // Clear txrequest

	// Rx buffer 0
	C1RX0CONbits.RXFUL = 0; // Clear rxstatus

	// Disable double buffer
	C1RX0CONbits.DBEN = 0;

	// Configure acceptance masks
	C1RXM0SIDbits.SID = mask; 	// Bits to compare
	C1RXM0SIDbits.MIDE = 1; 	// Determine as EXIDE

	// Configure acceptance filters
	C1RXF0SIDbits.SID   = filter; 	// Doesn't matter the value as mask is ‘0’
	C1RXF0SIDbits.EXIDE = 0;		// Enable filter for standard identifier

	// Interrupts
	IEC1bits.C1IE = 1; // Enable global CAN interrupt
	IFS1bits.C1IF = 0; // Clear global CAN interrupt flag

	// Enable Configure interrupts
	C1INTE = 0;
	C1INTEbits.RX0IE = 1; // Enable interrupt associated to rx buffer 0
	C1INTFbits.RX0IF = 0; // Clear interrupt flag associated to rx buffer 0

	// Set mode
	C1CTRLbits.REQOP = mode; 
	 // Wait until mode
	while(C1CTRLbits.OPMODE != mode);
}

/*
void CANsendMessage(unsigned int sid, unsigned char *data, unsigned int lenght)
{
	// Txbuffer 0
	C1TX0DLCbits.TXRTR = 0; // Set data frame
	C1TX0SIDbits.TXIDE = 0; // Set standard identifier

	// Set identifier - only use 11 bits - value max. 2047
	// unsigned int occupy 2 bytes (16 bits)
	C1TX0SIDbits.SID5_0  = sid & 0x003F; 		// Set the lowest 6 bits
	C1TX0SIDbits.SID10_6 = (sid & 0x07C0) >> 6; // Set the highest 5 bits

	C1TX0DLCbits.DLC = lenght;	// DLC = data lenght

	// Send bytes
	for(i = 0; i < lenght; i++)
	{
		// Fill buffer
		C1TX0B1+i = data[i]   // Set data
	}

	C1TX0CONbits.TXREQ = 1;   // Transmit
}
*/

void CANsendMessage(unsigned int sid, unsigned char data)
{
	// Txbuffer 0
	C1TX0DLCbits.TXRTR = 0; // Set data frame
	C1TX0SIDbits.TXIDE = 0; // Set standard identifier

	// Set identifier - only use 11 bits - value max. 2047
	// unsigned int occupy 2 bytes (16 bits)
	C1TX0SIDbits.SID5_0  = sid & 0x003F; 		// Set the lowest 6 bits
	C1TX0SIDbits.SID10_6 = (sid & 0x07C0) >> 6; // Set the highest 5 bits

	C1TX0DLCbits.DLC = 1;	// DLC 1 byte
	C1TX0B1 = data;   	  	// Set data
	
	C1TX0CONbits.TXREQ = 1;	// Transmit
}

unsigned char CANtransmissionCompleted()
{
	if(C1TX0CONbits.TXREQ != 0) return 0;
	return 1;
}

/*
void _ISR _C1Interrupt(void)
{
	if(C1INTFbits.RX0IF == 1)
	{
		sid = C1RX0SIDbits.SID;
		ide = C1RX0SIDbits.RXIDE; // standard or extended frame
		rtr = C1RX0DLCbits.RXRTR; // 1 remote frame
		dlc = C1RX0DLCbits.DLC;

		data = C1RX0B1 & 0x00FF;

		// Clear rxbuffer 0
		C1RX0CONbits.RXFUL = 0;

		// Clear interrupt flag associated to rx buffer 0
		C1INTFbits.RX0IF = 0;
	}
	// Clear global CAN interrupt flag
	IFS1bits.C1IF = 0
}
*/
