#include "dht11.h"
#include "delay.h"

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
			return ERROR_DHT11_FIRST_INIT;
	
	delay_us(80);
	if(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_RESET)
			return ERROR_DHT11_SECOND_INIT;
	
	/* Wait until the sensor starts transmitting data (pull the line to the ground) */
	while(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_SET){};
		
	return SUCCESS_DHT11_INIT;
}

uint8_t dht11_read_byte(struct dht11_sensor * sensor)
{
	uint8_t i = 8, byte = 0;
	
	input_mode(sensor); /* set input mode */
	
	while(i--){
		/* Wait until pull the line to up */
		while(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_RESET){};
			
		delay_us(40);
			
		if(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_SET){
			byte |= (1 << i);
			/* Wait until pull the line to ground */
			while(HAL_GPIO_ReadPin(sensor->dht_port, sensor->dht_pin) == GPIO_PIN_SET){};
		}
	}
	
	return byte;
}

void dht11_read(struct dht11_sensor * sensor)
{
	uint8_t ret = 0;
	uint8_t data[5] = {0};
	
	ret = dht11_start(sensor);
	if(ret != SUCCESS_DHT11_INIT){
		/* ******* */
		return;
	}
	
	/* Read bytes */
	for(uint8_t i = 0; i < 5; i++){
		data[i] = dht11_read_byte(sensor);
	}
	
	/* Check control summ */
	if((data[0] + data[1] + data[2] + data[3]) == data[4]){
		sensor->humidity = data[0];
		sensor->temperature = data[2];
	}
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
