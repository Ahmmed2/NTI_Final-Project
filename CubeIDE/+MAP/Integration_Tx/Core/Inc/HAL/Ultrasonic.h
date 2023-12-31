/*
 * Ultrasonic.h
 *
 *  Created on: Nov 9, 2023
 *      Author: Ahmed
 */

#ifndef INC_HAL_ULTRASONIC_H_
#define INC_HAL_ULTRASONIC_H_

#include "stm32f1xx_hal.h"

/* Pins */

#define TRIG_PIN 		GPIO_PIN_1
#define TRIG_PORT 		GPIOB
#define ECHO_PIN 		GPIO_PIN_0
#define ECHO_PORT 		GPIOB

/* UltraSonic Directions */

#define US_FORWARD			0
#define US_BACKWARD			1
#define US_LEFT				2
#define US_RIGHT			3


/* SW Function Decelerations */
void HAL_voidUltraSonic (uint16_t *UltraSonic_Reading) 		         ;
uint8_t HAL_UltraSonic_Decision(uint16_t *UltraSonic_Reading) 			 ;

#endif /* INC_HAL_ULTRASONIC_H_ */
