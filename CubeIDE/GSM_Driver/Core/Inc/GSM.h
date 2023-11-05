/*
 * GSM.h
 *
 *  Created on: Nov 5, 2023
 *      Author: moham
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include "stm32f1xx_hal.h"

void GSM_VidInit(void);
uint8_t GSM_VidCheckConnection(void);
uint8_t GSM_VidSendSMS(uint8_t *Ptr_u8PhoneNumber, uint8_t *Ptr_u8Message);

#define GSM_TIMEOUT					100
#define GSM_CHECKCMD_SIZE			4
#define GSM_CHECKSIG_SIZE			8
#define GSM_CHECKNETREG_SIZE		10
#define GSM_TXTMODECMD_SIZE			11
#define GSM_SMSOP_SIZE				9
#define GSM_SMSCL_SIZE				3
#define GSM_BuffSize				20


//uint8_t Glb_u8Cmd4[]={"\"+201061794778\""};
//uint8_t Glb_u8Cmd5[]={"HAAA7"};

#endif /* INC_GSM_H_ */
