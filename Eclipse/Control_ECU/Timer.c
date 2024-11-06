#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Function pointer for callback functions for Timer0, Timer1, and Timer2
static void (*g_Timer0_CallbackPtr)(void) = NULL_PTR;
static void (*g_Timer1_CallbackPtr)(void) = NULL_PTR;
static void (*g_Timer2_CallbackPtr)(void) = NULL_PTR;

// ISR for Timer0 Compare Match
ISR(TIMER0_COMP_vect)
{
	if (g_Timer0_CallbackPtr != NULL_PTR)
	{
		(*g_Timer0_CallbackPtr)();  // Call the Timer0 callback function if set
	}
}

// ISR for Timer1 Compare Match
ISR(TIMER1_COMPA_vect)
{
	if (g_Timer1_CallbackPtr != NULL_PTR)
	{
		(*g_Timer1_CallbackPtr)();  // Call the Timer1 callback function if set
	}
}

// ISR for Timer2 Compare Match
ISR(TIMER2_COMP_vect)
{
	if (g_Timer2_CallbackPtr != NULL_PTR)
	{
		(*g_Timer2_CallbackPtr)();  // Call the Timer2 callback function if set
	}
}

// ISR for Timer0 Overflow
ISR(TIMER0_OVF_vect)
{
	if (g_Timer0_CallbackPtr != NULL_PTR)
	{
		(*g_Timer0_CallbackPtr)();  // Call the Timer0 callback function if set
	}
}

// ISR for Timer1 Overflow
ISR(TIMER1_OVF_vect)
{
	if (g_Timer1_CallbackPtr != NULL_PTR)
	{
		(*g_Timer1_CallbackPtr)();  // Call the Timer1 callback function if set
	}
}

// ISR for Timer2 Overflow
ISR(TIMER2_OVF_vect)
{
	if (g_Timer2_CallbackPtr != NULL_PTR)
	{
		(*g_Timer2_CallbackPtr)();  // Call the Timer2 callback function if set
	}
}

/**
 * Initializes the specified timer according to the configuration provided.
 *
 * Config_Ptr Pointer to a configuration structure containing timer settings.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	if (Config_Ptr->timer_mode == NORMAL_MODE)
	{
		switch (Config_Ptr->timer_ID)
		{
		case Timer0:
			TCNT0 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer0
			TCCR0 |= (1<<FOC0); // Set force output compare for Timer0
			TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<TOIE0); // Enable overflow interrupt for Timer0
			break;

		case Timer1:
			TCNT1 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer1
			TCCR1A |= (1<<FOC1A); // Set force output compare for Timer1
			TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<TOIE1); // Enable overflow interrupt for Timer1
			break;

		case Timer2:
			TCNT2 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer2
			TCCR2 |= (1<<FOC2); // Set force output compare for Timer2
			TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<TOIE2); // Enable overflow interrupt for Timer2
			break;
		}
	}
	else if (Config_Ptr->timer_mode == COMPARE_MODE)
	{
		switch (Config_Ptr->timer_ID)
		{
		case Timer0:
			TCNT0 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer0
			OCR0 = (Config_Ptr->timer_compare_MatchValue); // Set compare match value
			TCCR0 |= (1<<FOC0) | (1<<WGM01); // Set force output compare and WGM mode for Timer0
			TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<OCIE0); // Enable compare match interrupt for Timer0
			break;

		case Timer1:
			TCNT1 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer1
			OCR1A = (Config_Ptr->timer_compare_MatchValue); // Set compare match value for Timer1
			TCCR1A |= (1<<FOC1A); // Set force output compare for Timer1
			TCCR1B |= (1<<WGM12); // Set WGM mode for Timer1
			TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<OCIE1A); // Enable compare match interrupt for Timer1
			break;

		case Timer2:
			TCNT2 = (Config_Ptr->timer_InitialValue); // Set initial value for Timer2
			OCR2 = (Config_Ptr->timer_compare_MatchValue); // Set compare match value for Timer2
			TCCR2 |= (1<<FOC2) | (1<<WGM21); // Set force output compare and WGM mode for Timer2
			TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock); // Set clock source
			TIMSK |= (1<<OCIE2); // Enable compare match interrupt for Timer2
			break;
		}
	}
}

/**
 * Deinitializes the specified timer, stopping it and clearing its settings.
 *
 * timer_ID The ID of the timer to deinitialize (0, 1, or 2).
 */
void Timer_deInit(Timer_ID_Type timer_ID)
{
	switch (timer_ID)
	{
	case Timer0:
		TCCR0 = 0x00; // Stop Timer0
		TCNT0 = 0x00; // Reset Timer0 counter
		OCR0 = 0x00; // Reset compare match value for Timer0
		break;

	case Timer1:
		TCCR1A = 0x00; // Stop Timer1
		TCCR1B = 0x00; // Stop Timer1
		TCNT1 = 0x00; // Reset Timer1 counter
		OCR1A = 0x00; // Reset compare match value for Timer1
		TIMSK &= ~ (1<<OCIE1A); // Disable compare match interrupt for Timer1
		break;

	case Timer2:
		TCCR2 = 0x00; // Stop Timer2
		TCNT2 = 0x00; // Reset Timer2 counter
		OCR2 = 0x00; // Reset compare match value for Timer2
		break;
	}
}

/**
 * Sets a callback function for the specified timer.
 *
 * a_ptr Pointer to the callback function to be called on timer events.
 * timer_ID The ID of the timer for which to set the callback.
 */
void Timer_setCallBack(void (*a_ptr)(void), Timer_ID_Type timer_ID)
{
	switch (timer_ID)
	{
	case Timer0:
		g_Timer0_CallbackPtr = a_ptr; // Set callback for Timer0
		break;

	case Timer1:
		g_Timer1_CallbackPtr = a_ptr; // Set callback for Timer1
		break;

	case Timer2:
		g_Timer2_CallbackPtr = a_ptr; // Set callback for Timer2
		break;
	}
}
