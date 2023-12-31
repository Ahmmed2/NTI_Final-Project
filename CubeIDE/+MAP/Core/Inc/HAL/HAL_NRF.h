/*
 * HAL_NRF.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Ahmed
 */

#ifndef INC_HAL_HAL_NRF_H_
#define INC_HAL_HAL_NRF_H_


/***************Include Start ***************/

#include "stm32f1xx_hal.h"
#include "string.h"
#include "strings.h"

/***************Include END *****************/

/***************Macros Definitions Start *****************/

/* Chip Enable Configuration */
#define NRF_CE_PORT						GPIOA
#define NRF_CE_PIN						GPIO_PIN_1

/* Chip Select Configuration */
#define NRF_CSNE_PORT					GPIOA
#define NRF_CSNE_PIN					GPIO_PIN_2


/* Register map of NRF */
#define CONFIG      					0x00
#define EN_AA      						0x01
#define EN_RXADDR   					0x02
#define SETUP_AW   					    0x03
#define SETUP_RETR  					0x04
#define RF_CH       					0x05
#define RF_SETUP    					0x06
#define STATUS                          0x07
#define OBSERVE_TX                      0x08
#define CD                              0x09
#define RX_ADDR_P0                      0x0A
#define RX_ADDR_P1                      0x0B
#define RX_ADDR_P2                      0x0C
#define RX_ADDR_P3                      0x0D
#define RX_ADDR_P4                      0x0E
#define RX_ADDR_P5                      0x0F
#define TX_ADDR                         0x10
#define RX_PW_P0                        0x11
#define RX_PW_P1                        0x12
#define RX_PW_P2                        0x13
#define RX_PW_P3                        0x14
#define RX_PW_P4                        0x15
#define RX_PW_P5                        0x16
#define FIFO_STATUS                     0x17
#define DYNPD	                        0x1C
#define FEATURE	                        0x1D



/* Command Set of NRF */
#define R_REGISTER                      0x00
#define W_REGISTER                      0x20
#define REGISTER_MASK                   0x1F
#define ACTIVATE                        0x50
#define R_RX_PL_WID                     0x60
#define R_RX_PAYLOAD                    0x61
#define W_TX_PAYLOAD                    0xA0
#define W_ACK_PAYLOAD                   0xA8
#define FLUSH_TX                        0xE1
#define FLUSH_RX                        0xE2
#define REUSE_TX_PL                     0xE3
#define NOP                             0xFF

/* SPI1 Handler */
#define NRF_SPI1						&hspi1


/* Data Defines */

///////////////////////////////////

/* Indication */
#define INDICATION_SUDDEN_BRAKE				1
#define	INDICATION_TRAFFIC					2
#define	INDICATION_OBSTACLE					3
#define INDICATION_NORMAL					4
///////////////////////////////////

/* Numbers Indication */

#define NRF_NUMBERS_EXIST		0
#define NRF_NUMBERS_NOT_EXIST	1

/***************Macros Definitions END   *****************/

/***************Macros Functions Definitions Start *****************/

/***************Macros Functions Definitions END   *****************/


/***************Data Type Definitions Start *****************/

/* SPI1 Handler */
extern SPI_HandleTypeDef hspi1;

/* Type of Data to be sent */
typedef struct
{
	uint8_t Speed    		;
	uint8_t Direction       ;
	uint8_t Distance     	;
	uint8_t Indication      ;

}DataTransfer_t;


/* System Modes */
#define 	Comm_Mode				0
#define 	Dominant_Mode			1
#define 	Emergency_Mode			2
#define		Stationary_Mode			3
#define		Normal_Mode				4


/***************Data Type Definitions END   *****************/


/***************Software Interfaces Definitions Start *****************/

void NRF_ChipSelect (void) 									  							;
void NRF_ChipUnSelect (void) 								  							;
void NRF_ChipEnable (void) 									  							;
void NRF_ChipDisable (void)									  							;

/* Write (Multi) Byte  */
void NRF_voidWriteByteReg(uint8_t Reg , uint8_t Data)									;
void NRF_voidWriteMultiByteReg(uint8_t Reg , uint8_t *Data , uint8_t Size)  			;

/* Read (Multi) Byte  */
uint8_t NRF_u8ReadByteReg(uint8_t Reg )													;
void NRF_voidReadMultiByteReg(uint8_t Reg , uint8_t *Data , uint32_t Size)				;

/* System Configuration */
void NRF_voidCommandSet (uint8_t Copy_u8Command )										;
void NRF_voidInit(void) 																;

/* Transmit Data */
void NRF_voidTransmitterMode (uint8_t * Address ,uint8_t Copy_u8Channel_Number ) 		;
void NRF_voidSendData (uint8_t *Data,uint8_t Copy_u8SizeinByte,uint8_t Copy_u8CharFlag)	;
uint8_t HAL_NRF_Send_Number(uint32_t Copy_u32Number , uint8_t Copy_u8Number_Index)  	;

/* Receive Data */
void NRF_voidReceiverMode (uint8_t * Address ,uint8_t Copy_u8Channel_Number )			;
uint8_t NRF_u8IsDataAvailable (uint8_t Copy_u8PipeNum)									;
void NRF_voidReceiveData (uint8_t * Data )												;

/* Reset NRF */
void NRF_voidResetNRF(uint8_t Copy_u8REG)												;


/***************Software Interfaces Definitions END   *****************/




#endif /* INC_HAL_HAL_NRF_H_ */




