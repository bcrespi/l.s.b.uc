/******************************************************************************/
/*                                                                            */
/* Description: LED library (source)                                          */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "LEDlib.h"

#include <p30F4011.h>

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

// LED config registers (I/O)
#define LED0_TRIS TRISEbits.TRISE0
#define LED1_TRIS TRISEbits.TRISE1
#define LED2_TRIS TRISEbits.TRISE2
#define LED3_TRIS TRISEbits.TRISE3
#define LED4_TRIS TRISEbits.TRISE4
#define LED5_TRIS TRISEbits.TRISE5

// LED write registers (value)
#define LED0 LATEbits.LATE0
#define LED1 LATEbits.LATE1
#define LED2 LATEbits.LATE2
#define LED3 LATEbits.LATE3
#define LED4 LATEbits.LATE4
#define LED5 LATEbits.LATE5

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

// Initialize LED
// This function config. the port as output 
void LEDInit()
{
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
}

// Turn on the LED selected (0-5)
void onLED(unsigned int led)
{
    switch(led)
    {
        case 0: LED0 = 1; break;
        case 1: LED1 = 1; break;
        case 2: LED2 = 1; break;
        case 3: LED3 = 1; break;
        case 4: LED4 = 1; break;
        case 5: LED5 = 1; break;
    }
}

// Turn off the LED selected (0-5)
void offLED(unsigned int led)
{
    switch(led)
    {
        case 0: LED0 = 0; break;
        case 1: LED1 = 0; break;
        case 2: LED2 = 0; break;
        case 3: LED3 = 0; break;
        case 4: LED4 = 0; break;
        case 5: LED5 = 0; break;
    }
}

void switchLED(unsigned int led)
{
	switch(led)
    {
        case 0: LED0 = ((LED0 + 1) % 2); break;
        case 1: LED1 = ((LED1 + 1) % 2); break;
        case 2: LED2 = ((LED2 + 1) % 2); break;
        case 3: LED3 = ((LED3 + 1) % 2); break;
        case 4: LED4 = ((LED4 + 1) % 2); break;
        case 5: LED5 = ((LED5 + 1) % 2); break;
    }
}
