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

#define ULTRA_1 		0
#define ULTRA_2 		1
#define ULTRA_3 		2
#define ULTRA_4 		3
#define ULTRA_COUNT	    1

extern uint32_t pMillis;


/* UltraSonic Directions */

#define US_FORWARD			0
#define US_RIGHT			1
#define US_LEFT				2
#define US_BACKWARD			3



typedef struct {
    GPIO_TypeDef* trigPort;
    GPIO_TypeDef* echoPort;
    uint16_t trigPin;
    uint16_t echoPin;
    uint32_t* val1;
    uint32_t* val2;
    uint16_t* distance;
} UltrasonicSensor;



/* SW Function Decelerations */
void HAL_voidUltraSonicInit(void)										;
void HAL_voidUltraSonic (uint16_t *UltraSonic_Reading) 		         	;
uint8_t HAL_UltraSonic_Decision(uint16_t *UltraSonic_Reading) 			;

#endif /* INC_HAL_ULTRASONIC_H_ */
