#include "keypad.h"             // Include keypad driver for key input functionality
#include "lcd.h"               // Include LCD driver for displaying messages
#include <util/delay.h>       // Include delay library for creating time delays
#include "password.h"          // Include password management functions
#include "UART.h"              // Include UART driver for serial communication

#define Size 5                // Define the size of the password (number of digits)

uint8 key;                    // Variable to store the key pressed by the user
uint8 password[Size];         // Array to store the new password
uint8 re_password[Size];      // Array to store the re-entered password for confirmation
uint8 i = 0;                  // Index variable for traversing the password arrays

void Create_Password(void)
{
	// Initialize arrays to 0 to clear any previous password
	for (i = 0; i < Size; i++)
	{
		password[i] = 0;      // Clear the password array
		re_password[i] = 0;   // Clear the re-entered password array
	}

	i = 0;                    // Reset index for password entry
	LCD_clearScreen();       // Clear the LCD screen
	LCD_displayString("Plz Enter Pass:"); // Prompt user to enter a password
	LCD_moveCursor(1, 0);    // Move cursor to the second line

	// Loop to capture password input from the user
	while (1)
	{
		key = KEYPAD_getPressedKey();  // Get the pressed key from the keypad

		if ((key >= 0) && (key <= 9))   // Check if the pressed key is a digit
		{
			if (i < Size)               // Ensure we don't exceed the password size
			{
				password[i] = key;      // Store the key in the password array
				LCD_displayCharacter('*'); // Display an asterisk for privacy
				i++;                     // Increment index
			}
			_delay_ms(500);              // Delay to debounce key press
		}
		else if ((key == '=') && (i == Size)) // Check if '=' is pressed after entering the password
		{
			break;                      // Exit loop when password is fully entered
		}
	}

	_delay_ms(500);                  // Short delay before re-entering the password

	i = 0;                            // Reset index for re-entering password
	LCD_clearScreen();               // Clear the LCD screen
	LCD_displayString("Plz re-Enter the"); // Prompt user to re-enter the same password
	LCD_moveCursor(1, 0);            // Move cursor to the second line
	LCD_displayString("Same Pass: "); // Indicate the user to enter the same password
	LCD_moveCursor(1, 10);           // Move cursor to the correct position

	// Loop to capture re-entered password from the user
	while (1)
	{
		key = KEYPAD_getPressedKey();  // Get the pressed key from the keypad

		if ((key >= 0) && (key <= 9))   // Check if the pressed key is a digit
		{
			if (i < Size)               // Ensure we don't exceed the re-password size
			{
				re_password[i] = key;   // Store the key in the re-password array
				LCD_displayCharacter('*'); // Display an asterisk for privacy
				i++;                     // Increment index
			}
			_delay_ms(500);              // Delay to debounce key press
		}
		else if ((key == '=') && (i == Size)) // Check if '=' is pressed after re-entering the password
		{
			break;                      // Exit loop when password is fully re-entered
		}
	}
}

void send_password(void)
{
	// Send the original password over UART
	for (i = 0; i < Size; i++)
	{
		UART_sendByte(password[i]);    // Send each byte of the password
	}

	// Send the re-entered password over UART
	for (i = 0; i < Size; i++)
	{
		UART_sendByte(re_password[i]);   // Send each byte of the re-entered password
	}
}
