#include "DCmotor.h"          // Include the header for DC motor functionality
#include "common_macros.h"    // Include common macro definitions
#include "gpio.h"             // Include the GPIO (General Purpose Input/Output) header
#include "PWM.h"              // Include the PWM (Pulse Width Modulation) header

// Function to initialize the DC motor pins
void DcMotor_Init(void)
{
	// Set the direction of the motor control pins to output
	GPIO_setupPinDirection(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, PIN_OUTPUT);

	// Initialize both pins to low (motor off)
	GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);
}

// Function to rotate the DC motor in a specified direction at a given speed
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	// Ensure the speed is clamped to the range 0 to 100
	if (speed > 100)
	{
		speed = 100;  // Limit speed to maximum of 100%
	}

	// Control the direction of the motor based on the state
	switch (state)
	{
	case CLOCKWISE:
		// Set pins for clockwise rotation
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;

	case ANTI_CLOCKWISE:
		// Set pins for anti-clockwise rotation
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;

	case STOP:
	default:
		// Stop the motor by setting both pins to low
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	}

	// Control the speed using PWM based on the speed parameter
	switch (speed)
	{
	case 100:
		PWM_Timer0_Start(DUTY_CYCLE_100);  // Set PWM for full speed
		break;
	case 75:
		PWM_Timer0_Start(DUTY_CYCLE_75);   // Set PWM for 75% speed
		break;
	case 50:
		PWM_Timer0_Start(DUTY_CYCLE_50);   // Set PWM for 50% speed
		break;
	case 25:
		PWM_Timer0_Start(DUTY_CYCLE_25);   // Set PWM for 25% speed
		break;
	default:
		PWM_Timer0_Start(DUTY_CYCLE_0);    // Set PWM to 0% speed (motor off)
		break;
	}
}
