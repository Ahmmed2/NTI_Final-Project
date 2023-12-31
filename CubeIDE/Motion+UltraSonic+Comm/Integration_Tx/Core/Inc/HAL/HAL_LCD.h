/*
 * HAL_LCD.h
 *
 *  Created on: Nov 4, 2023
 *      Author: Ahmed
 */

#ifndef INC_HAL_HAL_LCD_H_
#define INC_HAL_HAL_LCD_H_



/***************Include Start ***************/

#include "stm32f1xx_hal.h"


/***************Include END *****************/

/***************Macros Definitions Start *****************/

/*LCD Type */
#define LCD_TYPE	Four_BIT
#define Four_BIT		0
#define Eight_BIT		1

/* Data and Control Port */
#define CONTROL_PORT 			GPIOB
#define DATA_PORT    			GPIOB

/* Control Pins */
#define RS 						GPIO_PIN_9
#define EN						GPIO_PIN_8

/*Data Pins */
#define D7 						GPIO_PIN_7
#define D6 						GPIO_PIN_6
#define D5 						GPIO_PIN_5
#define D4 						GPIO_PIN_4

/* Lines */
#define LINE1 						 1
#define LINE2  						 2
#define LINE3  						 3
#define LINE4  						 4

/* OFFSET */
#define OFFSET0		 0
#define OFFSET1		 1
#define OFFSET2		 2
#define OFFSET3		 3
#define OFFSET4		 4
#define OFFSET5		 5
#define OFFSET6		 6
#define OFFSET7		 7
#define OFFSET8		 8
#define OFFSET9		 9
#define OFFSET10	 10
#define OFFSET11	 11
#define OFFSET12	 12
#define OFFSET13	 13
#define OFFSET14	 14
#define OFFSET15	 15
#define OFFSET16	 16
#define OFFSET17	 17
#define OFFSET18	 18
#define OFFSET19	 19
#define OFFSET20	 20


/* Shifting */
#define RIGHT									0
#define LEFT									1
#define DISPLAY_LEFT							2
#define DISPLAY_RIGHT							3



/* Commands */

/*Clear LCD */
#define CLR_LCD       0x01
#define CLR_LCD_H     0b0000
#define CLR_LCD_L     0b0001

/*Function Set */
#define FUNCTION_SET    0b00111000
#define FUNCTION_SET_H  0b0010
#define FUNCTION_SET_L  0b0010
#define FUNCTION_SET_LL 0b1000

/* Display On / OFF */
#define DisplayON_OFF   0b00001110
#define DisplayON_OFF_H 0b0000
#define DisplayON_OFF_L 0b1111

/* Clear Display */
#define CLEAR_DISPLAY   0b00000001
#define CLEAR_DISPLAY_H 0b0000
#define CLEAR_DISPLAY_L 0b0001

/*Entry Mode */
#define ENTRY_MODE   0b00000110
#define ENTRY_MODE_H 0b0000
#define ENTRY_MODE_L 0b0110

/* Shifting */
#define SHIFTING_H    0b0001

#define SHIFTINGRIGHT_L						0b0100
#define SHIFTINGLEFT_L						0b0000
#define SHIFTING_ENTIRE_DISPLAY_L			0b1000
#define SHIFTING_ENTIRE_DISPLAY_R			0b1100


/* Addresses */

/*To Select Certain Line */
#define DDRAM_BASE_ADDRESS				 0X80
#define FIRST_LINE_ADDRESS				 0X80
#define SECOND_LINE_ADDRESS				 0X80+0X40
#define THIRD_LINE_ADDRESS				 0X80+0X14
#define FOURTH_LINE_ADDRESS				 0X80+0X54

/*For Special Character */
#define CGRAM_BASE_ADDRESS				 0x40
///////////////////////////////////////////////////////////////



/***************Macros Definitions END   *****************/

/***************Macros Functions Definitions Start *****************/

/***************Macros Functions Definitions END   *****************/


/***************Data Type Definitions Start *****************/




/***************Data Type Definitions END   *****************/


/***************Software Interfaces Definitions Start *****************/

void LCD_voidInit(void);

/* 4-BIT LCD */
void LCD_voidWriteCommand_4L(uint8_t Copy_uint8_tValue ) ;
void LCD_voidWrite_Data_4L(uint8_t Copy_uint8_tValue );
void LCD_voidEnable_4L();
void LCD_voidSendDATA_4L(uint8_t Copy_uint8_tDATA);



/* 8-Bit LCD */
void LCD_voidWriteCommand_8L(uint8_t Copy_uint8_tCommand);
void LCD_voidWriteDATA_8L(uint8_t Copy_uint8_tDATA);

void LCD_GoToXY(uint8_t X, uint8_t Y);
void LCD_voidWriteSting(uint8_t *Copy_uint8_tstring ,  uint8_t Copy_uint8_tLine );
void LCD_voidDisplayNumber(uint32_t Copy_uint8_tDATA);
void LCD_voidWriteSpecialCharacter(uint8_t Copy_uint32_tarr[8],uint8_t Copy_uint8_tPattern_Number , uint8_t Copy_uint8_tLine , uint8_t Copy_uint8_tOffset );
void LCD_voidShift(uint8_t Copy_uint8_tShifttingDirection);
void LCD_voidClear();



/* Communicate Through IC-74HC595"Serial To parallel Converter  */
void LCD_voidInit_IC(void) ;
void LCD_voidWriteDataIC_4L(uint8_t Copy_uint8_tCommand)  ;
void LCD_EnableICPulse ()	;
void LCD_voidClearIC_4L () ;


/***************Software Interfaces Definitions END   *****************/





#endif /* INC_HAL_HAL_LCD_H_ */
