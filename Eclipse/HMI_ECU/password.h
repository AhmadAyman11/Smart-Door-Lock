#ifndef PASSWORD_H_              // Header guard to prevent multiple inclusions
#define PASSWORD_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Size 5                    // Define the size of the password (number of digits)

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Create_Password(void);       // Prototype for function to create a new password

void send_password(void);          // Prototype for function to send the password over UART

#endif /* PASSWORD_H_ */          // End of header guard
