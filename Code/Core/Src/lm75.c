#include "lm75.h"

float lm75_read_temp(I2C_HandleTypeDef *hi2c)
{
	uint16_t data;
	HAL_I2C_Mem_Write(hi2c, LM75_ADDRESS, 0x00, 1, 0x00, 1, 100);

	HAL_I2C_Master_Receive(hi2c, LM75_ADDRESS, (uint8_t*)&data, 2, 100);
	data = ((( data >> 8 ) | ( data << 8 )) >> 7) & 0x01FF;

	if(data & 0x0100 ){
		data = (0x01FE ^ data) + 2;
		return (float)( data * (-0.5f) );
	}
	else{
		return (float)( data * 0.5f );
	}
}

void lm75_write_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp)
{
	uint8_t command[3];
	
	command[0] = reg;
	command[1] = temp;
	command[2] = 0x00;
	
	HAL_I2C_Master_Transmit(hi2c, LM75_ADDRESS, (uint8_t*)command, 3, 100);
}

void lm75_write_shutdown_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp)
{
	lm75_write_temperature(hi2c, 0x02, temp);
}

void lm75_write_turn_on_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp)
{
	lm75_write_temperature(hi2c, 0x03, temp);
}

void lm75_sleep_mode(I2C_HandleTypeDef *hi2c, enum LM75_SLEEP_MODE mode)
{
	uint8_t command[2];
	
	command[0] = 0x01;
	
	switch(mode){
		case LM75_NORMAL:
			command[1] = 0x00;
			break;
		case LM75_SHUTDOWN:
			command[1] = 0x01;
			break;
	}
	
	HAL_I2C_Master_Transmit(hi2c, LM75_ADDRESS, command, 2, 100);
}