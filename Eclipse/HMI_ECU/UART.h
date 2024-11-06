#ifndef UART_H_
#define UART_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define UART_BaudRateType   uint32  // Define a type for baud rate, using uint32

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	Five_Bit,        // 5 data bits
	Six_Bit,         // 6 data bits
	Seven_Bit,      // 7 data bits
	Eight_Bit,      // 8 data bits
	Nine_Bit = 7    // 9 data bits (not commonly used, mapped to 7 for enumeration)
} UART_BitDataType;

typedef enum
{
	Disabled,       // Parity disabled
	Even = 2,      // Even parity
	Odd             // Odd parity
} UART_ParityType;

typedef enum
{
	One_Bit,        // 1 stop bit
	Two_Bit         // 2 stop bits
} UART_StopBitType;

// Structure to hold UART configuration parameters
typedef struct
{
	UART_BitDataType bit_data;    // Number of data bits
	UART_ParityType parity;        // Parity bit configuration
	UART_StopBitType stop_bit;    // Number of stop bits
	UART_BaudRateType baud_rate;   // Baud rate for UART communication
} UART_ConfigType;

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
