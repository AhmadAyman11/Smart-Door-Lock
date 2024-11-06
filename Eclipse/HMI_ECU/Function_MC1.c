#include "Function_MC1.h"

// Global variable declarations
uint8 status;
uint8 Password_flag = 0;     // Flag to check if password creation was successful
uint8 state;                  // State for door operation
uint8 Pass_flag = 0;         // Flag for password validation during door opening
uint8 Sensor;                 // Sensor state variable
uint8 wrong_attempts = 0;     // Counter for wrong password attempts
uint8 pass_flag = 0;         // Flag for password change validation
uint8 wrong_attempts_new = 0; // Counter for new password attempts
uint8 State_new;             // State for new password validation

/**
 * Function to create a password for the first time
 */
void Create_Password_First_time(void)
{
	while (Password_flag == 0) // Loop until password is created successfully
	{
		UART_sendByte(Done1); // Send a request to create a password
		Create_Password();     // Call function to create a password
		send_password();       // Send the created password
		status = UART_recieveByte(); // Wait for status response

		if (status == Successful)
		{
			LCD_clearScreen();
			LCD_displayString("Successful"); // Display success message
			Password_flag = 1;              // Set flag to indicate success
			_delay_ms(500);                 // Delay for user to read message
		}
		else if (status == Failed)
		{
			LCD_clearScreen();
			LCD_displayString("Pass not match"); // Display failure message
			Password_flag = 0;                    // Reset flag for retry
			_delay_ms(500);                       // Delay for user to read message
		}
	}
}

/**
 * Function to handle the door opening process
 */
void Open_Door_Option(void)
{
	UART_sendByte(open_Door); // Send request to open the door
	Pass_flag = 0;            // Reset password flag
	wrong_attempts = 0;       // Reset wrong attempts counter

	while (Pass_flag == 0) // Loop until door is successfully opened
	{
		UART_sendByte(Done2); // Send a request to open the door
		Open_Door();          // Call function to attempt opening the door
		state = UART_recieveByte(); // Get the state response

		if (state == Open)
		{
			Pass_flag = 1;      // Set flag to indicate door is opened
			LCD_clearScreen();
			LCD_displayString("Successful"); // Display success message
			_delay_ms(500);                  // Delay for user to read message
		}
		else if (state == Close)
		{
			wrong_attempts++; // Increment wrong attempts counter
			LCD_clearScreen();
			LCD_displayString("Pass not match"); // Display failure message
			_delay_ms(500);                      // Delay for user to read message
			if (wrong_attempts == MAX_ATTEMPTS) // Check if max attempts exceeded
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2);
				LCD_displayString("System Locked"); // Display lock message
				LCD_moveCursor(1, 1);
				LCD_displayString("Wait For 1 min");
				Wrong_attempt(Duration2); // Call function to handle lockout duration
				wrong_attempts = 0;       // Reset attempts counter
			}
		}
	}

	UART_sendByte(Done3); // Send confirmation for successful door opening

	LCD_clearScreen();
	LCD_displayString("Door Unlocking"); // Indicate the door is unlocking
	Timer_Hold(Duration1); // Hold the timer for the specified duration

	Sensor = UART_recieveByte(); // Wait for sensor response
	while (1)
	{
		if (Sensor == Done4)
		{
			LCD_clearScreen();
			LCD_displayString("Wait For People"); // Indicate to wait for people
			LCD_moveCursor(1, 3);
			LCD_displayString("To Enter");
			while (UART_recieveByte() != Done5); // Wait for confirmation of entry
			Sensor = Done5; // Update sensor state
		}
		else if (Sensor == Done5)
		{
			LCD_clearScreen();
			LCD_displayString("Door Locking"); // Indicate door is locking
			Timer_Hold(Duration1); // Hold the timer for the specified duration
			break; // Exit the loop after locking
		}
	}
}

/**
 * Function to handle the password change process
 */
void Change_Password_Option(void)
{
	UART_sendByte(change_password); // Send request to change password
	pass_flag = 0;                   // Reset password change flag
	wrong_attempts_new = 0;          // Reset wrong attempts counter for new password

	while (pass_flag == 0) // Loop until password change is successful
	{
		UART_sendByte(Done6); // Send a request to check current password
		Check_Password();      // Call function to check the current password
		State_new = UART_recieveByte(); // Get the state response

		if (State_new == Successful_new)
		{
			pass_flag = 1; // Set flag to indicate password change is valid
			LCD_clearScreen();
			LCD_displayString("Successful"); // Display success message
			_delay_ms(500);                  // Delay for user to read message
		}
		else if (State_new == Failed_new)
		{
			wrong_attempts_new++; // Increment wrong attempts counter
			LCD_clearScreen();
			LCD_displayString("Pass not match"); // Display failure message
			_delay_ms(500);                      // Delay for user to read message
			if (wrong_attempts_new == MAX_ATTEMPTS) // Check if max attempts exceeded
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2);
				LCD_displayString("System Locked"); // Display lock message
				LCD_moveCursor(1, 1);
				LCD_displayString("Wait For 1 min");
				Wrong_attempt(Duration2); // Call function to handle lockout duration
				wrong_attempts_new = 0;   // Reset attempts counter
			}
		}
	}

	Password_flag = 0; // Reset password flag for new password creation
	while (Password_flag == 0) // Loop until new password is created successfully
	{
		UART_sendByte(Done1); // Send a request to create a new password
		Create_Password();     // Call function to create a new password
		send_password();       // Send the new password
		status = UART_recieveByte(); // Wait for status response

		if (status == Successful)
		{
			LCD_clearScreen();
			LCD_displayString("Successful"); // Display success message
			Password_flag = 1;              // Set flag to indicate success
			_delay_ms(500);                 // Delay for user to read message
		}
		else if (status == Failed)
		{
			LCD_clearScreen();
			LCD_displayString("Pass not match"); // Display failure message
			Password_flag = 0;                    // Reset flag for retry
			_delay_ms(500);                       // Delay for user to read message
		}
	}
}
