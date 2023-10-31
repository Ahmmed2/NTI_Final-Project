/*
 *  DC_MOTOR.c
 *  Created on: Oct 31, 2023
 *  version : 1.0
 *  Author: Alaa Abdul Wahab
 */

#include "dc_motor.h"

extern TIM_HandleTypeDef htim1;

void controlMotor1(uint8_t speed, uint8_t direction)
{
  if (direction == 0)
  {
    // Set IN1 to logic level 0 and IN2 to logic level 1
    HAL_GPIO_WritePin(GPIOA, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, MOTOR1_IN2_PIN, GPIO_PIN_SET);
  }
  else
  {
    // Set IN1 to logic level 1 and IN2 to logic level 0
    HAL_GPIO_WritePin(GPIOA, MOTOR1_IN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
  }

  // Set the PWM duty cycle for Motor 1 speed control
  // Calculate duty cycle based on the desired speed
  uint32_t dutyCycle = ((100 - speed) * htim1.Init.Period) / 100;

  // Set the duty cycle for TIM_CHANNEL_2
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutyCycle);
  // Start the PWM generation for Motor 1
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void controlMotor2(uint8_t speed, uint8_t direction)
{
  if (direction == 0)
  {
    // Set IN1 to logic level 0 and IN2 to logic level 1
    HAL_GPIO_WritePin(GPIOA, MOTOR2_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, MOTOR2_IN2_PIN, GPIO_PIN_SET);
  }
  else
  {
    // Set IN1 to logic level 1 and IN2 to logic level 0
    HAL_GPIO_WritePin(GPIOA, MOTOR2_IN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, MOTOR2_IN2_PIN, GPIO_PIN_RESET);
  }

  // Set the PWM duty cycle for Motor 2 speed control
  // Calculate duty cycle based on the desired speed
  uint32_t dutyCycle = ((100 - speed) * htim1.Init.Period) / 100;

  // Set the duty cycle for TIM_CHANNEL_2
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, dutyCycle);
  // Start the PWM generation for Motor 2
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}
