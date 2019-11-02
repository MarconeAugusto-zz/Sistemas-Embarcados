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
public:
    enum BusSpeed {
        SLOW = 0,   //100 KHz
        FAST = 2    //400 KHz
    };
    enum Modo {
        READ = 0,   //Leitura
        WRITE = 1    //Escrita
    };
    TWIMaster(BusSpeed bs, Modo md); //passar a freq da comunicação e o endereço dos slaves;
    TWIMaster(const TWIMaster& orig);
    virtual ~TWIMaster();
private:

};

#endif	/* TWIMASTER_H */

