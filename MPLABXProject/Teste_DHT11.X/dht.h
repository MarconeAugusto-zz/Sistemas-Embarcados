/* 
 * File:   dht.h
 * Author: marcone
 *
 * Created on 4 de Dezembro de 2019, 13:02
 */

#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>
#include <avr/io.h>

//setup port
#define DHT_DDR DDRE
#define DHT_PORT PORTE
#define DHT_PIN PINE
#define DHT_INPUTPIN PE4

//timeout retries
#define DHT_TIMEOUT 200

//functions
extern uint8_t dht_gettemperature(uint8_t *temperature);
extern uint8_t dht_gethumidity(uint8_t *humidity);
extern uint8_t dht_gettemperaturehumidity(uint8_t *temperature, uint8_t *humidity);

#endif
