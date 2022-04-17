#include "lm75.h"

static uint8_t lm75_write_command(I2C_HandleTypeDef *hi2c, uint8_t command)
{
	return HAL_I2C_Mem_Write(hi2c, LM75_ADDRESS, 0x00, 1, &command, 1, 10);
}

static uint16_t lm75_read_command(I2C_HandleTypeDef *hi2c, uint8_t command, uint16_t data)
{
	HAL_I2C_Master_Receive(hi2c, LM75_ADDRESS, (uint8_t*)&data, 2, 10);
	return data;
}

float lm75_read_temp(I2C_HandleTypeDef *hi2c)
{
	uint16_t data;
	lm75_write_command(hi2c, 0x00);

	data = lm75_read_command(hi2c, 0x00, data);
	data = ((( data >> 8 ) | ( data << 8 )) >> 7) & 0x01FF;

	if(data & 0x0100 ){
		data = (0x01FE ^ data) + 2;
		return (float)( data * (-0.5f) );
	}
	else{
		return (float)( data * 0.5f );
	}
}
