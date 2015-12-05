/******************************************************************************/
/*                                                                            */
/* Description: Practica guiada 1                                             */
/*				keyboard and leds testing                                     */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "LEDlib.h"
#include "delay.h"

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

int sequenceLine1[] = {0, 1};
int sequenceLine2[] = {2, 3};
int sequenceLine3[] = {4, 5};

int sequenceColumn1[] = {0, 2, 4};
int sequenceColumn2[] = {1, 3, 5};

// int to iterate
int iteration;
int delay;

/******************************************************************************/
/* Pre-declarared functions                                                   */
/******************************************************************************/

void sequenceLine(int line[]);
void sequenceColumn(int column[]);
void imCrazyAndTurnAllOff();

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

int main(void)
{
	// char to save the key pressed and the last/before key
	char c, last = -1;

	// Initialize keyboard and led
	KeybInit();
	LEDInit();

	while(1)
	{
		// Get the key pressed
		c = getKeyNotBlocking();

		if(c != NO_KEY_PRESSED || last == 2 || last == 5 || last == 8 || last == 9 || last == 10)
		{
			// Here you have pressed one key or last key pressed is 2, 5, 8, 9 or 10
			// Restore last key pressed
			if(c == NO_KEY_PRESSED && (last == 2 || last == 5 || last == 8 || last == 9 || last == 10)) c = last;

			if(c != NO_KEY_PRESSED)
			{
				// Check key pressed
				switch(c)
				{
					case 0: 	onLED(0);							break;
					case 1: 	onLED(1);							break;
					case 2: 	sequenceLine(sequenceLine1);		break;
					case 3: 	onLED(2);							break;
					case 4: 	onLED(3);							break;
					case 5: 	sequenceLine(sequenceLine2);		break;
					case 6: 	onLED(4);							break;
					case 7: 	onLED(5);							break;
					case 8: 	sequenceLine(sequenceLine3);		break;
					case 9: 	sequenceColumn(sequenceColumn1);	break;
					case 10: 	sequenceColumn(sequenceColumn2);	break;
					case 11:	imCrazyAndTurnAllOff();				break;
				}
				// Save last key pressed
				last = c;
			}
		}
		else
		{
			// Here you have not pressed any key and last key is different to 2, 5, 8, 9 and 10
			if(last != NO_KEY_PRESSED){
				switch(last)
				{
					case 0:		offLED(0);			break;
					case 1:		offLED(1);			break;
					case 3:		offLED(2);			break;
					case 4:		offLED(3);			break;
					case 6:		offLED(4);			break;
					case 7:		offLED(5);			break;
				}
				// Save last key pressed
				last = c;
			}			
		}
	}
}

void sequenceLine(int line[])
{
	for(iteration = 0; iteration < 2; iteration++)
	{
		onLED(line[iteration]);
		// Wait 0,5s
		for(delay = 0; delay < 100; delay++)
		{
			Delay5ms();
		}
		offLED(line[iteration]);
	}
}

void sequenceColumn(int column[])
{
	for(iteration = 0; iteration < 3; iteration++)
	{
		onLED(column[iteration]);
		// Wait 0,5s
		for(delay = 0; delay < 100; delay++)
		{
			Delay5ms();
		}
		offLED(column[iteration]);
	}
}

void imCrazyAndTurnAllOff()
{
	for(iteration = 0; iteration < 6; iteration++)
	{
		offLED(iteration);
	}
}
