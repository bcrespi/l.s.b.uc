/******************************************************************************/
/*                                                                            */
/* Description: Timer library (header)                                        */
/*                                                                            */
/* Authors: Bartomeu Crespi Jimenez                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

// Initialize Timer
void Timer1Init(unsigned int period, unsigned char pscaler, unsigned char priority);

// Start Timer
void Timer1Start();

// Pause Timer
void Timer1Pause();

// Stop Timer
void Timer1Stop();

// Clear Timer Interruption
void TimerClearInt();
