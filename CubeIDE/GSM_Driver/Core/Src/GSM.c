/*
 * GSM.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Emad
 */
#include "GSM.h"
#include "string.h"
//GSM RX Message Buffer
uint8_t Glb_u8GSMBuff[10];
// GSM Commands
uint8_t Glb_u8CheckCmd[]={"AT\r\n"};
uint8_t Glb_u8CheckSignalCmd[]={"AT+CSQ\r\n"};
uint8_t Glb_u8NetRegCmd[]={"AT+COPS?\r\n"};
uint8_t Glb_u8TxtModeCmd[]={"AT+CMGF=1\r\n"};
uint8_t Glb_u8SMSOPCmd[]={"AT+CMGS=\""};
uint8_t Glb_u8SMSCLCmd[]={"\"\r\n"};

extern UART_HandleTypeDef huart3;
/**
 * @brief: Init (Actually Does nothing) and check the SIM800L module.
 *         Sends AT commands and checks responses for connection status,
 * @return: void
 */
void GSM_VidInit()
{
	// Send AT command to check connection status
	for (uint8_t i = 0; i < 2; i++)
	{
	HAL_UART_Transmit(&huart3, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
	HAL_UART_Receive(&huart3, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
	}
}


//Function Not Yet Completed
uint8_t GSM_VidCheckConnection(void)
{
	uint8_t Loc_u8StatusConnection = 0;
	// Send AT command to check connection status

    for (uint8_t i = 0; i < 2; i++)
    {
    	HAL_UART_Transmit(&huart3, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&huart3, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
        if (Glb_u8GSMBuff[0] == 'O' && Glb_u8GSMBuff[1] == 'K')
        {
        	Loc_u8StatusConnection = 0;
            break;
        }
        else
        {
            // If connection status check fails, try again later
            // and send a notification to the dashboard after a set period of time
        	Loc_u8StatusConnection = 1;
        }
    }

    // Check signal quality by sending AT+CSQ command
    for (uint8_t i = 0; i < 2; i++)
    {

    	HAL_UART_Transmit(&huart3, Glb_u8CheckSignalCmd, GSM_CHECKSIG_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&huart3, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
        if (Glb_u8GSMBuff[0] == 'O' && Glb_u8GSMBuff[1] == 'K')
        {
        	Loc_u8StatusConnection = 0;
            break;
        }
        else
        {
            // If signal quality check fails, try again later
            // and send a notification to the Dash-board after a set period of time
        	Loc_u8StatusConnection = 1;
        }
    }

    // Check network registration by sending AT+COPS? command
    for (uint8_t i = 0; i < 2; i++)
    {
    	HAL_UART_Transmit(&huart3, Glb_u8NetRegCmd, GSM_CHECKNETREG_SIZE, GSM_TIMEOUT);
    	HAL_UART_Receive(&huart3, Glb_u8GSMBuff, GSM_BuffSize, GSM_TIMEOUT);
        if (Glb_u8GSMBuff[0] == 'O' && Glb_u8GSMBuff[1] == 'K')
        {
        	Loc_u8StatusConnection = 0;
            break;
        }
        else
        {
            // If network registration check fails, try again later
            // and send a notification to the Dash-board after a set period of time
        	Loc_u8StatusConnection = 1;
        }
    }
    return Loc_u8StatusConnection;
}

/**
 *
 * @brief: This function sends an SMS message to the specified phone number.
 * @details: This function sends an SMS message to the specified phone number
 * using the SIM800L module. It first sends an AT command to set the message format
 * to text mode,then sends another AT command to set the phone number,
 * and finally sends the message using a third AT command.
 * The function waits for a response from the module after each AT command
 * and checks if the response indicates success or failure.
 * @param phone_number: pointer to a string containing the phone number to send the SMS to
 * @param message: pointer to a string containing the message to be sent
 * @return uint8_t Status of Sending SMS
 */

uint8_t GSM_VidSendSMS(uint8_t *Ptr_u8PhoneNumber, uint8_t *Ptr_u8Message)
{
	uint8_t Loc_u8PhoneNumSize = strlen(Ptr_u8PhoneNumber);
	uint8_t Loc_u8MessageSize = strlen(Ptr_u8Message);


		// Set text mode for SMS

	    HAL_UART_Transmit(&huart3, Glb_u8CheckCmd, GSM_CHECKCMD_SIZE, GSM_TIMEOUT);
	    HAL_Delay(200);
	  	HAL_UART_Transmit(&huart3, Glb_u8TxtModeCmd, GSM_TXTMODECMD_SIZE, GSM_TIMEOUT);
	  	HAL_Delay(200);
	  	HAL_UART_Transmit(&huart3, Glb_u8SMSOPCmd, GSM_SMSOP_SIZE, GSM_TIMEOUT);
	  	HAL_Delay(200);
		HAL_UART_Transmit(&huart3, (uint8_t*)Ptr_u8PhoneNumber, Loc_u8PhoneNumSize, GSM_TIMEOUT);
		HAL_Delay(200);
		HAL_UART_Transmit(&huart3, Glb_u8SMSCLCmd, GSM_SMSCL_SIZE, GSM_TIMEOUT);
		HAL_Delay(200);
		HAL_UART_Transmit(&huart3, (uint8_t*)Ptr_u8Message, Loc_u8MessageSize, GSM_TIMEOUT);
		HAL_Delay(200);
		HAL_UART_Transmit(&huart3, (uint8_t*)"\x1A", 1, GSM_TIMEOUT);
		HAL_Delay(200);

		return 1;

}

