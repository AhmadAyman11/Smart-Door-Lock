#ifndef FUNCTION_MC1_H_
#define FUNCTION_MC1_H_

#include "lcd.h"
#include "gpio.h"
#include "keypad.h"
#include <util/delay.h>
#include "password.h"
#include "UART.h"
#include <avr/io.h>

#include "Hold_function.h"
#include "option.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
// Define constants for various operation statuses and commands
#define Successful       1           // Indicates a successful operation
#define Failed           0           // Indicates a failed operation
#define Open             2           // Indicates the door is opened
#define Close            3           // Indicates the door is closed
#define Done1            4           // Command for the first done operation
#define Done2            6           // Command for the second done operation
#define Done3            7           // Command for the third done operation
#define Done4            8           // Command indicating sensor status - wait for people
#define Done5            9           // Command indicating sensor status - done with entry
#define Done6            10          // Command for changing password operation
#define Successful_new   11          // Indicates a successful new password verification
#define Failed_new       12          // Indicates a failed new password verification
#define open_Door        13          // Command to open the door
#define change_password  14          // Command to change the password

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
// Function to create a password for the first time
void Create_Password_First_time(void);

// Function to handle the door opening process
void Open_Door_Option(void);

// Function to handle the password change process
void Change_Password_Option(void);

#endif /* FUNCTION_MC1_H_ */
