/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define US1_Trig_Pin GPIO_PIN_0
#define US1_Trig_GPIO_Port GPIOA
#define NRF_CE_Pin GPIO_PIN_1
#define NRF_CE_GPIO_Port GPIOA
#define NRF_CSN_Pin GPIO_PIN_2
#define NRF_CSN_GPIO_Port GPIOA
#define Emergency_switch_Pin GPIO_PIN_3
#define Emergency_switch_GPIO_Port GPIOA
#define US1_ECHO_Pin GPIO_PIN_4
#define US1_ECHO_GPIO_Port GPIOA
#define US2_Trig_Pin GPIO_PIN_0
#define US2_Trig_GPIO_Port GPIOB
#define US2_ECHO_Pin GPIO_PIN_1
#define US2_ECHO_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_12
#define EN2_GPIO_Port GPIOB
#define US3_Trig_Pin GPIO_PIN_13
#define US3_Trig_GPIO_Port GPIOB
#define US3_ECHO_Pin GPIO_PIN_14
#define US3_ECHO_GPIO_Port GPIOB
#define US4_ECHO_Pin GPIO_PIN_15
#define US4_ECHO_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_8
#define EN1_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_11
#define IN1_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_12
#define IN2_GPIO_Port GPIOA
#define US4_Trig_Pin GPIO_PIN_15
#define US4_Trig_GPIO_Port GPIOA
#define IN3_Pin GPIO_PIN_8
#define IN3_GPIO_Port GPIOB
#define IN4_Pin GPIO_PIN_9
#define IN4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/* System Modes */
#define 	Comm_Mode				0
#define 	Dominant_Mode			1
#define 	Emergency_Mode			2
#define		Stationary_Mode			3
#define		Normal_Mode				4
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
