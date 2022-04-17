#ifndef _LM75_H
#define _LM75_H

#include "stm32f1xx_hal.h"

#ifndef LM75_ADDRESS
#define LM75_ADDRESS			((0x48 | 0x00) << 1) //0x10010000
#endif // LM75_ADDRESS


#ifndef LM75_RESPONSE
enum LM75_RESPONSE {
	ERROR_LM75_FIRST_INIT,
	ERROR_LM75_SECOND_INIT,
	SUCCESS_LM75_INIT
};
#endif // LM75_RESPONSE

static uint8_t lm75_write_command(I2C_HandleTypeDef *hi2c, uint8_t command);
static uint16_t lm75_read_command(I2C_HandleTypeDef *hi2c, uint8_t command, uint16_t data);
float lm75_read_temp(I2C_HandleTypeDef *hi2c);

#endif  // _LM75_H
