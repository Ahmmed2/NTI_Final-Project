/*
 *  DC_MOTOR.c
 *  Created on: Oct 31, 2023
 *  version : 2.0
 *  Author: Alaa Abdul Wahab
 */

#include "HAL/DC_MOTOR.h"

extern TIM_HandleTypeDef htim1;

void HAL_voidControlMotors(uint8_t speed, uint8_t direction)
{
    if (speed == 0)
    {
        HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_EN_PIN , GPIO_PIN_RESET);

        if (direction == STOP)
        {
            // Stop the motors
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
        }
        else if (direction == BACKWARD)
        {
            // Move the motors in the backward direction to move the car backward
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
        }
        else if (direction == FORWARD)
        {
            // Move the motors in the forward direction to move the car forward
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
        }
        else if (direction == RIGHT)
        {
            // Move the left motors in the forward direction and stop the right motors to make the car turn right
        	HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_EN_PIN , GPIO_PIN_SET);
        	HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);

        }
        else if (direction == LEFT)
        {
            // Move the right motors in the forward direction and stop the left motors to make the car turn left
        	HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_EN_PIN , GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN3_PIN, GPIO_PIN_RESET);
        	HAL_GPIO_WritePin(MOTOR_2_PORT, MOTOR2_IN4_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_1_PORT, MOTOR1_IN2_PIN, GPIO_PIN_SET);

        }

        // Set the PWM duty cycle for both motors' speed control
        // Set the duty cycle for TIM_CHANNEL_1 (Motor 1) to control its speed
        uint64_t dutyCycle1 = (speed * htim1.Init.Period) / 100;
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutyCycle1);

        // Start the PWM generation for motor1
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    }
}

