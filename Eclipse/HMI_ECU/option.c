#include "option.h"
#include "lcd.h"
#include "UART.h"
#include <util/delay.h>
#include "keypad.h"

uint8 key;                    // Variable to store the pressed key from the keypad
uint8 Pass[Size];             // Array to store the entered password
uint8 x = 0;                  // Index for the entered password
uint8 pass[Size];             // Array to store the old password for checking

// Function to prompt the user to enter a password to open the door
void Open_Door(void)
{
	for (x = 0; x < Size; x++)
	{
		Pass[x] = 0; // Clear previous entries in the Pass array
	}

	x = 0; // Reset index for entered password
	LCD_clearScreen(); // Clear the LCD screen
	LCD_displayString("Plz Enter Pass:"); // Prompt user to enter the password
	LCD_moveCursor(1, 0); // Move cursor to the next line on the LCD

	while (1) // Infinite loop until a valid password is entered
	{
		key = KEYPAD_getPressedKey(); // Get the key pressed by the user

		if ((key >= 0) && (key <= 9)) // Check if the pressed key is a digit
		{
			if (x < Size) // Check if there is space in the Pass array
			{
				Pass[x] = key; // Store the pressed digit in the Pass array
				LCD_displayCharacter('*'); // Display '*' on the LCD for each digit
				x++; // Increment the index for the next digit
			}
			_delay_ms(500); // Delay for debounce
		}
		else if ((key == '=') && (x == Size)) // Check if '=' is pressed and the password is complete
		{
			break; // Exit the loop if the password entry is complete
		}
	}

	_delay_ms(200); // Delay before sending the password

	// Send the entered password via UART
	for (x = 0; x < Size; x++)
	{
		UART_sendByte(Pass[x]); // Send each digit of the password
	}
}

// Function to prompt the user to enter the old password for verification
void Check_Password(void)
{
	for (x = 0; x < Size; x++)
	{
		pass[x] = 0; // Clear previous entries in the pass array
	}

	x = 0; // Reset index for the entered old password
	LCD_clearScreen(); // Clear the LCD screen
	LCD_displayString("Plz Enter old"); // Prompt user to enter the old password
	LCD_moveCursor(1, 0); // Move cursor to the next line on the LCD
	LCD_displayString("Pass:"); // Display "Pass:" prompt
	LCD_moveCursor(1, 5); // Move cursor to where the user will enter the old password

	while (1) // Infinite loop until a valid old password is entered
	{
		key = KEYPAD_getPressedKey(); // Get the key pressed by the user

		if ((key >= 0) && (key <= 9)) // Check if the pressed key is a digit
		{
			if (x < Size) // Check if there is space in the pass array
			{
				pass[x] = key; // Store the pressed digit in the pass array
				LCD_displayCharacter('*'); // Display '*' on the LCD for each digit
				x++; // Increment the index for the next digit
			}
			_delay_ms(500); // Delay for debounce
		}
		else if ((key == '=') && (x == Size)) // Check if '=' is pressed and the password is complete
		{
			break; // Exit the loop if the password entry is complete
		}
	}

	_delay_ms(200); // Delay before sending the old password

	// Send the old password via UART
	for (x = 0; x < Size; x++)
	{
		UART_sendByte(pass[x]); // Send each digit of the old password
	}
}
