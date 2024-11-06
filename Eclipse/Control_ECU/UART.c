#include "UART.h"
#include "avr/io.h"
#include "common_macros.h"

void UART_init(const UART_ConfigType * Config_Ptr)
{
    uint16 ubrr_value = 0; // Variable to hold the calculated UBRR value for baud rate setting

    /* Set U2X to 1 for double transmission speed */
    UCSRA = (1 << U2X);

    /* Enable receiver and transmitter */
    UCSRB = (1 << RXEN) | (1 << TXEN);

    /* Select UCSRC Register (URSEL = 1) */
    UCSRC |= (1 << URSEL);

    /* Set parity mode */
    UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->parity) << 4);

    /* Set stop bit configuration */
    UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->stop_bit) << 3);

    /* Set data bits configuration */
    UCSRC = (UCSRC & 0xF9) | ((Config_Ptr->bit_data) << 1);

    /* Calculate the UBRR register value for the desired baud rate */
    ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

    /* Load the UBRR value into the UBRRH and UBRRL registers */
    /* UBRRH holds the upper 8 bits and UBRRL holds the lower 8 bits */
    UBRRH = ubrr_value >> 8; // Set upper 8 bits of UBRR
    UBRRL = ubrr_value;      // Set lower 8 bits of UBRR
}


void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

