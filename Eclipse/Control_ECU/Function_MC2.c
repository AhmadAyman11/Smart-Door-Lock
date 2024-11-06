#include "Function_MC2.h"

// Global variables for password handling and system states
uint8 Pass[Size];
uint8 matching;
uint8 i;
uint8 Sensor = 0;
uint8 wrong_attempts = 0;
uint8 pass[Size];
uint8 Match_new;
uint8 wrong_attempts_new = 0;
uint8 Value[Size];
uint8 Option;
uint8 i;
uint8 password[Size];
uint8 re_password[Size];
uint8 Match;
uint8 Value[Size];




// Function to write a new password to the EEPROM
void Write_password(void)
{
	// Wait for a command indicating readiness to receive password
	while(UART_recieveByte() == Done1)
	{
		// Receive and store the initial password
		for (i = 0; i < Size; i++)
		{
			password[i] = UART_recieveByte();
		}

		// Receive and store the re-entered password
		for (i = 0; i < Size; i++)
		{
			re_password[i] = UART_recieveByte();
		}

		// Check if both entered passwords match
		Match = 1;
		for (i = 0; i < Size; i++)
		{
			if (password[i] != re_password[i])
			{
				Match = 0;
				break;
			}
		}

		// Notify the result of password matching
		if (Match == 1)
		{
			UART_sendByte(Successful);
			break;
		}
		else
		{
			UART_sendByte(Failed);
		}
	}

	// Store the password in EEPROM
	for(i = 0; i < Size; i++)
	{
		EEPROM_writeByte(i, password[i]);
		_delay_ms(10);  // Delay for EEPROM write operation
	}

	// Read back the password from EEPROM to confirm it is stored correctly
	for(i = 0; i < Size; i++)
	{
		EEPROM_readByte(i, &Value[i]);
		_delay_ms(10);  // Delay for EEPROM read operation
	}
}


// Function to open the door if the correct password is provided
void Open_Door(void)
{
	Sensor = PIR_getState();  // Get initial state of the PIR sensor
	wrong_attempts = 0;       // Reset wrong attempts counter

	// Wait for command to begin password entry
	while(UART_recieveByte() == Done2)
	{
		// Receive the entered password
		for (i = 0; i < Size; i++)
		{
			Pass[i] = UART_recieveByte();
		}

		// Check if entered password matches the stored password
		matching = 1;
		for (i = 0; i < Size; i++)
		{
			if (Pass[i] != Value[i])
			{
				matching = 0;
				break;
			}
		}

		// If password matches, open the door; otherwise, increment wrong attempts counter
		if (matching)
		{
			UART_sendByte(Open);
			break;
		}
		else
		{
			UART_sendByte(Close);
			wrong_attempts++;
			if (wrong_attempts == MAX_ATTEMPTS)
			{
				_delay_ms(500);
				Buzzer(Duration2);  // Sound buzzer on exceeding maximum attempts
				wrong_attempts = 0;
			}
		}
	}

	// Wait for door closure signal
	while (UART_recieveByte() == Done3)
	{
		RotateMotorWithTimer(CLOCKWISE, Speed, Duration1);  // Rotate motor to open door
		Sensor = PIR_getState();

		// Monitor PIR sensor state while door is open
		while(1)
		{
			Sensor = PIR_getState();

			if (Sensor == 1)  // If motion is detected
			{
				UART_sendByte(Done4);  // Send signal for motion detected
				while (PIR_getState() == 1);

				UART_sendByte(Done5);  // Send signal for no motion
				RotateMotorWithTimer(ANTI_CLOCKWISE, Speed, Duration1);  // Close door
				Sensor = 0;
				break;
			}
			else if (Sensor == 0)  // If no motion is detected
			{
				UART_sendByte(Done5);  // Send signal for no motion
				RotateMotorWithTimer(ANTI_CLOCKWISE, Speed, Duration1);  // Close door
			}
			break;
		}
		break;
	}
}

// Function to change the password if the current password is correctly provided
void Change_password(void)
{
	wrong_attempts_new = 0; // Reset new wrong attempts counter

	// Wait for command to initiate password change
	while (UART_recieveByte() == Done6)
	{
		// Receive the current password for verification
		for (i = 0; i < Size; i++)
		{
			pass[i] = UART_recieveByte();
		}

		// Verify if the entered password matches the stored password
		Match_new = 1;
		for (i = 0; i < Size; i++)
		{
			if (pass[i] != Value[i])
			{
				Match_new = 0;
				break;
			}
		}

		// If password is correct, allow password change; otherwise, track wrong attempts
		if (Match_new)
		{
			UART_sendByte(Successful_new);
			break;
		}
		else
		{
			UART_sendByte(Failed_new);
			wrong_attempts_new++;
			if (wrong_attempts_new == MAX_ATTEMPTS)
			{
				_delay_ms(500);
				Buzzer(Duration2);  // Activate buzzer on maximum failed attempts
				wrong_attempts_new = 0;
			}
		}
	}
}
