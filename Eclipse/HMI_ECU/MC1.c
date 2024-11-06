#include "Function_MC1.h"

int main(void)
{
	uint8 Option;

	// Enable global interrupts
	SREG = (1 << 7);

	// Initialize peripherals
	LCD_init();
	UART_ConfigType config = {Eight_Bit, Disabled, One_Bit, 9600};
	UART_init(&config);

	// Prompt the user to create a password for the first time
	Create_Password_First_time();

	while (1)
	{
		// Display options for the user
		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("- : Change Pass");

		// Get user input from keypad
		Option = KEYPAD_getPressedKey();

		switch (Option)
		{
		case '+':
			Open_Door_Option();  // Function to open the door
			break;

		case '-':
			Change_Password_Option();  // Function to change the password
			break;

		default:
			// Optionally handle unexpected input
			LCD_clearScreen();
			LCD_displayString("Invalid Option");
			_delay_ms(1000);  // Delay to show the message
			break;
		}
	}
}
