#ifndef __DHT_H__
#define __DHT_H__

#include <stdio.h>
#include <mega8.h>

//Port where DHT sensor is connected
#define DHT_DDR DDRC
#define DHT_PORT PORTC
#define DHT_PIN PINC
#define DHT_INPUTPIN 0        /// Khai Bao Chan noi vao VXL

//Define sensor type
#define DHT_DHT11 0
#define DHT_DHT22 1
#define DHT_TYPE DHT_DHT22

//timeout retries
#define DHT_TIMEOUT 200

//functions
#if DHT_TYPE == 1   // DHT ==1 ---> DHT22, DHT ==0 --> DHT11
extern char dht_GetTempUtil(int *temperature, int *humidity);
#elif DHT_TYPE == 0
extern char dht_GetTempUtil(char *temperature, char *humidity);
#endif

#endif