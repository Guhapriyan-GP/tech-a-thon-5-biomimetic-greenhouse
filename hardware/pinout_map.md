# ESP32 Pinout Mapping

This document outlines the physical wiring connections between the ESP32-WROOM-32 microcontroller, the MPU6050 sensor, and the hardware isolation gates.

### I2C Sensor Bus (MPU6050)
| ESP32 Pin | Component Pin | Function |
| :--- | :--- | :--- |
| **3V3** | VCC | Power |
| **GND** | GND | Common Ground |
| **GPIO 21** | SDA | I2C Data |
| **GPIO 22** | SCL | I2C Clock |

### Hardware Interlock & Actuation (Core 1)
| ESP32 Pin | Component | Function | Status |
| :--- | :--- | :--- | :--- |
| **GPIO 14** | 74LS08 AND Gate (Input A) | Software Request (`GPIO_SW_REQUEST`) | Active HIGH |
| **GPIO 15** | 74LS08 AND Gate (Input B) | Watchdog Status (`GPIO_WATCHDOG_ALIVE`) | Active HIGH |
| **GPIO 16** | PC817 Optocoupler (Grid Sense) | Grid Power Present (`GPIO_GRID_PRESENT`) | Input Pull-down |
| **GPIO 17** | 2N7000 MOSFET Gate | Relay Enable (`GPIO_RELAY_ENABLE`) | PWM / Digital Out |

### Power Delivery
| ESP32 Pin | Component | Function |
| :--- | :--- | :--- |
| **VIN (5V)** | DB107 Rectifier Output | Main Board Power |
| **GND** | System Ground | Common Ground for Low-Voltage Logic |
