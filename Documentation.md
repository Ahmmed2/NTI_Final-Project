# NTI_Graduation-Project [V2V Communication]:
  ## Purpose:
  Establishing a communication model that exchanges information between vehicles and the highway system infrastructure. Infrastructure components include road     
  signs, lane markings, traffic lights, and other smart road infrastructure connected via wireless connection in order to:
  1. Reducing road accidents and fatalities.
  2. Optimizing traffic flow.
  3. Adjusting traffic signals and speed limits.
  4. Reduce the environmental impact of transportation.  
  ## Implementation Assumptions :
  1. Car 1 (Master) always leads Car 2 (Slave).
  2. Both are in a straight line. 
  ## Requirements:
  1. Data to be sent: 
    -	Speed.
    -	Distance.
    -	Indicator. 
      -	Traffic.
      -	Brake.
      -	Obstacle.
    -	Direction.
    -	Location. 
  ## Modes of operation:
  1. Normal mode: CAR 2 is still out of range so no communication yet and each act based on its own data.
  2. Communication mode (if CAR 2 is within the communication range): CAR 1 sends data to CAR 2. 
  3. Dominant mode: CAR1 sends data and controls CAR2 actions.
  ## Scenarios:
  1. No problems.
  2. Obstacles. 
  3. Normal brake.
  4. Sudden brake in communication mode (Switches to Dominant mode).
  5. Theft detected (Switches to Emegency Mode).
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
************************************************************************************************************************************************************************************************************************************************************************************************************************************
# [Component Documentation]

# NRF24L01 Module Documentation

## 1. Introduction

### Overview
The NRF24L01 module is a highly integrated, ultra-low power 2Mbps RF transceiver designed for wireless communication applications.

### Features
- **Low Operating Voltage:** 1.9 - 3.6V
- **Max Data Rate:** 2 Mbps
- **Range:** Up to 100 meters
- **Multiple Frequency Channels:** 125 selectable channels
- **Automatic Packet Handling**
- **Built-in Hardware Acknowledgment and Retransmission**

### Pinout
- **VCC:** Power Supply
- **GND:** Ground
- **CE:** Chip Enable (Enables/Disables RX/TX mode)
- **CSN:** Chip Select Not (SPI Slave Select)
- **SCK:** Serial Clock (SPI Clock)
- **MOSI:** Master Out Slave In (SPI Data Input)
- **MISO:** Master In Slave Out (SPI Data Output)
- **IRQ:** Interrupt Request (Optional)

## 2. Getting Started

### Hardware Setup
1. Connect VCC and GND to the power supply.
   - NRF24L01 VCC pin to STM32 3.3V pin (Power Supply)
   - NRF24L01 GND pin to STM32 GND pin (Ground)
2. Connect CE, CSN, SCK, MOSI, MISO, and IRQ pins to the microcontroller.
   - NRF24L01 MISO pin to STM32 SPI1_MISO PA6 pin (Master In Slave Out)
   - NRF24L01 MOSI pin to STM32 SPI1_MOSI PA7 pin (Master Out Slave In)
   - NRF24L01 SCK pin to STM32 SPI1_SCK PA5 pin (Serial Clock)
   - NRF24L01 CE pin to STM32 GPIO PA1 pin (Chip Enable)
   - NRF24L01 CSN pin to STM32 GPIO PA2 pin (Slave Select)
   - NRF24L01 IRQ pin not connected.

### Software Setup
1. Initialize the NRF module: `NRF_voidInit()`.
2. Initialize SPI communication: `MX_SPI1_Init()`.
3. Choose transmitter or receiver mode.
4. Send or receive data based on the chosen mode.

## 3. Configuration

### SPI Communication Settings
- **Data Size**
- **Clock Polarity**
- **Clock Phase**

### Module Initialization
- **Power-Up Sequence**
- **Register Initialization**

## 4. Data Transmission

### Sending Data
1. Set the TX address.
2. Write data to the TX FIFO.
3. Start transmission.

### Receiving Data
1. Set the RX address for the desired pipe.
2. Read data from the RX FIFO.

### Error Handling
- **Handling Acknowledgment Failures**
- **Retransmission Strategies**

## 5. Advanced Features

### Multiple Pipes Configuration
1. Set individual addresses for each pipe.
2. Enable the corresponding pipes in the EN_RXADDR register.

### Dynamic Payload Length (DPL)
- Enable DPL in the FEATURE register.
- Set payload lengths dynamically for each pipe.

### Acknowledgment (ACK) Payloads
- Enable ACK payloads in the FEATURE register.
- Configure the payload data for ACK packets.

## 6. Troubleshooting

### Common Issues
- **No Communication**
- **Unstable Communication**
- **Limited Range**

### Debugging Tips
- Use Status Register Flags
- Use External Interrupts (IRQ pin)

## 7. Usage Examples

### Simple Transmit and Receive
Provide simple code examples for basic transmit and receive operations.

### Using Multiple Pipes
Show examples of configuring and using multiple pipes for data transmission.

### Advanced Features Implementation
Demonstrate the implementation of features like DPL and ACK payloads in practical applications.
******************************************************************************************************************************************************************

# HC-05 Bluetooth Module Documentation

## 1. Introduction

The HC-05 Bluetooth module is a versatile wireless communication module designed for enabling serial communication between devices. Widely employed in embedded systems, IoT projects, and robotics applications, the HC-05 provides a reliable solution for wireless data transfer.

## 2. Specifications

- **Bluetooth Version:** Bluetooth v2.0+EDR (Enhanced Data Rate)
- **Operating Voltage:** 3.3V
- **Communication Range:** Approximately 10 meters (varies based on the environment)
- **Serial Communication:** UART (Universal Asynchronous Receiver/Transmitter)
- **Default Baud Rate:** 9600 bps
- **Supported Profiles:** SPP (Serial Port Profile)
- **Supported Modes:** Master and Slave

## 3. Pinout

- **VCC:** Power Supply (3.3V)
- **GND:** Ground
- **TXD:** Transmit Data (Serial Output)
- **RXD:** Receive Data (Serial Input)
- **STATE:** Connection Status Indicator (Optional)
- **EN:** Enable Pin (Optional)

## 4. Modes of Operation

- **AT Mode:** Allows module configuration using AT commands.
- **Data Mode:** Module is connected and ready for data transmission.

## 5. Connecting HC-05 to Microcontroller

### STM32 Microcontroller Connection

- **VCC:** 3.3V
- **GND:** Ground
- **TXD:** Connected to STM32 RX A9 pin (e.g., USART1_TX)
- **RXD:** Connected to STM32 TX A10 pin (e.g., USART1_RX)
- **STATE (Optional):** Not connected
- **EN (Optional):** Not connected

## 6. Troubleshooting

### Module Not Responding:

- Check the wiring and power supply connections.
- Ensure the baud rate settings match between the microcontroller and HC-05.

### Limited Range or Connection Issues:

- Check for interference from other electronic devices.
- Verify there are no physical obstacles between devices.

## Getting Started

To integrate the HC-05 module into your project:

1. **Hardware Setup:**
   - Connect the HC-05 module to your STM32 microcontroller according to the provided pinout.

2. **Software Integration:**
   - Initialize the UART communication on your STM32 microcontroller with the appropriate baud rate.
   - Enable the global interrupt
******************************************************************************************************************************************************************

# GSM Module Documentation

## 1. Introduction

### Overview
The GSM module (SIM800L) with a serial interface. It can send and receive text messages and receive phone calls and SMS. The SIM800L is connected to a microcontroller using the serial UART interface.

### Features
- **Low Operating Voltage:** 3.4V to 4.4V
- **Peak Current:** 2A
- **Max Data Rate:** 85.6 kbps
- **Frequancies:** its works on frequencies 850MHz, 900MHz, 1800MHz, and 1900MHz

## Pinout
  ### Used
- **VCC:** Power Supply
- **GND:** Ground
- **NET:** Used to connect Antenna
- **RXD:** Recsive Data
- **TXD:** Transimit Data
  ### UnUsed
- **RING:** Incoming Call 
- **DTR:** Enable / Disable Sleep Mode
- **MIC+:** Connect Mic +
- **MIC-:** Connect Mic -
- **SPK+:** Connect Speaker +
- **SPK-:** Connect Speaker -


## 2. Getting Started

### Hardware Setup
1. Connect VCC and GND to the power supply.
   - SIM800L VCC pin to STM32 5V pin (Power Supply)
   - SIM800L GND pin to STM32 GND pin (Ground)
2. Connect RXD and TXD pins to the microcontroller.
   - SIM800L RXD pin to STM32 UART3 TX (PB10) pin
   - SIM800L TXD pin to STM32 UART3 RX (PB11) pin
3- Connect NET pin to Antenna for Signal powering

### Software Setup
1. Initialize the GSM module: Connecting module to power.
2. Wait for 9 - 12 Seconds for GSM initiating:  `GSM_VidInit()`.
3. Check GSM Connection is Valid : `GSM_VidCheckConnection()`.
4. Sending Certian message to cerian phone number : `GSM_VidSendSMS`.

## 3. Configuration

### UART Communication Settings
- **Data Size**
- **BaudRate**
- **Selecting Parity**
- **Stop Bit**


### Module Initialization
- **Power-Up Module**
- **Waiting for established connection**

## 4. Data Transmission

### Sending Data
2. Write data Commands to the TX.
3. Start transmission.

### Receiving Data
1. Set the RX address for the desired pipe.
2. Read data from the RX FIFO.
3. Recsived data has the acknowledgement for each command 

### Error Handling
- **Handling Acknowledgment Failures:** Acknowledgment (OK) is not sent
- **Retransmission Strategies: ** Re-establishing connections  


## 6. Troubleshooting

### Common Issues
- **No Communication**
- **Unstable Communication**
- **Garbage Data**

### Debugging Tips
- Use Checking Commands and Read Recsived Data
- Checking every command and comparing it with Data sheets commands

## 7. Usage Examples

### Simple Transmit and Receive
Provide simple code examples for basic transmit and receive operations.

### Sending Commands and Getting Acknowledgment
Sending different commands and Recsiving the right ACK for every command.

### Sending SMS to Phone Number
Setting Message to be sent to a phone number.
******************************************************************************************************************************************************************

# DC Motor Documentation


## 1. Introduction
### Overview
A DC motor is an electric motor that converts direct current (DC) electrical energy into mechanical motion. It is widely used in various applications, including robotics, automation, and motor control systems.

### Features
- Operating Voltage: Typically 3-24V (Depends on the motor model)
- Speed Control: Can be controlled by varying the voltage or using pulse width modulation (PWM)
- Direction Control: Can be controlled by reversing the polarity of the power supply or using an H-bridge circuit
- Torque: Varies depending on the motor model and voltage

### Pinout (Example):
- VCC: Power Supply
- GND: Ground
- IN1: Input 1 (Control signal for direction)
- IN2: Input 2 (Control signal for direction)
- PWM: Pulse Width Modulation (Controls motor speed)
## 2. Getting Started

### Hardware Setup
1. Connect VCC and GND to the power supply.
- DC Motor VCC pin to power supply positive terminal (Power Supply)
- DC Motor GND pin to power supply negative terminal (Ground)

2. Connect control pins to the microcontroller or motor driver.
- DC Motor IN1 pin to microcontroller GPIO pin or motor driver input pin
- DC Motor IN2 pin to microcontroller GPIO pin or motor driver input pin
- DC Motor PWM pin to microcontroller PWM output pin or motor driver PWM input pin

### Software Setup
- Initialize the microcontroller's GPIO pins or PWM module for the DC motor control.
- Configure the control pins as outputs for direction control.
- Configure the PWM pin for speed control .

## 3. Configuration

### Direction Control
Set the control pins to the desired logic levels to control the motor's direction.
For example, setting IN1 to HIGH and IN2 to LOW may rotate the motor in one direction, while setting IN1 to LOW and IN2 to HIGH may rotate it in the opposite direction.

### Speed Control
Set the duty cycle of the PWM signal to control the motor's speed. Higher duty cycles result in faster speeds, while lower duty cycles result in slower speeds.

## 4. Motor Operation

- Start the Motor
- Set the control pins and PWM signal according to the desired direction and speed.
- Activate the motor by providing power to the VCC pin.
- Stop the Motor
- Set the control pins to neutral or OFF state.

- Remove power from the VCC pin.
## 5. Advanced Features
### Motor Braking
- Implement electronic braking techniques to quickly stop the motor's rotation.
This can be achieved by shorting the motor terminals or applying a reverse voltage for a brief period.
### Motor Current Sensing
- Integrate current sensing techniques to monitor the motor's current for protection or feedback purposes.
This can be done using current sensors or by measuring voltage across a shunt resistor.

## 6. Troubleshooting
- Common Issues
- Motor Not Rotating
- Unstable Motor Operation
- Motor Overheating
- Debugging Tips
- Check wiring connections and ensure proper voltage levels.
- Verify the logic levels of the control pins and PWM signal.

## 7. Usage Examples
- Simple Motor Control
Provide a code example for basic control of a DC motor, including starting, stopping, and changing the direction.
- Speed Control using PWM
Demonstrate a code example for controlling the speed of a DC motor using PWM signals.
******************************************************************************************************************************************************************

# Ultrasoinc Sensor Documentation

## 1. Introduction
### Overview
The ultrasonic sensor is a device that uses sound waves to measure distances and detect objects. It is commonly used in various applications such as robotics, distance measurement, and object detection.

### Features
- Operating Voltage: Typically 5V
- Measurement Range: From 2 cm to 4 metres.
- Output: Digital or analog output (depends on the sensor)
- Ultrasonic Transducer: Emits and receives sound waves
- Trigger Pin: Initiates the measurement by sending a trigger signal
- Echo Pin: Receives the echo signal reflected from objects

### Pinout (Example):
- VCC: Power Supply (5V)
- GND: Ground
- TRIG: Trigger Pin (Input)
- ECHO: Echo Pin (Output)

## 2. Getting Started

### Hardware Setup
1-Connect VCC and GND to the power supply.
- Ultrasonic Sensor VCC pin to microcontroller's 5V pin (Power Supply)
- Ultrasonic Sensor GND pin to microcontroller's GND pin (Ground)
2-Connect TRIG and ECHO pins to the microcontroller.
- Ultrasonic_1 Sensor TRIG pin to microcontroller's GPIO pin (Trigger)->PIN_A0
- Ultrasonic_1 Sensor ECHO pin to microcontroller's GPIO pin (Echo)->PIN_A4
- Ultrasonic_2 Sensor TRIG pin to microcontroller's GPIO pin (Trigger)->PIN_B0
- Ultrasonic_2 Sensor ECHO pin to microcontroller's GPIO pin (Echo)->PIN_B1
- Ultrasonic_3 Sensor TRIG pin to microcontroller's GPIO pin (Trigger)->PIN_B13
- Ultrasonic_3 Sensor ECHO pin to microcontroller's GPIO pin (Echo)->PIN_B14
- Ultrasonic_4 Sensor TRIG pin to microcontroller's GPIO pin (Trigger)->PIN_A15
- Ultrasonic_4 Sensor ECHO pin to microcontroller's GPIO pin (Echo)->PIN_B15

### Software Setup
 1-Initialize the microcontroller's GPIO pins for the ultrasonic sensor.
 2-Configure the trigger pin as an output and the echo pin as an input.
 3-Start Ultrasoin sensor : Start_Ultrasonic();
 4-Read Distance :Read_DistancesUltrasonics();


## 3. Configuration

- Triggering the Measurement
- Send a pulse on the trigger pin to initiate the measurement.
- Wait for a short duration(10 us) to allow the ultrasonic sensor to settle.
- Receiving the Echo
- Measure the duration it takes for the echo signal to arrive.
- Calculate the distance based on the speed of sound and the measured time.

## 4. Data Acquisition

### Distance Measurement
 -Convert the measured time into a distance using the speed of sound in air (approximately 343 meters per second).
 -Handle any conversions or calibrations required based on the specific sensor and application.
### Object Detection
 -Set a threshold distance to consider an object detected based on the application requirements.
 -Compare the measured distance with the threshold to determine if an object is present.

## 5. Advanced Features
- Filtering and Averaging
Implement filtering techniques such as averaging or median filtering to reduce noise or improve measurement accuracy.
Multiple Sensor Integration
- If using multiple ultrasonic sensors, ensure proper synchronization and avoid interference between sensors.
Consider using different trigger and echo pins for each sensor and implementing a time-multiplexing scheme.
## 6. Troubleshooting
- Common Issues
- Inaccurate Measurements
- Unstable Readings
- Interference or Crosstalk between Sensors
- Debugging Tips
- Check wiring connections and ensure proper voltage levels.
- Verify the timing and synchronization between trigger and echo signals.
- Use debugging tools such as an oscilloscope to monitor the signals.
## 7. Usage Examples

### Simple Distance Measurement
 Provide a code example for a basic distance measurement using an ultrasonic sensor.

### Object Detection 
 Demonstrate a code example for detecting objects based on a predefined threshold distance.




  







