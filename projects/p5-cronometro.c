/******************************************************************************/
/*                                                                            */
/* Description: Practica guiada 5                                             */
/*				Cronómetro de cuenta atrás                                    */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "LCDlib.h"
#include "TIMERlib.h"
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

volatile float time_left;
// char to save if timer is running
char running = 0;
char message[5];
unsigned int delay;

/******************************************************************************/
/* _ISR _Interrupt                                                            */
/******************************************************************************/

void _ISR _T1Interrupt(void)
{
	// Clear interrupt
    TimerClearInt();
    time_left -= 0.001;
    if(time_left < 0.001)
    {
    	running = 0;
    	Timer1Stop();
    }
}

/******************************************************************************/
/* Pre-declarared functions                                                   */
/******************************************************************************/

void print()
{
	memset(message, 0, sizeof(message));
	sprintf(message, "%.3f", time_left);
	LCDClear();
	LCDMoveHome();
	LCDPrint(message);
}

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

int main(void)
{
	// char to save the key pressed and the last/before key
	char c, last = -1;

	// Initialize keyboard and lcd
	KeybInit();
	LCDInit();

	// Configure Timer1
	Timer1Init(29492, 0b00, 4);

	while(1)
	{
		// Get the key pressed
		c = getKeyNotBlocking();

		if(c != NO_KEY_PRESSED && c != last)
		{
			// Save key
			last = c;

			// Timer has been started
			if(running && c == 5)
			{
				// Pressed pause
				running = 0;
				Timer1Pause();
			}
			else if(!running && c == 8)
			{
				running = 0;
				time_left = 0;
				Timer1Stop();
			}
			else if(!running)
			{
				// Modify time
				switch(c)
				{
					case 0:
						if(time_left <= 58.999)
						{
							time_left += 1;
						}
					break;
					case 1:
						if(time_left <= 59.998)
						{
							time_left += 0.001;
						}
					break;
					case 6:
						if(time_left >= 1.000)
						{
							time_left -= 1;
						}
					break;
					case 7:
						if(time_left >= 0.001)
						{
							time_left -= 0.001;
						}
					break;
					case 2:
						if(time_left > 0.000)
						{
							running = 1;
							Timer1Start();
						}
					break;
				}
			}
		}
		else
		{
			// Key non released or any key pressed
			// Save key
			last = c;
		}
		print();
	}
}
