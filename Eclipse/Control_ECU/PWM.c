#include "PWM.h"
#include "common_macros.h"
#include <avr/io.h>
#include "gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
    TCNT0 = 0;                // Initialize counter
    OCR0 = duty_cycle;        // Set duty cycle
    GPIO_setupPinDirection(PWM_PORT_ID, PWM_PIN_ID, PIN_OUTPUT); // Set pin as output
    SET_BIT(TCCR0, WGM01);    // Set fast PWM mode
    SET_BIT(TCCR0, WGM00);    // Set fast PWM mode
    SET_BIT(TCCR0, CS01);     // Set prescaler to 64
    SET_BIT(TCCR0, CS00);     // Set prescaler to 64
    SET_BIT(TCCR0, COM01);    // Clear OC0 on compare match
}
