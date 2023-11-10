/*
 * HAL_NRF.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Ahmed
 *
 *      RX "Car2"
 *
 *      Tested in 11-11-2023
 *      Version 1
 */


#include "HAL/HAL_NRF.h"



void NRF_ChipSelect (void)
{
	HAL_GPIO_WritePin(NRF_CSNE_PORT, NRF_CSNE_PIN, GPIO_PIN_RESET) ;
}

void NRF_ChipUnSelect (void)
{
	HAL_GPIO_WritePin(NRF_CSNE_PORT, NRF_CSNE_PIN, GPIO_PIN_SET) ;
}


void NRF_ChipEnable (void)
{
	HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_SET) ;
}

void NRF_ChipDisable (void)
{
	HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_RESET) ;
}



/**
 * Brief : Write a Byte to Certain Register
 *
 * Parameters : Register want to write on --> Copy_u8Reg
 * 				Data to be Written 		  --> Copy_u8RegData
 *
 * Synchronous
 * Non reentrant
 * Return : None
 * note :
 *
 */
void NRF_voidWriteByteReg(uint8_t Copy_u8Reg , uint8_t Copy_u8RegData)
{
	uint8_t Local_Buffer[2] ;

	/* Fifth Bit in write Register is always 1 */
	Local_Buffer[0] = (Copy_u8Reg | (1<<5)) ;

	/* Data to be written */
	Local_Buffer[1] =  Copy_u8RegData ;

	/* Chip Select */
	NRF_ChipSelect() ;

	/* Send Data */
	HAL_SPI_Transmit(NRF_SPI1, Local_Buffer,2,1000) ;

	/* Release"Unselect"  device */
	NRF_ChipUnSelect () ;
}

/**
 * Brief : Write Multi Byte Start from Register Address .
 *
 * Parameters : Register want to write on --> Copy_u8Reg
 * 				Data to be Written 		  --> Copy_u8RegData
 * 				Size --> Size of data Sent
 *
 * Synchronous
 * Non reentrant
 * Return : None
 * note :
 *
 */

void NRF_voidWriteMultiByteReg(uint8_t Copy_u8Reg , uint8_t *Data , uint8_t Copy_u8Size)
{
	uint8_t Local_Buffer[1] ;

	/* Fifth Bit in write Register is always 1 */
	Local_Buffer[0] = (Copy_u8Reg | (1<<5)) ;

	/* Chip Select */
	NRF_ChipSelect() ;

	/* Send Data */
	HAL_SPI_Transmit(NRF_SPI1, Local_Buffer, 1    , 1000) ;
	HAL_SPI_Transmit(NRF_SPI1, Data  , Copy_u8Size , 1000) ;

	/* Release"Unselect"  device */
	NRF_ChipUnSelect () ;
}



/**
 * Brief : Read a Byte from Register.
 *
 * Parameters : Register want to Read from --> Copy_u8Reg
 *
 * Synchronous
 * Non reentrant
 * Return : Register Value
 * note :
 *
 */
uint8_t NRF_u8ReadByteReg(uint8_t Copy_u8Reg)
{

	uint8_t Local_Data=0;

	/* Chip Select */
	NRF_ChipSelect() ;

	/* Receive Data */
	HAL_SPI_Transmit(NRF_SPI1,  &Copy_u8Reg , 1 ,100 ) ;
	HAL_SPI_Receive(NRF_SPI1 , &Local_Data, 1 ,100) ;

	/* Release"Unselect"  device */
	NRF_ChipUnSelect () ;

	return Local_Data ;
}

/**
 * Brief : Read Data Multi-Byte From Certain Register .
 *
 * Parameters : Register want to Read from --> Copy_u8Reg
 *				Data of Register 		   --> Data
 *				Size of Data want to read  --> Copy_u8Size
 * Synchronous
 * Non reentrant
 * Return : none
 * note :
 *
 */
void NRF_voidReadMultiByteReg(uint8_t Copy_u8Reg , uint8_t *Data , uint32_t Copy_u8Size)
{

	/* Chip Select */
	NRF_ChipSelect() ;

	/* Receive Data */
	HAL_SPI_Transmit(NRF_SPI1,&Copy_u8Reg ,1,100 ) ;
	HAL_SPI_Receive(NRF_SPI1 , Data ,Copy_u8Size ,1000) ;

	/* Release"Unselect"  device */
	NRF_ChipUnSelect () ;

}


/**
 * Brief : Send Commands using SPI .
 *
 * Parameters : Command to Send  --> Copy_u8Command
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */
void NRF_voidCommandSet (uint8_t Copy_u8Command )
{
	/* Chip Select */
	NRF_ChipSelect() ;

	/* Send Data */
	HAL_SPI_Transmit(NRF_SPI1, &Copy_u8Command, 1 ,100) ;

	/* Release"Unselect"  device */
	NRF_ChipUnSelect () ;
}



/**
 * Brief : Initialize NRF  .
 *
 * Parameters : NONE
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */
void NRF_voidInit ()
{
	/* Disable Chip */
	NRF_ChipDisable () ;
	NRF_ChipUnSelect() ;

	/* Reset All Registers */
	NRF_voidResetNRF(0X00) ;

	/* Config Init */
	NRF_voidWriteByteReg(CONFIG,0x00) ;

	/* EN_AA Init "NO ACK is Used" */
	NRF_voidWriteByteReg(EN_AA,0x00) ;

	/* EN_RXADDR Init "Disable Data pipes for now"  */
	NRF_voidWriteByteReg(EN_RXADDR,0x00) ;

	/* SETUP_AW Init "Width of data pipe Addresses" */
	NRF_voidWriteByteReg(SETUP_AW,0x03) ;	  	  //5 Byte Address Width

	/* SETUP_RETR Init "Auto Transmit time " */
	NRF_voidWriteByteReg(SETUP_RETR,0x00) ;	  //Disable Auto Transmit

	/* RF_CH Init "Channel Number" */
	NRF_voidWriteByteReg(RF_CH,0x00) ;	  	  //Disable for now will be configured later

	/* RF_SETUP Init "BaudRate , Power" */
	NRF_voidWriteByteReg(RF_SETUP,0x0E) ;	   	   //0dBM, 2Mbps

	/* Enable Chip */
	NRF_ChipEnable () ;
	NRF_ChipSelect() ;

}

/**
 * Brief : Configure Transmitter Mode  .
 *
 * Parameters : Address of PTX --> Address
 * 				Channel Number to Sent in --> Copy_u8Channel_Number
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */

void NRF_voidTransmitterMode (uint8_t * Address ,uint8_t Copy_u8Channel_Number )
{
	/* Disable Chip */
	NRF_ChipDisable () ;
	NRF_ChipUnSelect() ;

	/* Select Channel */
	NRF_voidWriteByteReg(RF_CH,Copy_u8Channel_Number) ;

	/* Transmit Address */
	NRF_voidWriteMultiByteReg(TX_ADDR,Address,5) ;

	/* Power up Device and select the device as TX */
	uint8_t Temp ;
	Temp = NRF_u8ReadByteReg(CONFIG);
	Temp = Temp | (1<<1);
	NRF_voidWriteByteReg(CONFIG,Temp) ;

	/* Enable Chip */
	NRF_ChipEnable () ;
	NRF_ChipSelect() ;
}



/**
 * Brief :  Transmit Data  .
 *
 * Parameters : Address of Data to be Transmitted  --> Data
 *
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */
void NRF_voidSendData (uint8_t * Data )
{
	/* Chip Select  */
	NRF_ChipSelect() ;

	/* Chip Enable  */
    NRF_ChipEnable () ;

   uint8_t Temp = W_TX_PAYLOAD ;

   /* Get the Receiver ready , Next Pay-Load is Data */
   HAL_SPI_Transmit(NRF_SPI1, &Temp, 1 , 100) ;

   /* Send Pay-Load "Data" */
   HAL_SPI_Transmit(NRF_SPI1, Data, 32 , 1000) ;

	/* Chip UnSelect  */
	NRF_ChipUnSelect() ;

	/* Delay */
	HAL_Delay(5) ;

	/* Check if TX Buffer is empty or not */
	uint8_t Local_FIFOStatus ;
	Local_FIFOStatus = NRF_u8ReadByteReg(FIFO_STATUS) ;

	// 4 --> TX_EMPTY(1)
	if ( (Local_FIFOStatus & (1<<4)) )
	{
		/* Put Any-Condition To Check */

		/* Flush TX */
		NRF_voidCommandSet(FLUSH_TX);

		/* For Debug */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET) ;

		// Reset FIFO_STATUS
		NRF_voidResetNRF(FIFO_STATUS) ;
	}

}


/**
 * Brief :  Receive Data from NRF  .
 *
 * Parameters : Address of Data to be Received  --> Address
 *				Channel Number to Receive from 	--> Copy_u8Channel_Number
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */

void NRF_voidReceiverMode (uint8_t * Address ,uint8_t Copy_u8Channel_Number )
{

	/* Disable Chip */
	NRF_ChipDisable () ;

	/* Select Channel */
	NRF_voidWriteByteReg(RF_CH,Copy_u8Channel_Number) ;

	/* Activate PIPE1 To receive */
	uint8_t Local_Temp =  NRF_u8ReadByteReg (EN_RXADDR) ;
	Local_Temp |= (1<<1) ; // In Case there is channels already Activated not to change it
	NRF_voidWriteByteReg(EN_RXADDR,Local_Temp) ;

	/* PIPE1 Address Width  */
	NRF_voidWriteMultiByteReg(RX_ADDR_P1,Address,5) ;

	/* Data received is 32 Byte "For PIPE1" */
	NRF_voidWriteByteReg(RX_PW_P1,32) ;

	/* Power up Device and select the device as RX */
	uint8_t Temp ;
	Temp = NRF_u8ReadByteReg(CONFIG);
	Temp = Temp | (1<<1) | (1<<0) ;
	NRF_voidWriteByteReg(CONFIG,Temp) ;

	/* Enable Chip */
	NRF_ChipEnable () ;

}

/**
 * Brief :  Check the state of Certain PIPE   .
 *
 * Parameters : PIPE Number want to Check   --> Copy_u8PipeNum
 *
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */

uint8_t NRF_u8IsDataAvailable (uint8_t Copy_u8PipeNum)
{
	uint8_t Local_Temp = 0 ;
	uint8_t Return_Value ;
	Local_Temp = NRF_u8ReadByteReg(STATUS) ;

	/* Check if Certain PIPE is Empty or Not + Data Ready or Not  */
	if (((Local_Temp)&(1<<6)) && ((Local_Temp)&(Copy_u8PipeNum<<1)) )
	{
		/* To Clear Data Ready Bit */
		NRF_voidWriteByteReg(STATUS,1<<6) ;

		Return_Value = 1 ;

	}
	else Return_Value = 0 ;

	return Return_Value ;

}


/**
 * Brief :  Receive Data From NRF.
 *
 * Parameters : Address to Receive Data in it    --> Data
 *
 *
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note :
 *
 */
void NRF_voidReceiveData (uint8_t * Data )
{
	/* Chip Select  */
	NRF_ChipSelect() ;

	/* Chip Enable  */
    NRF_ChipEnable () ;

   uint8_t Local_Temp = R_RX_PAYLOAD ;

   /* Get the Receiver ready To Read From it  */
   HAL_SPI_Transmit(NRF_SPI1, &Local_Temp, 1 , 100) ;

   /* Receive Pay-Load "Data" */
   HAL_SPI_Receive(NRF_SPI1, Data, 32 , 1000) ;

	/* Chip UnSelect  */
	NRF_ChipUnSelect() ;

	/* Delay */
	HAL_Delay(5) ;

	/* Flush RX FIFO */
	Local_Temp = FLUSH_RX ;
	NRF_voidCommandSet(Local_Temp) ;


}

/**
 * Brief :  Reset NRF .
 *
 * Parameters : Register you want to reset or you want to reset everything-->Copy_u8REG
 * Synchronous
 * Non reentrant
 * Return : NONE
 * note : Any Adress sent execpt 0x07 , 0x17 will reset all the registers automatic.
 *
 */


void NRF_voidResetNRF(uint8_t Copy_u8REG)
{
	if (Copy_u8REG == STATUS)
	{
		NRF_voidWriteByteReg(STATUS, 0x00);
	}

	else if (Copy_u8REG == FIFO_STATUS)
	{
		NRF_voidWriteByteReg(FIFO_STATUS, 0x11);
	}

	else
	{
	NRF_voidWriteByteReg(CONFIG, 0x08);
	NRF_voidWriteByteReg(EN_AA, 0x3F);
	NRF_voidWriteByteReg(EN_RXADDR, 0x03);
	NRF_voidWriteByteReg(SETUP_AW, 0x03);
	NRF_voidWriteByteReg(SETUP_RETR, 0x03);
	NRF_voidWriteByteReg(RF_CH, 0x02);
	NRF_voidWriteByteReg(RF_SETUP, 0x0E);
	NRF_voidWriteByteReg(STATUS, 0x00);
	NRF_voidWriteByteReg(OBSERVE_TX, 0x00);
	NRF_voidWriteByteReg(CD, 0x00);
	uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	NRF_voidWriteMultiByteReg(RX_ADDR_P0, rx_addr_p0_def, 5);
	uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	NRF_voidWriteMultiByteReg(RX_ADDR_P1, rx_addr_p1_def, 5);
	NRF_voidWriteByteReg(RX_ADDR_P2, 0xC3);
	NRF_voidWriteByteReg(RX_ADDR_P3, 0xC4);
	NRF_voidWriteByteReg(RX_ADDR_P4, 0xC5);
	NRF_voidWriteByteReg(RX_ADDR_P5, 0xC6);
	uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	NRF_voidWriteMultiByteReg(TX_ADDR, tx_addr_def, 5);
	NRF_voidWriteByteReg(RX_PW_P0, 0);
	NRF_voidWriteByteReg(RX_PW_P1, 0);
	NRF_voidWriteByteReg(RX_PW_P2, 0);
	NRF_voidWriteByteReg(RX_PW_P3, 0);
	NRF_voidWriteByteReg(RX_PW_P4, 0);
	NRF_voidWriteByteReg(RX_PW_P5, 0);
	NRF_voidWriteByteReg(FIFO_STATUS, 0x11);
	NRF_voidWriteByteReg(DYNPD, 0);
	NRF_voidWriteByteReg(FEATURE, 0);
	}
}
