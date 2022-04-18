#ifndef _LM75_H
#define _LM75_H

#include "stm32f1xx_hal.h"

#ifndef LM75_ADDRESS
#define LM75_ADDRESS			((0x48 | 0x00) << 1) //0x10010000
#endif // LM75_ADDRESS


#ifndef LM75_RESPONSE
enum LM75_SLEEP_MODE {
	LM75_NORMAL,
	LM75_SHUTDOWN
};
#endif // LM75_RESPONSE

float lm75_read_temp(I2C_HandleTypeDef *hi2c);
void lm75_sleep_mode(I2C_HandleTypeDef *hi2c, enum LM75_SLEEP_MODE mode);
void lm75_write_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp);
void lm75_write_shutdown_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp);
void lm75_write_turn_on_temperature(I2C_HandleTypeDef *hi2c, uint8_t reg, float temp);

#endif  // _LM75_H
