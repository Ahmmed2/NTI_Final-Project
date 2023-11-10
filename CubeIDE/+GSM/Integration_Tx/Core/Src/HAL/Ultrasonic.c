/*
 * Ultrasonic.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Ahmed
 */



#include "HAL/Ultrasonic.h"
#include "HAL/DC_MOTOR.h"


void HAL_voidUltraSonic (uint16_t *UltraSonic_Reading)
{


/* TODO  ****************/

}

uint8_t HAL_UltraSonic_Decision(uint16_t *UltraSonic_Reading)
{

	uint8_t Return_Value = 254 ;

	/* About to Hit */
	if ( (10 <= UltraSonic_Reading[0]) &&  (UltraSonic_Reading[0]<= 20) )
	{
		Return_Value = STOP ;

	}

	/* Close to Hit */
	else if ((20 < UltraSonic_Reading[0]) &&  (UltraSonic_Reading[0]<= 30) )
	{
		Return_Value = SPEED_25 ;

	}



	return Return_Value ;

}
