/*
 * Ultrasonic.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Ahmed
 */



#include "HAL/Ultrasonic.h"
#include "HAL/DC_MOTOR.h"

extern UART_HandleTypeDef huart1;;
extern TIM_HandleTypeDef htim2;
uint32_t pMillis;
uint32_t val1_Ultrsonic_1 = 0;
uint32_t val2_Ultrsonic_1 = 0;
uint32_t val1_Ultrsonic_2 = 0;
uint32_t val2_Ultrsonic_2 = 0;
uint32_t val1_Ultrsonic_3 = 0;
uint32_t val2_Ultrsonic_3 = 0;
uint32_t val1_Ultrsonic_4 = 0;
uint32_t val2_Ultrsonic_4 = 0;

uint16_t distance1 = 0;
uint16_t distance2 = 0;
uint16_t distance3 = 0;
uint16_t distance4 = 0;


/*
 * Forward
 * Right
 * Left
 * Backward
 */

UltrasonicSensor ultrasonicSensors[ULTRA_COUNT] = {
    {GPIOA, GPIOA, GPIO_PIN_0, GPIO_PIN_4, &val1_Ultrsonic_1, &val2_Ultrsonic_1, &distance1},
   //{GPIOB, GPIOB, GPIO_PIN_0, GPIO_PIN_1, &val1_Ultrsonic_2, &val2_Ultrsonic_2, &distance2},
   // {GPIOB, GPIOB, GPIO_PIN_13, GPIO_PIN_14, &val1_Ultrsonic_3, &val2_Ultrsonic_3, &distance3},
   // {GPIOA, GPIOB, GPIO_PIN_15, GPIO_PIN_15, &val1_Ultrsonic_4, &val2_Ultrsonic_4, &distance4}
};

void HAL_voidUltraSonicInit(void)
{
    HAL_TIM_Base_Start(&htim2);
}


void HAL_voidUltraSonic (uint16_t *UltraSonic_Reading)
{

	for (int i = 0; i < ULTRA_COUNT; i++)
	{
		UltrasonicSensor sensor = ultrasonicSensors[i];



		HAL_GPIO_WritePin(sensor.trigPort, sensor.trigPin, GPIO_PIN_SET);
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		while (__HAL_TIM_GET_COUNTER(&htim2) < 10);  // wait for 10 us
		HAL_GPIO_WritePin(sensor.trigPort, sensor.trigPin, GPIO_PIN_RESET);

		pMillis = HAL_GetTick();
		while (!(HAL_GPIO_ReadPin(sensor.echoPort, sensor.echoPin)) && pMillis + 10 > HAL_GetTick());
		*(sensor.val1) = __HAL_TIM_GET_COUNTER(&htim2);

		pMillis = HAL_GetTick();
		while ((HAL_GPIO_ReadPin(sensor.echoPort, sensor.echoPin)) && pMillis + 50 > HAL_GetTick());
		*(sensor.val2) = __HAL_TIM_GET_COUNTER(&htim2);


		*(sensor.distance) = (*(sensor.val2) - *(sensor.val1)) * 0.0022 ;
/*		if (*(sensor.distance) > 0 && *(sensor.distance) < 100) {
			*(sensor.distance) = *(sensor.distance) + 1;
		} else if (*(sensor.distance) >= 100 && *(sensor.distance) <= 200) {
			*(sensor.distance) = *(sensor.distance) + 2;
		} else if (*(sensor.distance) >= 200 && *(sensor.distance) <= 300) {
			*(sensor.distance) = *(sensor.distance) + 3;
		} else {
			*(sensor.distance) = *(sensor.distance) + 4;
		}
*/

/*		if ( (*(sensor.distance))>=0 &&  (*(sensor.distance))<40 )
		{
			*sensor.distance = *sensor.distance - 18 ;
		}

		else if ( (*(sensor.distance))>=40 &&  (*(sensor.distance))<65 )
		{
			*sensor.distance = (*sensor.distance - 48) ;
		}
		else if ((*(sensor.distance)) >= 65 &&  (*(sensor.distance))<75 )
		{
			*sensor.distance = *sensor.distance - 65 ;
		}
		else if ((*(sensor.distance)) >= 75 &&  (*(sensor.distance))<95 )
		{
			*sensor.distance = *sensor.distance - 70 ;
		}
		else if ( *(sensor.distance) >= 150 )
		{
			*sensor.distance = *sensor.distance - 135 ;
		}
*/
		// Store the distance in the array
		UltraSonic_Reading[i] = *(sensor.distance);


	}

}

uint8_t HAL_UltraSonic_Decision(uint16_t *UltraSonic_Reading)
{

	uint8_t Return_Value = 254 ;

	/* About to Hit */
	if ( (UltraSonic_Reading[0]<= 20) )
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		Return_Value = STOP ;

	}

	/* Close to Hit */
	else if ((20 < UltraSonic_Reading[0]) &&  (UltraSonic_Reading[0]<= 30) )
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		Return_Value = SPEED_25 ;

	}
	else HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);



	return Return_Value ;

}
