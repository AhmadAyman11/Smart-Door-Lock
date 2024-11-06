#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

// Enum to define the available timer IDs
typedef enum
{
	Timer0,
	Timer1,
	Timer2
} Timer_ID_Type;

// Enum to define the clock prescaler options for the timers
typedef enum
{
	NO_CLOCK,
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024
} Timer_ClockType;

// Enum to define the operating modes of the timers
typedef enum
{
	NORMAL_MODE,
	COMPARE_MODE
} Timer_ModeType;

// Structure to hold configuration parameters for the timer
typedef struct
{
	uint16 timer_InitialValue;          // Initial value to start the timer from
	uint16 timer_compare_MatchValue;    // Compare match value (used in compare mode only)
	Timer_ID_Type timer_ID;              // Identifier for which timer to configure
	Timer_ClockType timer_clock;         // Clock source for the timer
	Timer_ModeType timer_mode;           // Operating mode of the timer
} Timer_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

// Function to initialize the timer with the specified configuration
void Timer_init(const Timer_ConfigType * Config_Ptr);

// Function to deinitialize the specified timer, stopping it and clearing its settings
void Timer_deInit(Timer_ID_Type timer_type);

// Function to set a callback function for the specified timer
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* TIMER_H_ */
