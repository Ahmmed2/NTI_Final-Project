/*
 *  DC_MOTOR.c
 *  Created on: Oct 31, 2023
 *  version : 2.0
 *  Author: Alaa Abdul Wahab
 */

#include "HAL/dc_motor.h"

extern TIM_HandleTypeDef htim1;

void HAL_voidControlMotors(uint8_t Copy_u8Speed, uint8_t Copy_u8direction)
{
  if (Copy_u8direction == STOP)
  {
		/*stop the 4 motors to stop the car*/
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
  }
  else if (Copy_u8direction == BACKWARD)
  {
		/*move the  motors in the backward direction to move the car backward*/
	    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN1_PIN, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
  }
  else if (Copy_u8direction == FORWARD)
  {
		/*move the  motors in the forward direction to move the car forward*/
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
  }
  else if (Copy_u8direction == RIGHT)
  {
		/*move the left motors in the forward direction and stop the right motors to make the car turn right*/
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN3_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
  }
  else if (Copy_u8direction == LEFT)
  {		/*move the right motors in the forward direction and stop the left motors to make the car turn left*/
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_PORT, MOTOR2_IN4_PIN, GPIO_PIN_SET);
  }

  // Set the PWM duty cycle for both motors' speed control
  // Calculate duty cycle based on the desired speed
  uint64_t dutyCycle = ((100 - Copy_u8Speed) * htim1.Init.Period) / 100;

  // Set the duty cycle for TIM_CHANNEL_1 (Motor 1)
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutyCycle);
  // Start the PWM generation for Motor 1
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  // Set the duty cycle for TIM_CHANNEL_2 (Motor 2)
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, dutyCycle);
  // Start the PWM generation for Motor 2
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}
