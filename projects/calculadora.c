/******************************************************************************/
/*                                                                            */
/* Description: Practica guiada 2                                             */
/*				Interfaz de una calculadora                                   */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez & Francesc Bisquerra Castell              */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "LCDlib.h"
#include "delay.h"

#include <stdio.h>

#include <p30f4011.h>

int main(void)
{
	// char to save the key pressed and the last/before key
	char c, last = -1;
	
	// Counter of keys pressed (to know the cursor position)
	unsigned int cursorPosition = 0;

	// Initialize keyboard and lcd
	KeybInit();
	LCDInit();

	/*
	 * Pattern collection:
	 *
	 *	- Skull 			{0x04, 0x0E, 0x15, 0x1B, 0x0E, 0x15, 0x0A, 0x00}
	 *	- Heart 			{0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00}
	 *	- Heart (filled) 	{0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00}
	 *	- Key 				{0x0C, 0x04, 0x0C, 0x04, 0x1F, 0x11, 0x1F, 0x00}
	 *	- Bomb				{0x01, 0x01, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00}
	 *	- Home				{0x04, 0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x0A, 0x00}
	 *	- Battery			{0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00}
	 *	- Plug				{0x0A, 0x0A, 0x1F, 0x11, 0x1B, 0x0E, 0x04, 0x04}
	 */

	char skull[] = {0x04, 0x0E, 0x15, 0x1B, 0x0E, 0x15, 0x0A, 0x00};
	char bomb[] = {0x01, 0x01, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00};

	// Save pattern
	LCDStoreCharPattern(0, skull);
	LCDStoreCharPattern(1, bomb);

	// Points to DDRAM
	LCDMoveHome();

	// Personalized start message with patterns
	// Show pattern
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);
	LCDPrint(" ");
	LCDShowCharPattern(0);

	LCDMoveSecondLine();

	LCDPrint("failure ");
	LCDShowCharPattern(1);
	LCDPrint(" ");
	LCDShowCharPattern(1);
	LCDPrint(" ");
	LCDShowCharPattern(1);
	LCDPrint(" ");
	LCDShowCharPattern(1);

	cursorPosition = 31;

	// ALERT!
	// LCD has 2x16 digits that we can see (without scroll)

	while(1)
	{
		// Get the key pressed
		c = getKeyNotBlocking();

		// Need release the key for write the same key
		if(c != NO_KEY_PRESSED && c != last)
		{
			// Save key
			last = c;

			// Key actions
			if(c != 9 && c != 10)
			{
				// Pressed a writtable key

				// Cursor managment - Limits of LCD
				if(cursorPosition == 32)
				{
					// Do nothing - Out of LCD
				}
				else
				{
					// Print character
					switch(c)
					{
						case 0: 	LCDPrint("1"); 	break;
						case 1: 	LCDPrint("2"); 	break;
						case 2: 	LCDPrint("+"); 	break;
						case 3: 	LCDPrint("3"); 	break;
						case 4: 	LCDPrint("4"); 	break;
						case 5: 	LCDPrint("-"); 	break;
						case 6: 	LCDPrint("5"); 	break;
						case 7: 	LCDPrint("6"); 	break;
						case 8: 	LCDPrint("x"); 	break;
						case 11: 	LCDPrint("/"); 	break;
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
			}
			else if(c != 10)
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
					// Erase content (print a white space)
					LCDPrint(" ");
					// Move cursor back and decrease cursor position
					LCDMoveLeft();
					cursorPosition--;
				}
				else
				{
					// Cursor is between extreme positions or at position 32
					// Move cursor back
					LCDMoveLeft();
					// Erase content (print a white space)
					LCDPrint(" ");
					// Move cursor back and decrease cursor position
					LCDMoveLeft();
					cursorPosition--;
				}
			}
			else
			{
				// Pressed clear key ( c )

				// Clear LCD
				LCDClear();
				// Move to home
				LCDMoveHome();
				// Set counter of cursor position to 0 (zero)
				cursorPosition = 0;
			}
		}
		else
		{
			// Key non released or any key pressed

			// Save key
			last = c;
			// Correct when release any key
			Delay15ms();
		}
	}
}
