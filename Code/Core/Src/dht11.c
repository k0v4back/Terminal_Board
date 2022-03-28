#include "dht11.h"
#include "delay.h"

/*
dfdf
*/
uint8_t dht11_start(struct dht11_sensor * sensor)
{
	output_mode(sensor); /* set output mode */
	
	/* Sending Ready to start working from MCU */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	
	input_mode(sensor); /* set input mode */
	
	/* Checking if the sensor responded */
	delay_us(40);
	if(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_SET)
			return ERROR_DHT11_NOT_RESPONSE_1;
	delay_us(80);
	if(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_RESET)
			return ERROR_DHT11_NOT_RESPONSE_2;
	
	/* Wait until the sensor starts transmitting data */
	while(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin)){};
		
	return DHT11_SUCCESS_RESPONSE;
}

static void input_mode(struct dht11_sensor * sensor)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = sensor->dht_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(sensor->dht_port, &GPIO_InitStruct);
}

static void output_mode(struct dht11_sensor * sensor)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	HAL_GPIO_WritePin(sensor->dht_port, sensor->dht_pin, GPIO_PIN_SET);
	
  GPIO_InitStruct.Pin = sensor->dht_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
  HAL_GPIO_Init(sensor->dht_port, &GPIO_InitStruct);
}