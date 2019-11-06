/* 
 * File:   TWISlave.h
 * Author: marcone
 *
 * Created on 2 de Novembro de 2019, 16:04
 */

#ifndef TWISLAVE_H
#define	TWISLAVE_H
#define F_CPU 16000000UL                            /* Define CPU clock Frequency e.g. here its 16MHz */

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <string.h>
#include "UART.h"

class TWISlave{
public:
    TWISlave(uint8_t adress);
    ~TWISlave();
    void init();

private:    
    uint8_t Slave_Listen();
    uint8_t Slave_Transmit(char data);
    char Slave_Receive();
    char buffer[255];
    uint8_t count;
    UART uart;
};

#endif	/* TWISLAVE_H */

