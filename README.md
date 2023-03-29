# ESP32-Waveshare-EPaper-Driver
The ESP32-E-Paper-Driver is a driver board specially designed for driving E-Paper displays. It includes an ESP32 (WROOM-32E 8MB) as MCU, an E-Paper driver circuit, linear battery charge management, a fixed voltage LDO regulator and a driver circuit for voltage measurement without current drain.

I use the ESP32 e-paper driver in my smart home as a dashboard to display various sensor data and status information on an e-paper display. The driver connects to my MQTT broker via WLAN and regularly receives data, which is then shown on the display. Due to the low power consumption in sleep mode and the possibility of power supply via lithium battery, the display can be operated over a long period of time without having to be charged frequently.
