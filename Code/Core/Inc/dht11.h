#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f1xx_hal.h"
#include "main.h"

#ifndef ERROR_DHT11_NOT_RESPONSE_1
#define ERROR_DHT11_NOT_RESPONSE_1        1
#endif // ERROR_DHT11_NOT_RESPONSE

#ifndef ERROR_DHT11_NOT_RESPONSE_2
#define ERROR_DHT11_NOT_RESPONSE_2        2
#endif // ERROR_DHT11_NOT_RESPONSE

#ifndef DHT11_SUCCESS_RESPONSE
#define DHT11_SUCCESS_RESPONSE        		3
#endif // DHT11_SUCCESS_RESPONSE

struct dht11_sensor{
	GPIO_TypeDef *dht_port;				//GPIOA, GPIOB, ...,
	uint16_t dht_pin;							//GPIO_PIN_0, GPIO_PIN_1, ...,
};

uint8_t dht11_start(struct dht11_sensor * sensor);
static void input_mode(struct dht11_sensor * sensor);
static void output_mode(struct dht11_sensor * sensor);

#endif  // _DHT11_H
