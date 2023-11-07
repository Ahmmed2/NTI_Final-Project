 # Motor Driver version 2.0
 ## control 2 motors (speed and Direction)
 
 ### Motor->1 pins  En1->(Timer1_CH1)->GPIOA -> PIN8
 ###                IN1-> GPIOA -> PIN0
 ###                IN2-> GPIOA -> PIN1

 ### Motor->2 pins  En2->(Timer1_CH2)->GPIOA -> PIN9
 ###                IN3-> GPIOA -> PIN2
 ###                IN4-> GPIOA -> PIN3

 ### Functuion: controlMotors(speed, direction);
 ### Speed can be from (0 -> 100)
 ###                    0-> min speed (stop motors)
 ###                    100-> max speed 
 
 ### Direction can be : 1- FORWARD
 ###                    2- BACKWARD
 ###                    3- LEFT
 ###                    4- RIGHR
 ###                    5- STOP