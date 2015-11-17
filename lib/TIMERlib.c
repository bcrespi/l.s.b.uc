/******************************************************************************/
/*                                                                            */
/* Description: Timer library (source)                                        */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

#include "TIMERlib.h"

#include <p30F4011.h>

/******************************************************************************/
/* Global variable declarations                                               */
/******************************************************************************/

#define TIMER_PSCALER_1_1 	0b00
#define TIMER_PSCALER_1_8   0b01
#define TIMER_PSCALER_1_64  0b10
#define TIMER_PSCALER_1_256 0b11

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

// Clock: 29.491.200 Hz ≈ 30 MHz
// Size counter: 16bits -> 65536
// Prescaler: 1:1
//	- FclkTimer = 29.491.200 Hz -> TclkTimer = 33,9084 ns
// Prescaler: 1:8
//
// Prescaler: 1:64
//
// Prescaler: 1:256
//

// Initialize Timer
void Timer1Init(unsigned int period, unsigned char pscaler, unsigned char priority)
{
	// Config. Timer 1 control register
	T1CON = 0x0000;
	T1CONbits.TCKPS = pscaler;
	T1CONbits.TCS = 0;

	// Clean counter
	TMR1 = 0x0000;
	PR1 = period;

	// Config. interruptions
	// Enable Timer 1 interruption
	IEC0bits.T1IE = 1;
	// Clean status flag
	IFS0bits.T1IF = 0;
	// Set piority
	IPC0bits.T1IP = priority;
}

// Start Timer
void Timer1Start()
{
	T1CONbits.TON = 1;
}

// Pause Timer
void Timer1Pause()
{
	T1CONbits.TON = 0;
}

// Stop Timer
void Timer1Stop()
{
	T1CONbits.TON = 0;
	// Clean counter
	TMR1 = 0x0000;
}

// Clear interrupt
void TimerClearInt()
{
	IFS0bits.T1IF = 0;
}
