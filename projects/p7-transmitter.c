/******************************************************************************/
/*                                                                            */
/* Description: Practica guiada 7                                             */
/*				CAN in distributed systems - transmitter                      */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "CANlib.h"

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

/******************************************************************************/
/* Pre-declarared functions                                                   */
/******************************************************************************/

void printMessage(unsigned int msgSID, unsigned char * msgData, unsigned char msgDLC);

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

int main(void)
{
	// Declaration and initialization of message-related data
	unsigned int txMSGSID = 0;
	unsigned char txMsgData[12] = {'1', '2', '3', '4', '5', 'S', 'X', 'U', 'C', 'L', 'D', 'R'};
	unsigned char txMsgDLC;

	// Initialize keyboard and CAN
	KeybInit();
	CANInit(NORMAL_MODE, 0x0000, 0x0000);
	LCDInit();

	// Clear LCD
	LCDClear();

	while(1)
	{

	}
}
