/*
 *  DC_MOTOR.h
 *  Created on: Oct 31, 2023
 *  version : 2.0
 *  Author: Alaa Abdul Wahab
 */

#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_


#include "stm32f1xx_hal.h"
// Motor Driver Port
#define MOTOR_DRIVER_PORT GPIOA


// Motor 1 GPIO pin definitions
#define MOTOR1_IN1_PIN GPIO_PIN_0
#define MOTOR1_IN2_PIN GPIO_PIN_1

// Motor 2 GPIO pin definitions
#define MOTOR2_IN3_PIN GPIO_PIN_2
#define MOTOR2_IN4_PIN GPIO_PIN_3

// Define Directions
#define STOP 			0
#define FORWARD 		1
#define BACKWARD 		2
#define RIGHT			3
#define LEFT 			4


/* Speeds */
#define 	SPEED_0				0
#define		SPEED_25			25
#define		SPEED_50			50
#define		SPEED_75			75
#define		SPEED_100			100


/*
Syntax:                   void controlMotors(uint8_t speed, uint8_t direction)
Description:                    Control Motors speed and direction
Reentrancy:                              Non reentrant
Parameters:                            speed, direction
Return:                                     None
*/

/*Function Details: This function controls Motors using pulse width modulation (PWM).
 * It sets the direction of Motors based on the direction parameter and adjusts
 * the speed using the speed parameter.It uses GPIO pins to control the direction
 * and a hardware timer (TIM1) for PWM generation.
 */
void HAL_voidControlMotors(uint8_t Copy_u8Speed, uint8_t Copy_u8direction) ;


#endif /* INC_DC_MOTOR_H_ */
