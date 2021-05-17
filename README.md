## Smart Thermostat with STM32 Nucleo F401RE

For this **university project** a STM32 Nucleo F401RE board is used in order to create a "smart" thermostat.To achive that the board is interfaced with 
DS18B20 Temperature Sensor, LCD Display 16x2 Module HD44780 and HC-SR04 Ultrasonic Module Distance.The function of the thermostat is described above:

1. The temperature is measured and stored every 2 seconds using DS18B20 Temperature Sensor and after 2 minutes(24 values) the average temperature value is calculated and displayed in LCD Display 16x2 Module HD44780.The displayed message has the form "AvrgTemp is < *average temp value* >" and stays in display for 10 seconds.
2. When the temperature rises over a value that is defined as *HIGH_TEMP* in main.c two LEDs(one external LED & board LED(LD2) are turned on and an error message is displayed in LCD screen.The message has the form “Temp> <<HIGH_TEMP>> degrees”.When the temperature drops below this threshold the LEDs turn off and the displayed message gets erased.
3. When the temperature drops down a value that is defined as *LOW_TEMP* in main.c ine external LED turns on and an error message is displayed in LCD screen.The message has the form “Temp< <<LOW_TEMP>> degrees”.When the temperature rises above this threshold the LED turns off and the displayed message gets erased.
4. When HC-SR04 Ultrasonic Module Distance detects something 8cm to 16cm distance then a message is printed to LCD screen. To LCD screen's first line the last measured temperature value in printed, the message has the form “Temp is < *temp value* >” and into the second line the last calculated average temperature value is printed, the message has the form AvrgTemp is < *average temp value* >”. 

## References
1. [Official Arm keil site](http://www.keil.com/)
2. [DS18B20 and STM32-CONTROLLERSTECH site](https://controllerstech.com/ds18b20-and-stm32/)
3. [HC-SR04 and STM32- CONTROLLERSTECH site](https://controllerstech.com/hc-sr04-ultrasonic-sensor-and-stm32/)
4. [Dealing with LEDs using an STM32-playembedded.org site](https://www.playembedded.org/blog/leds-stm32/)

### For this project ARM Keil MDK and ARM University Program Libraries have been used.
