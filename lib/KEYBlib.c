/******************************************************************************/
/*                                                                            */
/* Description: keyboard library (source)                                     */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez & Francesc Bisquerra Castell              */
/*                                                                            */
/******************************************************************************/

#include "KEYBlib.h"
#include "delay.h"

#include <p30F4011.h>

/******************************************************************************/
/* Pre-processor directives                                                   */
/******************************************************************************/

// Keyboard config. registers (I/O)
#define COL0_TRIS  TRISBbits.TRISB0
#define COL1_TRIS  TRISBbits.TRISB1
#define COL2_TRIS  TRISBbits.TRISB2
#define ROW0_TRIS  TRISDbits.TRISD0
#define ROW1_TRIS  TRISDbits.TRISD1
#define ROW2_TRIS  TRISDbits.TRISD2
#define ROW3_TRIS  TRISDbits.TRISD3

// Keyboard write registers (value)
#define COL0       LATBbits.LATB0
#define COL1       LATBbits.LATB1
#define COL2       LATBbits.LATB2

// Keyboard read registers (value)
#define ROW0       PORTDbits.RD0
#define ROW1       PORTDbits.RD1
#define ROW2       PORTDbits.RD2
#define ROW3       PORTDbits.RD3


/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

void KeybInit()
{
    // Initialize columns as output pins
    COL0_TRIS = 0;
    COL1_TRIS = 0;
    COL2_TRIS = 0;

    // Initialize rows as input pins
    ROW0_TRIS = 1;
    ROW1_TRIS = 1;
    ROW2_TRIS = 1;
    ROW3_TRIS = 1;
}

unsigned char getKeyBlocking()
{
    while(1)
    {
        // Check column 0
        COL0_TRIS = 0;
        COL1_TRIS = 1;
        COL2_TRIS = 1;
        COL0 = 0;
        COL1 = 1;
        COL2 = 1;

        Delay10us();

        // Check row values
        if(ROW0 == 0) return 0;
        if(ROW1 == 0) return 3;
        if(ROW2 == 0) return 6;
        if(ROW3 == 0) return 9;

        // Check column 1
        COL0_TRIS = 1;
        COL1_TRIS = 0;
        COL2_TRIS = 1;
        COL0 = 1;
        COL1 = 0;
        COL2 = 1;

        Delay10us();

        // Check row values
        if(ROW0 == 0) return 1;
        if(ROW1 == 0) return 4;
        if(ROW2 == 0) return 7;
        if(ROW3 == 0) return 10;

        // Check column 2
        COL0_TRIS = 1;
        COL1_TRIS = 1;
        COL2_TRIS = 0;
        COL0 = 1;
        COL1 = 1;
        COL2 = 0;

        Delay10us();

        // Check row values
        if(ROW0 == 0) return 2;
        if(ROW1 == 0) return 5;
        if(ROW2 == 0) return 8;
        if(ROW3 == 0) return 11;
    }
}

unsigned char getKeyNotBlocking()
{
    // Check column 0
    COL0_TRIS = 0;
    COL1_TRIS = 1;
    COL2_TRIS = 1;
    COL0 = 0;
    COL1 = 1;
    COL2 = 1;

    Delay10us();

    // Check row values
    if(ROW0 == 0) return 0;
    if(ROW1 == 0) return 3;
    if(ROW2 == 0) return 6;
    if(ROW3 == 0) return 9;

    // Check column 1
    COL0_TRIS = 1;
    COL1_TRIS = 0;
    COL2_TRIS = 1;
    COL0 = 1;
    COL1 = 0;
    COL2 = 1;

    Delay10us();

    // Check row values
    if(ROW0 == 0) return 1;
    if(ROW1 == 0) return 4;
    if(ROW2 == 0) return 7;
    if(ROW3 == 0) return 10;

    // Check column 2
    COL0_TRIS = 1;
    COL1_TRIS = 1;
    COL2_TRIS = 0;
    COL0 = 1;
    COL1 = 1;
    COL2 = 0;

    Delay10us();

    // Check row values
    if(ROW0 == 0) return 2;
    if(ROW1 == 0) return 5;
    if(ROW2 == 0) return 8;
    if(ROW3 == 0) return 11;

    return NO_KEY_PRESSED;
}

unsigned char getMultiKeyNotBlocking(char *buttons)
{
    // Check column 0
    COL0_TRIS = 0;
    COL1_TRIS = 1;
    COL2_TRIS = 1;
    COL0 = 0;
    COL1 = 1;
    COL2 = 1;

    Delay10us();

    // Check row values
    if(ROW0 == 0) buttons[0] = 1;
    if(ROW1 == 0) buttons[3] = 1;
    if(ROW2 == 0) buttons[6] = 1;;
    if(ROW3 == 0) buttons[9] = 1;;

    // Check column 1
    COL0_TRIS = 1;
    COL1_TRIS = 0;
    COL2_TRIS = 1;
    COL0 = 1;
    COL1 = 0;
    COL2 = 1;

    Delay10us();

    // Check row values
    if(ROW0 == 0) buttons[1] = 1;
    if(ROW1 == 0) buttons[4] = 1;
    if(ROW2 == 0) buttons[7] = 1;
    if(ROW3 == 0) buttons[10] = 1;

    // Check column 2
    COL0_TRIS = 1;
    COL1_TRIS = 1;
    COL2_TRIS = 0;
    COL0 = 1;
    COL1 = 1;
    COL2 = 0;

    Delay10us();

    // Check row values
    if(ROW0 == 0) buttons[2] = 1;
    if(ROW1 == 0) buttons[5] = 1;
    if(ROW2 == 0) buttons[8] = 1;
    if(ROW3 == 0) buttons[11] = 1;

    return NO_KEY_PRESSED;
}
