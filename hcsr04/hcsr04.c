#include <platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <gpio.h>
#include <delay.h>
#include <stdint.h>
#include <stm32f4xx_gpio.h>
#include "hcsr04.h"





uint32_t hcsr04_read(void){

uint32_t local_time = 0;
	
	
	gpio_set(P_PROX_TRIGGER, 1); // pull the trigger pin high
	delay_us(10);                // delay for 10 us
	gpio_set(P_PROX_TRIGGER, 0); // pull the trigger pin low
	
	while(!(gpio_get(P_PROX_ECHO))){
	}
	
	while(gpio_get(P_PROX_ECHO)){
		local_time++;
		delay_us(1);
		
	}

	
	return local_time*2;
}