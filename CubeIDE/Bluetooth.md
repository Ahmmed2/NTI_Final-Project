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

