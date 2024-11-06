#ifndef DCMOTOR_H_  // Include guard to prevent multiple inclusions
#define DCMOTOR_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

// Define the port and pin IDs for controlling the DC motor
#define DCMOTOR_IN1_PORT_ID                PORTD_ID  // Port for the first control pin
#define DCMOTOR_IN1_PIN_ID                 PIN6_ID   // Pin ID for the first control pin

#define DCMOTOR_IN2_PORT_ID                PORTD_ID  // Port for the second control pin
#define DCMOTOR_IN2_PIN_ID                 PIN7_ID   // Pin ID for the second control pin

#define PWM_PORT_ID                        PORTB_ID  // Port for the PWM control
#define PWM_PIN_ID                         PIN3_ID   // Pin ID for the PWM signal

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

// Enumeration for the DC motor states
typedef enum
{
	STOP,          // Motor stopped
	CLOCKWISE,     // Motor rotating clockwise
	ANTI_CLOCKWISE  // Motor rotating anti-clockwise
} DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

// Function to initialize the DC motor control pins
void DcMotor_Init(void);

// Function to rotate the DC motor in a specified direction at a given speed
void DcMotor_Rotate(DcMotor_State state, uint8 speed);  // Accepts direction and speed

#endif /* DCMOTOR_H_ */  // End of include guard
