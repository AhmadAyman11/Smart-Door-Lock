#ifndef PWM_H_  // Include guard to prevent multiple inclusions
#define PWM_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

// Define duty cycle values for PWM
#define DUTY_CYCLE_100   255  // 100% duty cycle (fully on)
#define DUTY_CYCLE_75    192  // 75% duty cycle
#define DUTY_CYCLE_50    128  // 50% duty cycle
#define DUTY_CYCLE_25    64   // 25% duty cycle
#define DUTY_CYCLE_0     0    // 0% duty cycle (fully off)

// Define the port and pin for PWM signal
#define PWM_PORT_ID      PORTB_ID  // Port where the PWM signal is generated
#define PWM_PIN_ID       PIN3_ID    // Pin ID for the PWM output

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

// Function to start the PWM signal on the specified pin with the given duty cycle
void PWM_Timer0_Start(uint8 duty_cycle);  // Accepts a duty cycle value (0-255)

#endif /* PWM_H_ */  // End of include guard
