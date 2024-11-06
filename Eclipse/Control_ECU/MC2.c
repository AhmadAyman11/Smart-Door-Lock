#include "Function_MC2.h"

int main(void)
{
	uint8 Option;  // Variable to store the option received from UART

	SREG = (1<<7);  // Enable global interrupts by setting the I-bit in SREG

	// Initialize DC Motor and PIR sensor
	DcMotor_Init();
	PIR_init();

	// UART configuration: 8 data bits, no parity, 1 stop bit, 9600 baud rate
	UART_ConfigType uart = {Eight_Bit, Disabled, One_Bit, 9600};
	UART_init(&uart);

	// Timer configuration: Timer1 with a compare value of 3910 and a prescaler of 1024
	Timer_ConfigType timer = {0, 3910, Timer1, PRESCALER_1024, COMPARE_MODE};
	Timer_init(&timer);

	// Write the initial password to storage
	Write_password();

	// Main loop to continuously check for commands received via UART
	while(1)
	{
		Option = UART_recieveByte();  // Receive an option command from UART

		if(Option == open_Door)  // Check if the received command is to open the door
		{
			Open_Door();  // Execute the Open_Door function
		}
		else if(Option == change_password)  // Check if the command is to change the password
		{
			Change_password();  // Execute the Change_password function
			Write_password();   // Write the new password to storage
		}
	}
}
