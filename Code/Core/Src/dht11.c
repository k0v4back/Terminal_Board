#include "dht11.h"
#include "delay.h"

/*
dfdf
*/
uint8_t dht11_start(void)
{
	/* Sending Ready to start working from MCU */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	/* Checking if the sensor responded */
	delay_us(40);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15))
			return ERROR_DHT11_NOT_RESPONSE_1;
	delay_us(40);
	if(!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)))
			return ERROR_DHT11_NOT_RESPONSE_2;
	
	/* Wait until the sensor starts transmitting data */
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)){};
		
	return DHT11_SUCCESS_RESPONSE;
}