#include "stm32f1xx_hal.h"
#include "help_functions.h"

char s_humidity[15];
char s_temperature[15];
char s_bat_volt[15];
char s_lm75_temperature[15];

extern I2C_HandleTypeDef hi2c1;
extern _Bool ssd1306_init;

uint8_t UpdateDisplay(float humidity, float temperature, float bat_volt, float ln75_temp)
{

	if(ssd1306_init == 0){
			if(ssd1306_Init(&hi2c1) != 0){
				ssd1306_init = 0;
				Error_Handler();
				return 0;
			}
			ssd1306_Fill(Black);
			ssd1306_UpdateScreen(&hi2c1);
			ssd1306_init = 1;
	}
	sprintf(s_humidity, "%.0f%%", humidity);
	sprintf(s_temperature, "%.0fC", temperature);
	sprintf(s_bat_volt, "%.2fV", bat_volt);
	sprintf(s_lm75_temperature, "%.2fC", ln75_temp);
  ssd1306_SetCursor(90, 0);
  ssd1306_WriteString(s_bat_volt, Font_7x10, White);
	ssd1306_SetCursor(0, 18);
  ssd1306_WriteString(s_humidity, Font_7x10, White);
	ssd1306_SetCursor(0, 28);
  ssd1306_WriteString(s_temperature, Font_7x10, White);
	ssd1306_SetCursor(40, 28);
  ssd1306_WriteString(s_lm75_temperature, Font_7x10, White);
	ssd1306_SetCursor(0, 38);
  ssd1306_WriteString("DHT11", Font_7x10, White);
	ssd1306_SetCursor(40, 38);
  ssd1306_WriteString("LM75", Font_7x10, White);
	ssd1306_UpdateScreen(&hi2c1);
}
