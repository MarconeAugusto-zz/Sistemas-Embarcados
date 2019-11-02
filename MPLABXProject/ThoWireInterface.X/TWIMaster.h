/* 
 * File:   TWIMaster.h
 * Author: marcone
 *
 * Created on 30 de Outubro de 2019, 08:36
 */

#ifndef TWIMASTER_H
#define	TWIMASTER_H

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

class TWIMaster {
    char enderecos[];
public:
    enum BusSpeed {
        SLOW = 0,   //100 KHz
        FAST = 1    //400 KHz
    };
    enum Modo {
        READ = 0,   //Leitura
        WRITE = 1    //Escrita
    };

    //n�o faz muito sentido passar o modo no construtor... 
    //devido a op��o de enviar e receber do slave
    TWIMaster(BusSpeed bs, uint8_t n_slaves,char *enderecos); //passar a freq da comunica��o e o endere�o dos slaves;
    ~TWIMaster();
    //passar a posi��o do vetor de endere�os correspondente ao Slave desejado e os dados;
    void masterSend(const char* data, uint8_t posicao);
    //passar a posi��o do vetor de endere�os correspondente ao endere�o do Slave desejado
    uint8_t masterReceive(uint8_t posicao);
    
private:
};

#endif	/* TWIMASTER_H */

