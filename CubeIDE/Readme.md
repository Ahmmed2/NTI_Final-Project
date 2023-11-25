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

