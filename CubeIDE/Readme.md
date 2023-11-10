# This file will include , Main Configuration that we used also Pinout of our project 

## RCC will be configured as HSE 8MHZ 

## Pins Configuration

### NRF Pins 

CE	 ->		PA1
SCK	 ->		PA5
MISO ->		PA6
CSN	 ->		PA2
MOSI ->		PA7

### GSM module 
- PinB10 -> UART3 TX
- PinB11 -> UART3 RX

### Motion 
- Motor->1 pins En1->(Timer1_CH1)->GPIOA -> PIN8
- IN1-> GPIOA -> PIN11
- IN2-> GPIOA -> PIN12
- Motor->2 pins En2->GPIOB -> PIN12
- IN3-> GPIOB -> PIN8
- IN4-> GPIOB -> PIN9

### Ultrasonic Module
#### Ultrasonic 1
- TRIG->GPIOA->PIN4
- ECHO->GPIOA->PIN5
#### Ultrasonic 2
- TRIG->GPIOA->PIN6
- ECHO->GPIOA->PIN7
#### Ultrasonic 3
- TRIG->GPIOA->PIN10
- ECHO->GPIOA->PIN11
#### Ultrasonic 4
- TRIG->GPIOA->PIN12
- ECHO->GPIOA->PIN13
