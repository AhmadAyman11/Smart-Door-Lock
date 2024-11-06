#ifndef HOLD_FUNCTION_H_
#define HOLD_FUNCTION_H_

#include "std_types.h" // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Duration1      15   // Duration for hold function (in seconds)
#define Duration2      60   // Duration for wrong attempt lockout (in seconds)
#define MAX_ATTEMPTS   3    // Maximum allowed password attempts

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
// Callback function prototype for timer
void Timer_Callback(void);

// Function to hold for a specified duration
void Timer_Hold(uint8 duration1);

// Function to handle actions on wrong attempts for a specified duration
void Wrong_attempt(uint8 duration2);

#endif /* HOLD_FUNCTION_H_ */
