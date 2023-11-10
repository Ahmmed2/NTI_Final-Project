 # Motor Driver version 2.0
 ## control 2 motors (speed and Direction)
 
 ### - Motor->1 pins En1->(Timer1_CH1)->GPIOA -> PIN_A8
 ###               - IN1-> GPIOA -> PIN_A11
 ###               - IN2-> GPIOA -> PIN_A12
 ### - Motor->2 pins En2->GPIOB -> PIN_B12
 ###               - IN3-> GPIOB -> PIN_B8
 ###               - IN4-> GPIOB -> PIN_B9
 
 ### Functuion: controlMotors(speed, direction);
 ### Speed can be from (0 -> 100)
 ###                    0-> min speed (stop motors)
 ###                    100-> max speed 
 
 ### Direction can be : 1- FORWARD
 ###                    2- BACKWARD
 ###                    3- LEFT
 ###                    4- RIGHR
 ###                    5- STOP
