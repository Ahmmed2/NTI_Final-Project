/*
 * HAL_LCD.c
 *
 *  Created on: Nov 4, 2023
 *      Author: Ahmed
 */

#include "HAL/HAL_LCD.h"


const uint8_t Data[4] = {D7,D6,D5,D4};


#if LCD_TYPE == Four_BIT

void LCD_voidInit(void)
{

#if LCD_TYPE == Eight_BIT

	/* Set Pin Direction*/
	DIO_voidSetPinDirection(GPIOB,PIN0_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(GPIOB,PIN1_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(GPIOB,PIN2_ID, PIN_OUTPUT_ID);
	/*Set Port Direction*/
	DIO_voidSetPortDirection(GPIOB,0b11111111);

	/* Initialization */

	/*Delay 30*/
	HAL_Delay_ms(30);
	/*  Function Set*/
	LCD_voidWriteCommand(FUNCTION_SET);
	/*Delay 2*/
	HAL_Delay_ms(2);
	/* Display on/off*/
	LCD_voidWriteCommand(DisplayON_OFF);
	/*Delay 2ms*/
	HAL_Delay_ms(2);
	/* Clear Display*/
	LCD_voidWriteCommand(CLEAR_DISPLAY);

#endif


#if LCD_TYPE == Four_BIT

	                              /* Initialization */

	/*Delay 50*/
	HAL_Delay(1);

    /* SLCD_EN_Pind Command Function Set*/
	LCD_voidWriteCommand_4L(FUNCTION_SET_H);
	LCD_voidWriteCommand_4L(FUNCTION_SET_L);
	LCD_voidWriteCommand_4L(FUNCTION_SET_LL);
    /*Delay 50us*/
	HAL_Delay(1);

    /*SLCD_EN_Pind Command Display on/off*/
	LCD_voidWriteCommand_4L(DisplayON_OFF_H);
	LCD_voidWriteCommand_4L(DisplayON_OFF_L);
    /*Delay 50us*/
	HAL_Delay(1);

    /*SLCD_EN_Pind Command Clear Display*/
	LCD_voidWriteCommand_4L(CLEAR_DISPLAY_H);
	LCD_voidWriteCommand_4L(CLEAR_DISPLAY_L);
	/*Delay 2ms*/
	HAL_Delay(2);

	/*LCD_EN_Pintry Mode Set */
	LCD_voidWriteCommand_4L(ENTRY_MODE_H);
	LCD_voidWriteCommand_4L(ENTRY_MODE_L);



}
#endif


/* To let the LCD read the data on Pins */
void LCD_voidEnable_4L()
{
	HAL_GPIO_WritePin(CONTROL_PORT,EN,GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(CONTROL_PORT,EN,GPIO_PIN_RESET);
}



/* SLCD_EN_Pind the command Not Data on Data Pins from D7-D4 */
void LCD_voidWriteCommand_4L(uint8_t Copy_u8Value )
{
	uint8_t Local_u8Temp = 0 ;

	HAL_GPIO_WritePin(CONTROL_PORT,RS,GPIO_PIN_RESET);

	Local_u8Temp = Get_bit(Copy_u8Value,3) ;
 	HAL_GPIO_WritePin(DATA_PORT,D7,Local_u8Temp);
 	Local_u8Temp = Get_bit(Copy_u8Value,2) ;
 	HAL_GPIO_WritePin(DATA_PORT,D6,Local_u8Temp);
 	Local_u8Temp = Get_bit(Copy_u8Value,1) ;
 	HAL_GPIO_WritePin(DATA_PORT,D5,Local_u8Temp);
 	Local_u8Temp = Get_bit(Copy_u8Value,0) ;
 	HAL_GPIO_WritePin(DATA_PORT,D4,Local_u8Temp);
 	LCD_voidEnable_4L();



}


/* SLCD_EN_Pind Data not Command on the Data Pins */
void LCD_voidWrite_Data_4L(uint8_t Copy_u8Value )
{


		uint8_t Local_u8Temp,Local_u8Cont = 0,Local_u8LoopCounter=0 ;

		Local_u8Temp = (Copy_u8Value>>4);

		for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<2 ; Local_u8LoopCounter++)
		{
		HAL_GPIO_WritePin(CONTROL_PORT,RS,GPIO_PIN_SET);
		Local_u8Cont = Get_bit(Local_u8Temp,3) ;
		HAL_GPIO_WritePin(DATA_PORT,D7,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,2) ;
		HAL_GPIO_WritePin(DATA_PORT,D6,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,1) ;
		HAL_GPIO_WritePin(DATA_PORT,D5,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,0) ;
		HAL_GPIO_WritePin(DATA_PORT,D4,Local_u8Cont);
		Local_u8Temp = Copy_u8Value ;
		LCD_voidEnable_4L() ;
		}
}



void  LCD_voidSendDATA_4L(uint8_t Copy_u8DATA)
{

	/*SLCD_EN_Pind Data*/
	LCD_voidWrite_Data_4L(Copy_u8DATA);
}


#endif






void LCD_GoToXY(uint8_t Copy_u8X, uint8_t Copy_u8Y)
{
		#if (LCD_Type==Eight_BIT)

		uint8_t LOC_Default = DDRAM_BASE_ADDRESS;

		//FiLCD_RS_Pint Line
		if (Copy_u8_tX==1)
		{
			LOC_Default = FILCD_RS_PinT_LINE_ADDRESS + Copy_uint8_tY ;
			LCD_voidWriteCommand_8L(LOC_Default);
		}

		//Second Line
		else
		{
			LOC_Default = SECOND_LINE_ADDRESS + Copy_uint8_tY ;

			LCD_voidWriteCommand_8L(LOC_Default);
		}


		#elif (LCD_Type==Four_BIT)

		uint8_t LOC_Default = DDRAM_BASE_ADDRESS;
		uint8_t Local_u8Temp = 0 ;

		//FiLCD_RS_Pint Line
		if (Copy_u8X==LINE1)
		{
			LOC_Default= SECOND_LINE_ADDRESS + Copy_u8Y;

			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
		}

		//Second Line
		else if (Copy_u8X==LINE2)
		{
			LOC_Default= SECOND_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);

		}

		//Third Line
		else if (Copy_u8X==LINE3)
		{
			LOC_Default= THIRD_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);

		}

		//Fourth Line
		else if (Copy_u8X==LINE4)
		{
			LOC_Default= FOURTH_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);

		}
#endif
}


/* Write Group of CharacteLCD_RS_Pin on LCD */
void LCD_voidWriteSting(uint8_t *Copy_u8string , uint8_t Copy_u8Line)
{

#if (LCD_Type==Eight_BIT)

	uint8_t Local_uint8_tShift = 0 ;
	while (Copy_uint8_tstring[Local_uint8_tShift]!='\0')
	{
		LCD_GoToXY(Copy_uint8_tLine,Local_uint8_tShift);
		LCD_voidWriteDATA_8L(Copy_uint8_tstring[Local_uint8_tShift]);
		Local_uint8_tShift++;
	}

#elif (LCD_Type==Four_BIT)

	uint8_t Local_u8Shift = 0 ;
	while (Copy_u8string[Local_u8Shift]!='\0')
	{
		LCD_GoToXY(Copy_u8Line,Local_u8Shift);
		LCD_voidSendDATA_4L(Copy_u8string[Local_u8Shift]);
		Local_u8Shift++;
	}

#endif
}


/* Display NumbeLCD_RS_Pin on LCD */
void LCD_voidDisplayNumber(uint32_t Copy_u32DATA)
{

#if LCD_Type==Eight_BIT

	uint8_t  Local_uint32_tCount = 0 , Local_uint32_tCont = 0 ;
	s8  Local_s8Index = 0 ;
	uint32_t Local_uint32_tNumbeLCD_RS_Pin[100] ;

	while (Copy_uint32_tDATA != 0)
	{
		Local_uint32_tCont =  Copy_uint32_tDATA %10 ;
		Copy_uint32_tDATA  =  Copy_uint32_tDATA/10 ;
		Local_uint32_tNumbeLCD_RS_Pin[Local_uint32_tCount] = Local_uint32_tCont ;
		Local_uint32_tCount++ ;
	}

	for (Local_s8Index = (Local_uint32_tCount-1) ; Local_s8Index>=0 ; Local_s8Index--)
	{
		LCD_voidWriteDATA_8L(Local_uint32_tNumbeLCD_RS_Pin[Local_s8Index]+48);
	}


#elif LCD_Type==Four_BIT

	uint32_t  Local_u32Count = 0 ;
	uint8_t   Local_u8Cont = 0 ;
	int8_t    Local_s8Index = 0 ;
	uint32_t  Local_u32Numbers[100] ;
	uint32_t  Local_u8Temp = 0 ;


	if (Copy_u32DATA == Local_u8Temp )
	{
		LCD_voidSendDATA_4L(48) ;
	}

	else
	{

		while (Copy_u32DATA != 0  )
		{
			Local_u8Cont =  Copy_u32DATA %10 ;
			Copy_u32DATA  =  Copy_u32DATA/10 ;
			Local_u32Numbers[Local_u32Count] = Local_u8Cont ;
			Local_u32Count++ ;
		}


		for (Local_s8Index = (Local_u32Count-1) ; Local_s8Index>=0 ; Local_s8Index--)
		{
			LCD_voidSendDATA_4L(Local_u32Numbers[Local_s8Index]+48) ;
		}

}
#endif
}




/* Undefined Character in CGROM , and want to display it */
void LCD_voidWriteSpecialCharacter(uint8_t Copy_u32arr[8],uint8_t Copy_u8Pattern_Number , uint8_t Copy_u8Line , uint8_t Copy_u8Offset )
{
	/* We can write 8 Special Character ,each is 8 Byte */
	/* FiLCD_RS_Pint 8 Byte in the 64 Byte Start at address 64  */

#if LCD_Type==Eight_BIT

	uint8_t Local_Temp = 0 ;
	uint8_t Local_Loop_Counter = 0 ;

	Local_Temp = (CGRAM_BASE_ADDRESS+Copy_uint8_tPattern_Number*8 );
	LCD_voidWriteCommand_8L(Local_Temp);

	for (Local_Loop_Counter =0 ; Local_Loop_Counter < 8 ; Local_Loop_Counter++)
	{
		LCD_voidWriteDATA_8L(Copy_uint32_tarr[Local_Loop_Counter]);
	}

	/* Place To Print Special Character In */
	LCD_GoToXY(Copy_uint8_tLine,Copy_uint8_tOffset);

	/* Pattern Number */
	LCD_voidWriteDATA_8L(Copy_uint8_tPattern_Number);


#elif LCD_Type==Four_BIT

		uint8_t Local_Temp = 0 ;
		uint8_t Local_Loop_Counter = 0 ;
		Local_Temp = (CGRAM_BASE_ADDRESS+Copy_u8Pattern_Number*8 ) >> 4 ;
		LCD_voidWriteCommand_4L(Local_Temp);
		Local_Temp = (CGRAM_BASE_ADDRESS+Copy_u8Pattern_Number*8 );
		LCD_voidWriteCommand_4L(Local_Temp);

		for (Local_Loop_Counter = 0 ; Local_Loop_Counter<8 ; Local_Loop_Counter++)
		{
			LCD_voidSendDATA_4L(Copy_u32arr[Local_Loop_Counter]);
		}

		/* Place To Print Special Character In */
		LCD_GoToXY(Copy_u8Line,Copy_u8Offset);
		/* Pattern Number */
		LCD_voidSendDATA_4L(Copy_u8Pattern_Number);
#endif
}


/* To shift the CuLCD_RS_Pinor Right , Left or Change the Display */
void LCD_voidShift(uint8_t Copy_u8ShifttingDirection)
{

	LCD_voidWriteCommand_4L(SHIFTING_H);
	if (Copy_u8ShifttingDirection == RIGHT)
	{
		LCD_voidWriteCommand_4L(SHIFTINGRIGHT_L);
	}

	else if (Copy_u8ShifttingDirection == LEFT)
	{
		LCD_voidWriteCommand_4L(SHIFTINGLEFT_L);
	}
	else if (Copy_u8ShifttingDirection == DISPLAY_LEFT)
	{
		LCD_voidWriteCommand_4L(SHIFTING_ENTIRE_DISPLAY_L);

	}
	else if (Copy_u8ShifttingDirection == DISPLAY_RIGHT)
	{
		LCD_voidWriteCommand_4L(SHIFTING_ENTIRE_DISPLAY_R);
	}

}


/* To Clear LCD */
void LCD_voidClear()
{
#if LCD_Type==Eight_BIT
	LCD_voidWriteCommand_8L(CLR_LCD);



#elif LCD_Type==Four_BIT
	LCD_voidWriteCommand_4L(CLR_LCD_H);
	LCD_voidWriteCommand_4L(CLR_LCD_L);

#endif
}





/////////////////////////////////////////////////

