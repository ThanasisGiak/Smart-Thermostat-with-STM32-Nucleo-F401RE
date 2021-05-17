#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stm32f4xx_gpio.h>
#include <ds18b20.h>
#include <platform.h>
#include <stm32f4xx_gpio.h>
#include <hcsr04.h>
#include <gpio.h>
#include <lcd.h>
#include <delay.h>
#include <timer.h>
#include <led.h>
#include <math.h>
#include <hcsr04.h>
#define HIGH_TEMP 32                                                // above this temp value,print a warning in lcd screen and switch on red led and board led
#define LOW_TEMP  22                                                // below this temp value,print a warning in lcd screen and swintch on green led
#define HIGH_DIST 16                                                // if the proximity sensor senses any object between 8cm and 16cm print current temp value and last average temp value in lcd screen
#define LOW_DIST 8

uint32_t sensor_time;                                               // variable to store the duration of the pulse that proximity sensor senses to calculate distance
static float Temperature = 0;                                       //variable to store current value of temperature

int count = 0;                                                      // stores how much seconds have been passed since timer's enable

void timer_isr(){                                                   // function called from timer,every 0.5 seconds
  count++;
}
int main(void){
	int lcd_counter = 0, warning_flag = 0, lcd_flag = 0, dist_flag=0; // flags to see if something has been printed in lcd screen
	char temp_prnt[32];                                               // variable to store temp values to print them in lcd screen 
	float average_temp, temp_sum, cur_average_temp;                   // variables to store average temp value,sum of temp values sensed every 2 minutes,current average temp value
	uint8_t Temp_byte1, Temp_byte2;                                   // variables to store bytes for temp calculation
	uint16_t TEMP;                                                    // variable used in temp calculation
  static uint16_t dist;                                             // variabe used in dist calculation for proximity sensor
	static uint8_t Presence = 0;                                      // variable used in temp calculation
	
	gpio_set_mode(P_PROX_TRIGGER, Output);                            // set the gpio pin that trigger pin of proximiry sensor is connected as output
	gpio_set_mode(P_PROX_ECHO, Input);                                // set the gpio pin that echo pin of proximiry sensor is connected as input
	leds_init();                                                      // initialize leds used,one red and one green external led and board led(LD2)
	lcd_init();                                                       // initialize lcd screen
	timer_init(1000000);                                              // initialiaze timer,call an interrupt every 0.5 second
	timer_set_callback(timer_isr);                                    // set the function that called in every timer's interrupt
	timer_enable();                                                   // enable timer
 
 while(1){	
	
	if (!(count % 10)){                                               // if five seconds have been passed do
		count=0;                                                        // make count equal to zero
		lcd_counter++;                                                  // increment lcd_counter by one every five seconds
		
		if (lcd_counter == 2 && lcd_flag){                              // if lcd_counter equals two(that means that ten seconds have been passed) and lcd_flag is one do
			
			lcd_clear();                                                  // clear lcd screen
			lcd_set_cursor(0,0);                                          // set cursor in the first place of lcd screen
			lcd_flag = 0;                                                 // set lcd_flag equal to zero
	    warning_flag = 0;	                                            // set warning_flag equal to zero
			
		}
		
		if (!(lcd_counter % 2) && dist_flag){                           // if lcd_counter modulo 2 equals zero and dist_flag is one do
	     
	    lcd_clear();                                                  // clear lcd screen
			lcd_set_cursor(0,0);                                          // set cursor in the first place of lcd screen
      dist_flag=0;                                                  // set lcd_flag equal to zero
			warning_flag=0;                                               // set warning_flag equal to zero
			
		}			
	
  Presence = DS18B20_Start();                                       // check if any one wire communication device is connected to the board and start communicate
  delay_ms(1);                                                      // delay one millisecond
  DS18B20_Write(0xCC);                                              // skip ROM                                 
  DS18B20_Write(0x44);                                              // convert temp
  delay_ms(800);                                                    // delay eight hundred milliseonds

  Presence = DS18B20_Start();                                       // check if any one wire communication device is connected to the board and start communicate
  delay_ms(1);                                                      // delay one millisecond
  DS18B20_Write(0xCC);                                              // skip ROM
  DS18B20_Write(0xBE);                                              // Read Scratch-pad

  Temp_byte1 = DS18B20_Read();                                      // store byte read from ds18b20 temp sensor
  Temp_byte2 = DS18B20_Read();	                                    // store byte read from ds18b20 temp sensor
  TEMP = (Temp_byte2 << 8) | (Temp_byte1);                          
  Temperature = (float)(TEMP)/16;                                   // calculate TEMP to a float value
  temp_sum += Temperature;	                                        // keep all temp values sensed for 2 minutes
	}

		if (Temperature > HIGH_TEMP){                                   // if value of current temp is higher than 32 celsium degrees do
	      leds_set(1,0,1);                                            // switch on red led and board led(LD2)
	    if (warning_flag == 0){                                       // if warning_flag equals zero do
	
	        lcd_print("Temp>32 degrees");                             // print string in lcd screen
		      warning_flag=1;                                           // set warning_flag equal to one
				
	    }	
	  }
    else if (Temperature < LOW_TEMP){                               // if value of current temp is lower than 22 celsium degrees do 
            leds_set(0,1,0);                                        // switch on green led
	    if (warning_flag == 0){                                       // if warning_flag equals zero do
				
	       lcd_print("Temp<22 degrees");                              // print string in lcd screen
		     warning_flag=1;                                            // set warning_flag equal to one
				
      }
	  }
    else if (!lcd_flag && !dist_flag){                              // if lcd_flag equals zero and dist_flag equals zero do
			
	          lcd_clear();                                            // clear lcd screen
	          lcd_set_cursor(0,0);                                    // set cursor in the first place of lcd screen
	          leds_set(0,0,0);                                        // switch off all leds
			
    }


	if (lcd_counter == 24){                                           // if lcd_counter equals twenty four(that means that two minutes have been passed)
		
		average_temp= temp_sum/24;                                      // calculate average temp value
		cur_average_temp = average_temp;                                // store current average temp value
		temp_sum = 0;                                                   // set temp_sum(sum of temp values fpor 2 minutes) equal to zero                                                            
		lcd_flag =1;                                                    // set lcd_flag equal to zero		
		lcd_clear();                                                    // clear lcd screen                                           
		lcd_set_cursor(0,0);                                            // set cursor in the first place of lcd screen
		sprintf(temp_prnt,"%0.1f",average_temp);                        // change float variable average_temp type to string ans store it to temp_prnt
		lcd_print("AvrgTemp is ");                                      // print string in lcd screen
    delay_ms(1);		                                                // delay one millisecond
	  lcd_print(temp_prnt);                                           // print average temp value to lcd screen
		lcd_counter=0;                                                  // set lcd_counter value to zero
	  count =0;                                                       // set count value to zero
		
  }
	
    sensor_time = hcsr04_read();                                   // check if there is any object in front of prox sensor
		dist = sensor_time * .034/2;                                   // calculate the distance of this object from prox sensor 
	
		if (dist % 2){                                                 // caibrate the distance sensed to be more accurate
			
		   dist = 4*dist-1;
		}
		else{
			
       dist =dist*4;
		}	
		
	  if ((dist>= LOW_DIST && dist <= HIGH_DIST) && dist_flag==0 ){  // if distance measured is between 8 cm to 16 cm and dist_flag equals zero do
		
		   lcd_clear();                                                // clear lcd screen
		   lcd_set_cursor(0,0);                                        // set cursor in the first place of lcd screen
	     sprintf(temp_prnt,"%0.1f",Temperature);                     // change float variable Temperature type to string and store it to temp_prnt
		   lcd_print("Temp is ");                                      // print string in lcd screen
	     delay_ms(1);                                                // delay one millisecond
		   lcd_print(temp_prnt);                                       // print current temp value in lcd screen
		   lcd_set_cursor(0,1);                                        // set lcd cursor to the first place of the second line of lcd screen
		   sprintf(temp_prnt,"%0.1f",cur_average_temp);                // change float variable cur_average_temp type to string and store it to temp_prnt
		   lcd_print("AvrgTemp is ");                                  // print string in lcd screen
		   delay_ms(1);                                                // delay one millisecond 
		   lcd_print(temp_prnt);                                       // print current average temp value in lcd screen
		   dist_flag=1;                                                // set dist_flag equal to one
	  }
 }
}
	


