# This file will include , Main Configuration that we used also Pinout of our project 

## RCC will be configured as HSE 8MHZ 

## Pins Configuration

### NRF Pins 

- CE	  ->		PA1  
- SCK	  ->		PA5  
- MISO  ->		PA6  
- CSN	  ->		PA2  
- MOSI  ->		PA7
- GND   ->    GND
- VCC   ->    3.3V(Not 5V)

### GSM module 
- PinB10 -> UART3 TX
- PinB11 -> UART3 RX

### Motion 
- Motor->1 pins En1->(Timer1_CH1)->GPIOA -> PIN_A8
- IN1-> GPIOA -> PIN_A11
- IN2-> GPIOA -> PIN_A12
- Motor->2 pins En2->GPIOB -> PIN_B12
- IN3-> GPIOB -> PIN_B8
- IN4-> GPIOB -> PIN_B9

### Ultrasonic Module
#### Ultrasonic 1
- TRIG->GPIOA->PIN_A0
- ECHO->GPIOA->PIN_A4
- VCC -> 3.3v
- GND -> GND
#### Ultrasonic 2
- TRIG->GPIOB->PIN_B0
- ECHO->GPIOB->PIN_B1
- VCC -> 3.3v
- GND -> GND
#### Ultrasonic 3
- TRIG->GPIOB->PIN_B13
- ECHO->GPIOB->PIN_B14
- VCC -> 3.3v
- GND -> GND
#### Ultrasonic 4
- TRIG->GPIOA->PIN_A15
- ECHO->GPIOB->PIN_B15
- VCC -> 3.3v
- GND -> GND
### Bluetooth Module
- Tx -> UART1_Rx (PIN_B7)
- Rx -> UART1_Tx (PIN_B6)
- VCC -> 3.3v
- GND -> GND
