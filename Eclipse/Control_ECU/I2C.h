#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

#define TWI_AddressType    uint8
#define CPU_UL             8000000

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/**
 * Enumeration for TWI (I2C) baud rates, represented in Hz.
 * Each mode defines a standard baud rate as per TWI/I2C specifications.
 */
typedef enum
{
	Normal_Mode = 100000,       // Standard mode: 100 kHz
	Fast_Mode = 400000,         // Fast mode: 400 kHz
	Fast_Mode_Plus = 1000000,   // Fast mode plus: 1 MHz
	High_Speed_Mode = 3400000   // High-speed mode: 3.4 MHz
} TWI_BaudRateType;

/**
 * Configuration structure for TWI (I2C) initialization settings.
 * Contains the device address and the bit rate for TWI communication.
 */
typedef struct
{
	TWI_AddressType address;     // Device address on the TWI bus
	TWI_BaudRateType bit_rate;   // Communication speed in Hz (from TWI_BaudRateType)
} TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Initializes the TWI module with specified configurations.
 * Parameters:
 *   Config_Ptr - Pointer to a configuration structure containing the device address and bit rate
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);

/**
 * Sends a START condition on the TWI bus.
 */
void TWI_start(void);

/**
 * Sends a STOP condition on the TWI bus, ending the current transaction.
 */
void TWI_stop(void);

/**
 * Sends a byte of data on the TWI bus.
 * Parameters:
 *   data - Byte of data to be transmitted
 */
void TWI_writeByte(uint8 data);

/**
 * Reads a byte of data from the TWI bus and sends an ACK signal.
 * Returns:
 *   The byte of data read from the bus
 */
uint8 TWI_readByteWithACK(void);

/**
 * Reads a byte of data from the TWI bus and sends a NACK signal.
 * Returns:
 *   The byte of data read from the bus
 */
uint8 TWI_readByteWithNACK(void);

/**
 * Retrieves the current status of the TWI module.
 * Returns:
 *   The status code representing the TWI bus state
 */
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
