#ifndef _HELP_FUNCTIONS
#define _HELP_FUNCTIONS

#include "stm32f1xx_hal.h"
#include "main.h"
#include "ssd1306.h"
#include "fonts.h"
#include "dht11.h"

void UpdateDisplay(float humidity, float temperature, float bat_volt, float ln75_temp);

#endif  // _HELP_FUNCTIONS
