# NTI_Graduation-Project [V2V Communication]:
  ## Purpose:
  CAR 1 sends data to CAR 2 and act accordingly to avoid accidents. 
  ## Assumptions:
  1- Car 1 (Master) always leads Car 2 (Slave).
  2- Both are in a straight line. 
  ## Requirements:
  1- Data to be sent: 
    -	Speed.
    -	Distance.
    -	Indicator. 
      -	Traffic.
      -	Brake.
      -	Obstacle.
    -	Direction.
    -	Location. 
  ## Modes of operation:
  1- Normal mode: CAR 2 is still out of range so no communication yet and each act based on its own data.
  2- Communication mode (if CAR 2 is within the communication range): CAR 1 sends data to CAR 2. 
  3- Dominant mode: CAR1 sends data and controls CAR2 actions.
  ## Scenarios:
  1- No problems.
  2- Obstacles. 
  3- Normal brake.
  4- Sudden brake in communication mode (Switches to Dominant mode).
  5- Theft detected (Switches to Emegency Mode).
  ## States
  ### Stationery :
   System Starts: (Pooling Blutooh Module Reading “Forward, Backword ,Left , Right” && Emergency Button Not-Pressed ) || (Emergency Button Pressed). 

  ### Emergency (robbery) : 
   Red Led / Buzzer as Indication occur when Emergency Button is pressed.

  ### Normal Mode :
   - Normal Vehicle Action (Moving Vehicle) : 
     - Depends on Blutooth Module Orders to Keep in motion. 
     - Poll Ultrasonic Readings , The Vehicle decides if it continues in Motion or Stop if Ulltrasonic Reading detects obstacles”.

  ### Communication Mode :
   - Check the range of Car2  
     - Within range -> Sends Data with NRF to Car2. 
     -	Out of range ->  Return to Normal Mode. 
        
  ### Dominant Mode (Crash) :
   - Car 1 is going to crash (according to reading from Ultrasonic) and takes Full Control of Car2 (With permission)(Platooning mode ).



