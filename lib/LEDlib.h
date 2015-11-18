/******************************************************************************/
/*                                                                            */
/* Description: LED library (header)                                          */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

// Initialize LED
void LEDInit();

// Set LED on or off
void onLED(unsigned int led);
void offLED(unsigned int led);

// Swith LED
void switchLED(unsigned int led);
