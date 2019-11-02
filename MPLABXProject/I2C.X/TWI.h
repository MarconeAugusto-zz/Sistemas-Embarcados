/* 
 * File:   TWI.h
 * Author: marcone
 *
 * Created on 27 de Outubro de 2019, 15:57
 */

#ifndef TWI_H
#define F_CPU 16000000UL	/* Define CPU clock Frequency e.g. here its 16MHz */

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#define SCL_CLK 400000L		/* Define SCL clock frequency 400KHz */
#define	TWI_H
#define BITRATE(TWSR) ((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) //passar o valor pelo construtor

class TWI {
public:
    //Master
    TWI();  //mudar o construtor
    ~TWI();
    uint8_t Start(char write_address);
    uint8_t Repeated_Start(char read_address);
    void Stop();
    void Start_Wait(char write_address);
    uint8_t Write(char data);
    char Read_Ack();
    char Read_Nack();
    //Slave
    void Slave_Init(uint8_t slave_address);
    uint8_t Slave_Listen();
    uint8_t Slave_Transmit(char data);
    char Slave_Receive();
};

#endif	/* TWI_H */

