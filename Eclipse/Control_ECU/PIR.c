#include "PIR.h"
#include "gpio.h"

/**
 * @brief Initializes the PIR sensor by setting up the GPIO pin as input.
 *
 * This function configures the specified GPIO pin connected to the PIR sensor
 * as an input pin, enabling it to read the state of the PIR sensor.
 */
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_PORT_ID, PIR_PIN_ID, PIN_INPUT);  // Configure PIR sensor pin as input
}

/**
 * @brief Reads the current state of the PIR sensor.
 *
 * @return uint8 The state of the PIR sensor:
 *         - 1 if motion is detected
 *         - 0 if no motion is detected
 */
uint8 PIR_getState(void)
{
	uint8 value = 0;

	value = GPIO_readPin(PIR_PORT_ID, PIR_PIN_ID);  // Read the PIR sensor pin state

	return value;
}
