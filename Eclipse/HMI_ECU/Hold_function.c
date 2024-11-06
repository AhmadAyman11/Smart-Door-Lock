#include "Hold_function.h"
#include "lcd.h"        // Include LCD header for display functions
#include "Timer.h"      // Include timer header for timer functionalities

// Global counters for timer callbacks
uint8 counter1 = 0;
uint8 counter2 = 0;

// Callback function for Timer1 that increments counter1
void Timer_Callback1(void)
{
	counter1++;
}

// Function to hold for a specified duration using Timer1
void Timer_Hold(uint8 duration1)
{
	// Configure Timer1 for compare mode with the desired initial value and prescaler
	Timer_ConfigType timer_config = {0, 3910, Timer1, PRESCALER_1024, COMPARE_MODE};
	Timer_init(&timer_config);              // Initialize the timer
	Timer_setCallBack(Timer_Callback1, Timer1); // Set the callback for Timer1

	// Wait until counter1 reaches the specified duration
	while (counter1 < duration1) {}

	Timer_deInit(Timer1);                   // De-initialize Timer1
	counter1 = 0;                           // Reset counter1
}

// Callback function for Timer2 that increments counter2
void Timer_Callback2(void)
{
	counter2++;
}

// Function to handle wrong attempts with a specified duration
void Wrong_attempt(uint8 duration2)
{
	// Configure Timer1 for compare mode with the desired initial value and prescaler
	Timer_ConfigType timer_config = {0, 3910, Timer1, PRESCALER_1024, COMPARE_MODE};
	Timer_init(&timer_config);              // Initialize the timer
	Timer_setCallBack(Timer_Callback2, Timer1); // Set the callback for Timer2

	// Wait until counter2 reaches the specified duration
	while (counter2 < duration2) {}

	Timer_deInit(Timer1);                   // De-initialize Timer1
	counter2 = 0;                           // Reset counter2
}
