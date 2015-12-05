/******************************************************************************/
/*                                                                            */
/* Description: CAN library (header)                                          */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

 #define NORMAL_MODE	0b000
 #define LOOPBACK_MODE	0b010

/* 
 * 100 = Set Configurationmode
 * 000 = Set Normal Operationmode
 * 010 = Set Loopbackmode
 * 011 = Set Listen Onlymode
 * 001 = Set Disablemode
 */

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

// Initialize CAN (mode, mask, and filter)
void CANinit(unsigned char mode, unsigned int mask, unsigned int filter);

/*
// Send message (more than one byte)
void CANsendMessage(unsigned int sid, unsigned char *data, unsigned int lenght);
*/

// Send message (only one byte)
void CANsendMessage(unsigned int sid, unsigned char data);

// Check if transmission completed (after send, wait until transmission completed)
unsigned char CANtransmissionCompleted();
