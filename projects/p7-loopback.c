/******************************************************************************/
/*                                                                            */
/* Description: Practica guiada 7                                             */
/*				CAN in distributed systems - loopback mode                    */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "CANlib.h"
#include "LCDlib.h"
#include "delay.h"

#include <stdio.h>
#include <string.h>

#include <p30f4011.h>

/******************************************************************************/
/* Configuration words                                                        */
/******************************************************************************/

_FOSC(CSW_FSCM_OFF & EC_PLL16);
_FWDT(WDT_OFF);
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF);
_FGS(CODE_PROT_OFF);

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

unsigned int sid;
unsigned int ide;
unsigned int rtr;
unsigned char dlc;
unsigned char data;

unsigned int i;
unsigned int j;

/******************************************************************************/
/* Pre-declarared functions                                                   */
/******************************************************************************/

void printMessage(unsigned int sid, unsigned char data, unsigned char dlc);

/******************************************************************************/
/* _ISR _Interrupt                                                            */
/******************************************************************************/

void _ISR _C1Interrupt(void)
{
	if(C1INTFbits.RX0IF == 1)
	{
		sid = C1RX0SIDbits.SID;
		ide = C1RX0SIDbits.RXIDE;
		rtr = C1RX0DLCbits.RXRTR;
		dlc = C1RX0DLCbits.DLC;

		data = C1RX0B1 & 0x00FF;

		// Clear rxbuffer 0
		C1RX0CONbits.RXFUL = 0;

		// Clear interrupt flag associated to rx buffer 0
		C1INTFbits.RX0IF = 0;
	}
	// Print message received
	printMessage(sid, data, dlc);
	// Clear global CAN interrupt flag
	IFS1bits.C1IF = 0;
}

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

int main(void)
{
	// Declaration and initialization of message-related data
	unsigned int txMsgSID = 0;
	unsigned char txMsgData[12] = {'1', '2', '3', '4', '5', 'S', 'X', 'U', 'C', 'L', 'D', 'R'};

	unsigned char buffer[32];
	unsigned int lenght = 0;
	unsigned int cursorPosition = 0;

	// Initialize keyboard, CAN and LCD
	KeybInit();
	CANinit(LOOPBACK_MODE, 0x0000, 0x0000);
	LCDInit();

	// Clear LCD
	LCDClear();

	// Char to save key pressed
	unsigned char c;

	while(1)
	{
		if(CANtransmissionCompleted())
		{
			// Get key pressed
			c = getKeyBlocking();

			if(lenght < 32 && cursorPosition < 32)
			{
				buffer[lenght] = txMsgData[c];
				lenght++;

				if(c == 0 || c == 1 || c == 2 || c == 3 || c == 4 || c == 11)
				{
					switch(c)
					{
						case 0:		LCDPrint("1");	break;
						case 1:		LCDPrint("2");	break;
						case 2:		LCDPrint("3");	break;
						case 3:		LCDPrint("4");	break;
						case 4:		LCDPrint("5");	break;
						case 11:	LCDMoveRight(); break;
					}

					// Cursor managment - Update position
					if(cursorPosition == 15)
					{
						// Cursor is at the end of the first line
						// Move to second line
						LCDMoveSecondLine();
					}
					// Increase cursor position
					cursorPosition++;
				}
				else if(c == 6 || c == 9)
				{
					// Pressed erase and go back key ( <- )
					if(cursorPosition == 0)
					{
						// Cursor is at the begining of the first line
						// Do nothing
					}
					else if(cursorPosition == 16)
					{
						// Cursor is at the begining of the second line
						// Move cursor to the last position of the first line
						LCDSetCursor(15);
						if(c == 6)
						{
							// Erase content (print a white space)
							LCDPrint(" ");
							// Move cursor back and decrease cursor position
							LCDMoveLeft();
						}
						cursorPosition--;
					}
					else
					{
						// Cursor is between extreme positions or at position 32
						// Move cursor back
						LCDMoveLeft();
						if(c == 6)
						{
							// Erase content (print a white space)
							LCDPrint(" ");
							// Move cursor back and decrease cursor position
							LCDMoveLeft();
						}
						cursorPosition--;
					}
				}
				else if(c == 7)
				{
					// Move to first line
					LCDMoveFirstLine();
					cursorPosition = 0;
				}
				else if(c == 10)
				{
					// Move to second line
					LCDMoveSecondLine();
					cursorPosition = 16;
				}
				else
				{
					// Pressed clear (C) or send (S)
					if(c == 8)
					{
						// Clear LCD
						LCDClear();
						// Move to home
						LCDMoveHome();
						// Set counter of cursor position to 0 (zero)
						cursorPosition = 0;
					}
					else
					{
						// Clear LCD and show message
						////////////////////
						//    SENDING!    //
						//                //
						////////////////////
						LCDClear();
						LCDMoveHome();
						LCDPrint("    SENDING!");

						// Wait 1s before start send
						for(i = 0; i < 200; i++) Delay5ms();
						// Clear LCD
						LCDClear();

						// Send message according keys pressed
						for(i = 0; i < lenght; i++)
						{
							CANsendMessage(txMsgSID, buffer[i]);
							// Wait until transmission complete
							while(CANtransmissionCompleted() == 0);
							// Wait 0,5s before send the next
							for(j = 0; j < 100; j++) Delay5ms();
						}

						lenght = 0;
						cursorPosition = 0;
						LCDMoveHome();
					}
				}
			}
			else
			{
				// Clear LCD and show message in two lines
				////////////////////
				//    WARNING!    //
				//  Full memory   //
				////////////////////
				LCDClear();
				LCDMoveHome();
				LCDPrint("    WARNING!");
				LCDMoveSecondLine();
				LCDPrint("  Full memory");

				// Pressed key send (S)
				if(c == 5)
				{
					// Clear LCD and show message
					////////////////////
					//    SENDING!    //
					//                //
					////////////////////
					LCDClear();
					LCDMoveHome();
					LCDPrint("    SENDING!");

					// Wait 1s before start send
					for(i = 0; i < 200; i++) Delay5ms();
					// Clear LCD
					LCDClear();

					// Send message according keys pressed
					for(i = 0; i < lenght; i++)
					{
						CANsendMessage(txMsgSID, buffer[i]);
						// Wait until transmission complete
						while(CANtransmissionCompleted() == 0);
						// Wait 0,5s before send the next
						for(j = 0; j < 100; j++) Delay5ms();
					}
				
					lenght = 0;
					cursorPosition = 0;
					LCDMoveHome();
				}
			}
		}
		// Wait 0,25s before to detect another time the key pressed
		for(i = 0; i < 50; i++) Delay5ms();
	}
}

void printMessage(unsigned int sid, unsigned char data, unsigned char dlc)
{
	char buffer[32];

	// Print frame information on LCD
	for(j = 0; j < dlc; j++)
	{
		sprintf(buffer, "%c", data);
		LCDPrint(buffer);
	}
}

/*
void printMessage(unsigned int sid, unsigned char data, unsigned char dlc)
{
	char buffer[32];

	// Print frame information on LCD
	LCDClear();
	LCDMoveFirstLine();
	sprintf(buffer, "SID=%u DLC=%u", sid, dlc);
	LCDPrint(buffer);
	
	LCDMoveSecondLine();
	LCDPrint("Data: ");
	for(j = 0; j < dlc; j++)
	{
		sprintf(buffer, "%c", data);
		LCDPrint(buffer);
	}
}
*/
