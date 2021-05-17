#include <platform.h>
#include <gpio.h>
#include "led.h"

void leds_init(void){
	
	gpio_set_mode(P_LED_G,Output);
	gpio_set_mode(P_LED, Output);
	gpio_set_mode(P_LED_R, Output);
	leds_set(0,0,0);
}

void leds_set(int board_led_on,int green_on,int red_on){
	gpio_set(P_LED, !board_led_on != LED_ON);
	gpio_set(P_LED_G, !green_on != LED_ON);
	gpio_set(P_LED_R, !red_on != LED_ON);
}