#ifndef FUNCTION_MC2_H_
#define FUNCTION_MC2_H_

#include "UART.h"
#include "external_eeprom.h"
#include "DCmotor.h"
#include "Timer.h"
#include "PIR.h"
#include "std_types.h"
#include "BUZZER.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Hold_function.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define Size             5     // Size of the password array
#define Successful       1     // Status code for successful password match
#define Failed           0     // Status code for failed password match
#define Open             2     // Command to indicate door should open
#define Close            3     // Command to indicate door should close
#define Done1            4     // Command indicating the end of password setup phase
#define Done2            6     // Command to begin door operation
#define Done3            7     // Command to close the door after successful verification
#define Done4            8     // Signal to indicate motion detected by PIR
#define Done5            9     // Signal to indicate no motion detected
#define Done6            10    // Command to initiate password change
#define Successful_new   11    // Status code for successful new password setup
#define Failed_new       12    // Status code for failed new password setup
#define open_Door        13    // Command identifier for opening the door
#define change_password  14    // Command identifier for changing the password

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * Function to open the door if the correct password is provided.
 * Communicates with UART to receive the password and checks it against stored data.
 */
void Open_Door(void);

/**
 * Function to change the password if the current password is correctly provided.
 * Validates current password and allows for setting a new one if matched.
 */
void Change_password(void);

/**
 * Function to write a new password to EEPROM storage.
 * Handles password setup and verification process.
 */
void Write_password(void);

#endif /* FUNCTION_MC2_H_ */
