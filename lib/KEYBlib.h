/******************************************************************************/
/*                                                                            */
/* Description: keyboard library (header)                                     */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

#define NO_KEY_PRESSED	-1

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

// Initialize LCD
void KeybInit();

// Get key pressed (block until key is pressed)
char getKeyBlocking();

// Get key pressed (no bloking)
char getKeyNotBlocking();

// Get keys pressed (no bloking)
void getMultiKeyNotBlocking(char *keys);
