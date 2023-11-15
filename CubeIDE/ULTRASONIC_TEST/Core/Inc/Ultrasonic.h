/*
 * Ultrasonic.h
 *
 *  Created on: Nov 8, 2023
 *      Author: alaae
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "stm32f1xx_hal.h"

#define ULTRA_1 0
#define ULTRA_2 1
#define ULTRA_3 2
#define ULTRA_4 3
#define ULTRA_COUNT 1

extern uint32_t pMillis;


typedef struct {
    GPIO_TypeDef* trigPort;
    GPIO_TypeDef* echoPort;
    uint16_t trigPin;
    uint16_t echoPin;
    uint32_t* val1;
    uint32_t* val2;
    uint16_t* distance;
} UltrasonicSensor;

/*This function starts the timer (Timer 2) used for measuring the time intervals in the ultrasonic distance measurement.*/
void Start_Ultrasonic(void);

/* This function Triggers an ultrasonic sensor  by setting and then resetting its trigger pin.
* Measures the time it takes for the ultrasonic wave to travel to an object and back, calculating the distance based on the speed of sound.
* Adjusts the calculated distance based on certain conditions to improve accuracy.
* Stores the result in the (distances) variable
*/
void Read_DistancesUltrasonics(uint16_t* distances);

#endif /* INC_ULTRASONIC_H_ */

