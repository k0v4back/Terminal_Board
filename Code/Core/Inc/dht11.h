#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f1xx_hal.h"

#ifndef DHT11_RESPONSE
enum DHT11_RESPONSE {
	ERROR_DHT11_FIRST_INIT,
	ERROR_DHT11_SECOND_INIT,
	SUCCESS_DHT11_INIT
};
#endif // DHT11_RESPONSE

/**
 * struct dht11_sensor - dht11 configuration parameters.
 * @dht_port:		All the possible ports like GPIOA, GPIOB, ...,
 * @clr_mask:		All the possible pins like GPIO_PIN_0, GPIO_PIN_1, ...,
 */
struct dht11_sensor {
	GPIO_TypeDef 				*dht_port;
	uint16_t 						dht_pin;
	float 							humidity;
	float 							temperature;
};

uint8_t dht11_start(struct dht11_sensor * sensor);
uint8_t dht11_read_byte(struct dht11_sensor * sensor);
void dht11_read(struct dht11_sensor * sensor);
static void input_mode(struct dht11_sensor * sensor);
static void output_mode(struct dht11_sensor * sensor);

#endif  // _DHT11_H
