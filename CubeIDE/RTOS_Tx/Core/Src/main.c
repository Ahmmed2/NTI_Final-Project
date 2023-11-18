/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HAL/dc_motor.h"
#include "HAL/Ultrasonic.h"
#include "HAL/HAL_NRF.h"
#include "HAL/GSM.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

osThreadId defaultTaskHandle;
osThreadId Init_SystemHandle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osMessageQId Tx_QueueHandle;
osMessageQId Rx_QueueHandle;
osMessageQId US_QueueHandle;
osTimerId ActionDecision_TimerHandle;
osTimerId Mode_TimerHandle;
osSemaphoreId Mode_SemHandle;
/* USER CODE BEGIN PV */

/* Car State */
uint8_t Car_State = STATE_STATIONARY ;
uint8_t Car_Direction  ;
uint8_t Car_Speed  ;
uint8_t Indication_value ;
uint8_t System_Mode = Stationary_Mode ;

/* BM Receive Variable */
uint8_t rxData ;
uint8_t TMR_Counter = 0 ;

/* UltraSonic */
uint16_t US_ARR[4] = {50 , 50, 50 , 50} ;
uint8_t US_Decision = 0 ;

/* NRF */

/* Address of PIPE 1 */
uint8_t TxAddress[] = {0xEE,0xDD,0xCC,0xBB,0xAA} ;

/* Data to be Sent */
/*
 * S --> Speed
 * D --> Direction
 * M --> Distance
 * I --> Indication
 *
 */
uint8_t Data_States[4] = {'S','D','M','I'}  ;
uint8_t Data_Sent[8]  ;
uint8_t Debug_Var ;
DataTransfer_t Data_Tx ;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
void StartDefaultTask(void const * argument);
void Init_Task(void const * argument);
void DataGathering_Task(void const * argument);
void VehicleComm_Task(void const * argument);
void ActionDecision_Callback(void const * argument);
void Mode_Callback(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of Mode_Sem */
  osSemaphoreDef(Mode_Sem);
  Mode_SemHandle = osSemaphoreCreate(osSemaphore(Mode_Sem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of ActionDecision_Timer */
  osTimerDef(ActionDecision_Timer, ActionDecision_Callback);
  ActionDecision_TimerHandle = osTimerCreate(osTimer(ActionDecision_Timer), osTimerPeriodic, NULL);

  /* definition and creation of Mode_Timer */
  osTimerDef(Mode_Timer, Mode_Callback);
  Mode_TimerHandle = osTimerCreate(osTimer(Mode_Timer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of Tx_Queue */
  osMessageQDef(Tx_Queue, 5, uint8_t);
  Tx_QueueHandle = osMessageCreate(osMessageQ(Tx_Queue), NULL);

  /* definition and creation of Rx_Queue */
  osMessageQDef(Rx_Queue, 10, uint8_t);
  Rx_QueueHandle = osMessageCreate(osMessageQ(Rx_Queue), NULL);

  /* definition and creation of US_Queue */
  osMessageQDef(US_Queue, 3, uint8_t);
  US_QueueHandle = osMessageCreate(osMessageQ(US_Queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Init_System */
  osThreadDef(Init_System, Init_Task, osPriorityHigh, 0, 128);
  Init_SystemHandle = osThreadCreate(osThread(Init_System), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, DataGathering_Task, osPriorityAboveNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, VehicleComm_Task, osPriorityNormal, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 64;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 256;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 65535;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 32;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 50000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, US1_Trig_Pin|NRF_CE_Pin|NRF_CSN_Pin|IN1_Pin
                          |IN2_Pin|US4_Trig_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, US2_Trig_Pin|EN2_Pin|US3_Trig_Pin|IN3_Pin
                          |IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : US1_Trig_Pin NRF_CE_Pin NRF_CSN_Pin IN1_Pin
                           IN2_Pin US4_Trig_Pin */
  GPIO_InitStruct.Pin = US1_Trig_Pin|NRF_CE_Pin|NRF_CSN_Pin|IN1_Pin
                          |IN2_Pin|US4_Trig_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Emergency_switch_Pin US1_ECHO_Pin */
  GPIO_InitStruct.Pin = Emergency_switch_Pin|US1_ECHO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : US2_Trig_Pin EN2_Pin US3_Trig_Pin IN3_Pin
                           IN4_Pin */
  GPIO_InitStruct.Pin = US2_Trig_Pin|EN2_Pin|US3_Trig_Pin|IN3_Pin
                          |IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : US2_ECHO_Pin US3_ECHO_Pin US4_ECHO_Pin */
  GPIO_InitStruct.Pin = US2_ECHO_Pin|US3_ECHO_Pin|US4_ECHO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Init_Task */
/**
* @brief Function implementing the Init_System thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Init_Task */
void Init_Task(void const * argument)
{
  /* USER CODE BEGIN Init_Task */
  /* Infinite loop */
  for(;;)
  {
	  	HAL_voidUltraSonicInit() ;
	    NRF_voidInit();
	    NRF_voidTransmitterMode (TxAddress ,10 );
	    GSM_VidInit();
	    GSM_VidCheckConnection();
	    HAL_UART_Transmit(&huart1,'R',1,100); //indicate initialization finished

	    /*Emergency mode Robbery*/
	    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
	    {
	    	System_Mode = Emergency_Mode;
	    }
	    HAL_UART_Receive_IT(&huart1,&rxData,1); // Enabling interrupt receive

	    osThreadTerminate(Init_SystemHandle); //delete task
  }
  /* USER CODE END Init_Task */
}

/* USER CODE BEGIN Header_DataGathering_Task */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataGathering_Task */
void DataGathering_Task(void const * argument)
{
  /* USER CODE BEGIN DataGathering_Task */
  /* Infinite loop */
  for(;;)
  {
	  //read 4 US and insert data into Tx queue
	  HAL_voidUltraSonic (US_ARR);
	  for(uint8_t i = 0 ; i < 4 ; i++)
	  {
		  xQueueSend( Tx_QueueHandle, &US_ARR[i] , portMAX_DELAY );
	  }

	  //insert BM reading into Tx queue
	  xQueueSend( Tx_QueueHandle, &rxData , portMAX_DELAY );

    osDelay(1);
  }
  /* USER CODE END DataGathering_Task */
}

/* USER CODE BEGIN Header_VehicleComm_Task */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_VehicleComm_Task */
void VehicleComm_Task(void const * argument)
{
  /* USER CODE BEGIN VehicleComm_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END VehicleComm_Task */
}

/* ActionDecision_Callback function */
void ActionDecision_Callback(void const * argument)
{
  /* USER CODE BEGIN ActionDecision_Callback */
	uint16_t US_data[4] , BM , US_Decision;
	 for(uint8_t i = 0 ; i < 4 ; i++)
	  {
		 xQueueReceive( Tx_QueueHandle, &US_data[i] , portMAX_DELAY );
	  }
	 xQueueReceive( Tx_QueueHandle, &BM , portMAX_DELAY );
	switch (BM)
		  	{

		  	case 'F' :
		  		Car_Direction = FORWARD ;
		  		Car_State = STATE_MOVING ;
		  		break ;

		  	case 'B' :
		  		Car_Direction = BACKWARD ;
		      	Car_State = STATE_MOVING ;
		      	break ;

		  	case 'R' :
		  		Car_Direction = RIGHT ;
		  		Car_State = STATE_MOVING ;
		      	break ;

		  	case 'L' :
		  		Car_Direction = LEFT ;
		  		Car_State = STATE_MOVING ;
		      	break ;

		  	case 'P' :
		  		HAL_voidControlMotors(SPEED_0,STOP) ;
		  		Car_State = STATE_STOP ;
		      	break ;
		  	}
	US_Decision = HAL_UltraSonic_Decision(US_data);

	if (US_Decision == 254)
		{
		    Indication_value = INDICATION_NORMAL ;
			HAL_voidControlMotors(Normal_SPEED,Car_Direction) ;
			Car_Speed = Normal_SPEED ;
			HAL_UART_Transmit(&huart1,(uint8_t*)"D",1,100);
		}
		else if (US_Decision == STOP)
		{
			Indication_value = INDICATION_OBSTACLE ;
			HAL_voidControlMotors(SPEED_0,STOP) ;
			Car_Speed = SPEED_0 ;
			HAL_UART_Transmit(&huart1,(uint8_t*)"P",1,100);
		}
		else if (US_Decision == SPEED_25)
		{
			Indication_value = INDICATION_TRAFFIC ;
			HAL_voidControlMotors(SPEED_25,Car_Direction) ;
			Car_Speed = SPEED_25 ;
			HAL_UART_Transmit(&huart1,(uint8_t*)"S",1,100);
		}
	/* Update NRF values*/
	Data_Sent[0]	 = Data_States[0]						;
	Data_Sent[1]	 = Car_Speed							;
	Data_Sent[2]	 = Data_States[1]						;
	Data_Sent[3]	 = Car_Direction						;
	Data_Sent[4]     = Data_States[2]						;  /* Distance  */
	Data_Sent[5]     = US_data[3]			    			;
	Data_Sent[6]	 = Data_States[3]						;
	Data_Sent[7]	 = Indication_value						;

	xQueueSend( Tx_QueueHandle, &Data_States[0] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_Sent[1] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_States[1] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_Sent[3] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_States[2] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_Sent[5] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_States[3] , portMAX_DELAY );
	xQueueSend( Tx_QueueHandle, &Data_Sent[7] , portMAX_DELAY );
  /* USER CODE END ActionDecision_Callback */
}

/* Mode_Callback function */
void Mode_Callback(void const * argument)
{
  /* USER CODE BEGIN Mode_Callback */

  /* USER CODE END Mode_Callback */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
