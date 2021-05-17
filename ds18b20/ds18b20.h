#ifndef DS18B20_H
#define DS18B20_H
  
	extern uint8_t value;
	extern uint8_t Response;
	uint8_t DS18B20_Start (void);
	void DS18B20_Write(uint8_t data);
	uint8_t DS18B20_Read (void);

#endif // DS18B20_H