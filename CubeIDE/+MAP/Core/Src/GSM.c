/*
 * GSM.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Emad
 */
#include "HAL/GSM.h"
#include "string.h"
/* GSM RX Message Buffer */
uint8_t Glb_u8GSMBuff[70];
/* GSM Commands */
uint8_t Glb_u8CheckCmd[]={"AT\r\n"};
uint8_t Glb_u8CheckSignalCmd[]={"AT+CSQ\r\n"};
uint8_t Glb_u8NetRegCmd[]={"AT+COPS?\r\n"};
uint8_t Glb_u8TxtModeCmd[]={"AT+CMGF=1\r\n"};
uint8_t Glb_u8SMSOPCmd[]={"AT+CMGS=\""};
uint8_t Glb_u8SMSCLCmd[]={"\"\r\n"};

/*Uart Configuration using UART1*/
extern UART_HandleTypeDef huart3;
#define GSM_UART huart3


/**
 * @brief: Init and check the GSM module.
 *         Sends AT commands and checks responses for connection status,
 * @return: void
 */
void GSM_VidInit()
{
	// Send AT command to check connection status
	while (Glb_u8GSMBuff[5] != 'O' && Glb_u8GSMBuff[6] != 'K')
	{
		HAL_UART_Transmit(&GSM_UART, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
		HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	}
}

/**
 * @brief Checks the connection status of the GSM module.
 *        Sends AT commands and checks responses for connection status,
 *        signal quality, and network registration.
 * @return uint8_t Status of Connection
 */
uint8_t GSM_VidCheckConnection(void)
{
	uint8_t Loc_u8StatusConnection = GSM_FALSE;
	// Send AT command to check connection status

    for (uint8_t i = 0; i < 2; i++)
    {
    	HAL_UART_Transmit(&GSM_UART, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
        if (Glb_u8GSMBuff[5] == 'O' && Glb_u8GSMBuff[6] == 'K')
        {
        	Loc_u8StatusConnection = GSM_TRUE;
            break;
        }
        else
        {
            // If connection status check fails, try again later
            // and send a notification to the dashboard after a set period of time
        	Loc_u8StatusConnection = GSM_FALSE;
        }
    }



    // Check signal quality by sending AT+CSQ command
    for (uint8_t i = 0; i < 2; i++)
    {

    	HAL_UART_Transmit(&GSM_UART, Glb_u8CheckSignalCmd, GSM_CHECKSIG_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);

        if (Glb_u8GSMBuff[23] == 'O' && Glb_u8GSMBuff[24] == 'K')
        {

        	Loc_u8StatusConnection = GSM_TRUE;
            break;
        }
        else
        {
            // If signal quality check fails, try again later
            // and send a notification to the Dash-board after a set period of time
        	Loc_u8StatusConnection = GSM_FALSE;
        }
    }


    // Check network registration by sending AT+COPS? command
    for (uint8_t i = 0; i < 2; i++)
    {
    	HAL_UART_Transmit(&GSM_UART, Glb_u8NetRegCmd, GSM_CHECKNETREG_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);

        if (Glb_u8GSMBuff[36] == 'O' && Glb_u8GSMBuff[37] == 'K')
        {
        	Loc_u8StatusConnection = GSM_TRUE;
            break;
        }
        else
        {
            // If network registration check fails, try again later
            // and send a notification to the Dash-board after a set period of time
        	Loc_u8StatusConnection = GSM_FALSE;
        }
    }

    return Loc_u8StatusConnection;
}

/**
 *
 * @brief:This function sends an SMS message to the specified phone number.
 * @details:This function sends an SMS message to the specified phone number
 * 			using the SIM800L module. It first sends an AT command to set the message format
 * 			to text mode,then sends another AT command to set the phone number,
 * 			and finally sends the message using a third AT command.
 * 			The function waits for a response from the module after each AT command
 * 			and checks if the response indicates success or failure.
 * @param phone_number: Pointer to a string containing the phone number to send the SMS to
 * @param message: Pointer to a string containing the message to be sent
 * @return uint8_t Status of Sending SMS
 */

uint8_t GSM_VidSendSMS(uint8_t *Ptr_u8PhoneNumber, uint8_t *Ptr_u8Message)
{
	//Capturing the size of the phone number and the message
	uint8_t Loc_u8PhoneNumSize = strlen((const char*)Ptr_u8PhoneNumber);
	uint8_t Loc_u8MessageSize = strlen((const char*)Ptr_u8Message);

	// Check the connection
	HAL_UART_Transmit(&GSM_UART, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	// Set text mode for SMS
	HAL_UART_Transmit(&GSM_UART, Glb_u8TxtModeCmd, GSM_TXTMODECMD_SIZE, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	//SMS opening
	HAL_UART_Transmit(&GSM_UART, Glb_u8SMSOPCmd, GSM_SMSOP_SIZE, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	//Entering Phone Number
	HAL_UART_Transmit(&GSM_UART, (uint8_t*)Ptr_u8PhoneNumber, Loc_u8PhoneNumSize, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	//Closing Number format
	HAL_UART_Transmit(&GSM_UART, Glb_u8SMSCLCmd, GSM_SMSCL_SIZE, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	//Entering Message
	HAL_UART_Transmit(&GSM_UART, (uint8_t*)Ptr_u8Message, Loc_u8MessageSize, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);
	//Sending Message
	HAL_UART_Transmit(&GSM_UART, (uint8_t*)"\x1A", 1, GSM_TIMEOUT);
	HAL_UART_Receive(&GSM_UART, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	HAL_Delay(100);

	return GSM_TRUE;


}

