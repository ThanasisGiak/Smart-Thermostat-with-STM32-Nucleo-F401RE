#include <platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <gpio.h>
#include <delay.h>
#include <stdint.h>
#include <stm32f4xx_gpio.h>
#include "ds18b20.h"


	uint8_t value=0;
	uint8_t Response = 0;

uint8_t DS18B20_Start (void)
{

	
	gpio_set_mode(P_TMP,Output); // set the pin as output
	
	
	gpio_set(P_TMP,0); // pull the pin low
	delay_us(480);   // delay according to datasheet

	   
	gpio_set_mode(P_TMP,Input); // set the pin as input
	
	delay_us(80);    // delay according to datasheet

	if (!gpio_get(P_TMP))
	Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay_us(400); // 480 us delay totally.

	return Response;
}

void DS18B20_Write(uint8_t data)
{
	
	gpio_set_mode(P_TMP,Output); // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			 
			
			gpio_set_mode(P_TMP,Output); // set as output
			gpio_set(P_TMP, 0); // pull the pin LOW
			delay_us(1);  // wait for 1 us

			
			gpio_set_mode(P_TMP,Input); // set as input
			delay_us(60);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			
			gpio_set_mode(P_TMP,Output);
		
			
			gpio_set(P_TMP, 0); 	// pull the pin LOW
			delay_us(60);  // wait for 60 us

			
			gpio_set_mode(P_TMP,Input);
			
		}
	}
}
	uint8_t DS18B20_Read (void)
{

	
	gpio_set_mode(P_TMP,Input);
  
	for (int i=0;i<8;i++)
	{
		 
		gpio_set_mode(P_TMP,Output); // set as output

		gpio_set(P_TMP, 0); // pull the data pin LOW
		delay_us(2);  // wait for 2 us

		 
		gpio_set_mode(P_TMP,Input); // set as input
		
		if (gpio_get(P_TMP)) // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay_us(60);  // wait for 60 us
	}
	return value;
}