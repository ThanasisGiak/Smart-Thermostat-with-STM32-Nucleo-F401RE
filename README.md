## Smart Thermostat with STM32 Nucleo F401RE

For this **university project** a STM32 Nucleo F401RE board is used in order to create a "smart" thermostat.To achive that the board is interfaced with 
DS18B20 Temperature Sensor, LCD Display 16x2 Module HD44780 and HC-SR04 Ultrasonic Module Distance.The function of the thermostat is described above:

1. The temperature is measured and stored every 2 seconds using DS18B20 Temperature Sensor and after 2 minutes(24 values) the average temperature value is calculated and displayed in LCD Display 16x2 Module HD44780.The displayed message has the form "AvrgTemp is <<average temp value>>" and stays in display for 10 seconds.
2. 
