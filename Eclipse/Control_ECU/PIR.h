#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PIR_PORT_ID    PORTC_ID   // Port ID where the PIR sensor is connected
#define PIR_PIN_ID     PIN2_ID    // Pin ID within the port for the PIR sensor

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the PIR sensor by setting the relevant GPIO pin as input.
 */
void PIR_init(void);

/**
 * @brief Reads and returns the current state of the PIR sensor.
 *
 * @return uint8 Returns 1 if motion is detected, 0 if no motion is detected.
 */
uint8 PIR_getState(void);

#endif /* PIR_H_ */
