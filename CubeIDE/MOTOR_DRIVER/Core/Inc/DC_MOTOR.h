/*
 *  DC_MOTOR.h
 *  Created on: Oct 31, 2023
 *  version : 1.0
 *  Author: Alaa Abdul Wahab
 */

#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_


#include "stm32f1xx_hal.h"

// Motor 1 GPIO pin definitions
#define MOTOR1_IN1_PIN GPIO_PIN_0
#define MOTOR1_IN2_PIN GPIO_PIN_1

// Motor 2 GPIO pin definitions
#define MOTOR2_IN1_PIN GPIO_PIN_2
#define MOTOR2_IN2_PIN GPIO_PIN_3




/*
Syntax:                   void controlMotor1(uint8_t speed, uint8_t direction)
Description:                    Control Motor_1 speed and direction
Reentrancy:                              Non reentrant
Parameters:                            speed, direction
Return:                                     None
*/

/*Function Details: This function controls Motor 1 using pulse width modulation (PWM).
 * It sets the direction of Motor 1 based on the direction parameter and adjusts
 * the speed using the speed parameter.It uses GPIO pins to control the direction
 * and a hardware timer (TIM1) for PWM generation.
 */
void controlMotor1(uint8_t speed, uint8_t direction);

/*
Syntax:                   void controlMotor2(uint8_t speed, uint8_t direction)
Description:                    Control Motor_2 speed and direction
Reentrancy:                              Non reentrant
Parameters:                            speed, direction
Return:                                     None
*/

/*Function Details: This function controls Motor 2 using pulse width modulation (PWM).
 * It sets the direction of Motor 2 based on the direction parameter and adjusts
 * the speed using the speed parameter.It uses GPIO pins to control the direction
 * and a hardware timer (TIM1) for PWM generation.
 */
void controlMotor2(uint8_t speed, uint8_t direction);


#endif /* INC_DC_MOTOR_H_ */
