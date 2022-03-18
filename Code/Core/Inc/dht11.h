#ifndef _DHT11_H
#define _DHT11_H

#include "stm32f1xx_hal.h"

#ifndef ERROR_DHT11_NOT_RESPONSE_1
#define ERROR_DHT11_NOT_RESPONSE_1        1
#endif // ERROR_DHT11_NOT_RESPONSE

#ifndef ERROR_DHT11_NOT_RESPONSE_2
#define ERROR_DHT11_NOT_RESPONSE_2        2
#endif // ERROR_DHT11_NOT_RESPONSE

#ifndef DHT11_SUCCESS_RESPONSE
#define DHT11_SUCCESS_RESPONSE        		3
#endif // DHT11_SUCCESS_RESPONSE

uint8_t dht11_start(void);

#endif  // _DHT11_H
