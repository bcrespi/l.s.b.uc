/******************************************************************************/
/*                                                                            */
/* Description: LCD library (library)                                         */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez & Francesc Bisquerra Castell              */
/*                                                                            */
/******************************************************************************/

// Initialize LCD
void LCDInit();

// Clear LCD
void LCDClear();

// Move the cursor of the LCD to home
void LCDMoveHome();
// Move LCD cursor to first or second line.
void LCDMoveFirstLine();
void LCDMoveSecondLine();

// Writes a string to the alphanumeric LCD
void LCDPrint(char *str);

// Move LCD cursor left or right
void LCDMoveLeft();
void LCDMoveRight();

// Scroll LCD Screen left or right
void LCDScrollLeft();
void LCDScrollRight();

// Hide LCD cursor
void LCDHideCursor();
// Turn on underline LCD cursor
void LCDTurnOnUnderline();
// Turn on blinking-block LCD cursor
void LCDTurnOnBlinking();

// Move LCD cursor to specified position
// Only for LCD with 2 lines and 40 positions x line
void LCDSetCursor(unsigned int position);
