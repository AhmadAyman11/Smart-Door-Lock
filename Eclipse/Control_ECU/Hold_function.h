#ifndef HOLD_FUNCTION_H_
#define HOLD_FUNCTION_H_

#include "DCmotor.h"
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Duration1      15       // Duration for motor rotation in timer counts
#define Duration2      60       // Duration for buzzer activation in timer counts
#define Speed          50       // Default motor speed percentage (0-100)
#define MAX_ATTEMPTS   3        // Maximum number of attempts for certain operations

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * Timer callback function prototype for generic timer events.
 * This function is typically set as a callback for timers to increment counters.
 */
void Timer_Callback(void);

/**
 * Function to rotate the motor using a timer with a specified state, speed, and duration.
 * Parameters:
 *   state    - The desired motor state (e.g., FORWARD, REVERSE, STOP)
 *   speed    - Speed percentage of the motor (0-100)
 *   duration - Duration in timer counts for motor operation
 */
void RotateMotorWithTimer(DcMotor_State state, uint8 speed, uint8 duration);

/**
 * Timer callback function prototype specifically for the buzzer timer event.
 */
void Timer_Callback2(void);

/**
 * Function to activate the buzzer for a specific duration using a timer.
 * Parameters:
 *   duration2 - Duration in timer counts for buzzer activation
 */
void Buzzer(uint8 duration2);

#endif /* HOLD_FUNCTION_H_ */
