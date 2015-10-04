/******************************************************************************/
/*                                                                            */
/* Description: keyboard library (header)                                     */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez & Francesc Bisquerra Castell              */
/*                                                                            */
/******************************************************************************/

#define NO_KEY_PRESSED	-1

// Initialize LCD
void KeybInit();

// Get key pressed (block until key is pressed)
unsigned char getKeyBlocking();
// Get key pressed (no bloking)
unsigned char getKeyNotBlocking();
// Get keys pressed (no bloking)
unsigned char getMultiKeyNotBlocking();
