#include "Hold_function.h"

#include "DCmotor.h"
#include "Timer.h"
#include "PIR.h"
#include "BUZZER.h"

// Global counters to keep track of the timer counts
uint8 counter1 = 0;
uint8 counter2 = 0;

// Timer callback function for motor rotation timer
void Timer_Callback1(void)
{
	counter1++; // Increment counter1 each time the callback is triggered
}

/**
 * Function to rotate the motor with a specified speed and duration.
 * Parameters:
 *   state    - Motor state (e.g., FORWARD, REVERSE, STOP)
 *   speed    - Motor speed percentage (0-100)
 *   duration1 - Duration in timer counts for which the motor should rotate
 */
void RotateMotorWithTimer(DcMotor_State state, uint8 speed, uint8 duration1)
{
	// Start motor rotation with the specified state and speed
	DcMotor_Rotate(state, speed);

	// Configure the timer with specified parameters
	Timer_ConfigType timer_config = {0, 3910, Timer1, PRESCALER_1024, COMPARE_MODE};
	Timer_init(&timer_config); // Initialize the timer
	Timer_setCallBack(Timer_Callback1, Timer1); // Set the callback function for the timer

	// Wait until the timer has counted to the specified duration
	while (counter1 < Duration1){};

	// Stop the motor after the duration has elapsed
	DcMotor_Rotate(STOP, 0);

	// Deinitialize the timer and reset the counter for future use
	Timer_deInit(Timer1);
	counter1 = 0;
}

// Timer callback function for buzzer timer
void Timer_Callback2(void)
{
	counter2++; // Increment counter2 each time the callback is triggered
}

/**
 * Function to activate the buzzer for a specified duration.
 * Parameters:
 *   duration2 - Duration in timer counts for which the buzzer should be active
 */
void Buzzer(uint8 duration2)
{
	// Turn the buzzer on
	Buzzer_on();

	// Configure the timer with specified parameters
	Timer_ConfigType timer_config = {0, 3910, Timer1, PRESCALER_1024, COMPARE_MODE};
	Timer_init(&timer_config); // Initialize the timer
	Timer_setCallBack(Timer_Callback2, Timer1); // Set the callback function for the timer

	// Wait until the timer has counted to the specified duration
	while (counter2 < Duration2){};

	// Turn the buzzer off after the duration has elapsed
	Buzzer_off();

	// Deinitialize the timer and reset the counter for future use
	Timer_deInit(Timer1);
	counter2 = 0;
}
