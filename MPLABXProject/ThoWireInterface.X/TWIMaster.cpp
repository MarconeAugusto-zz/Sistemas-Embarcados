/* 
 * File:   TWIMaster.cpp
 * Author: marcone
 * 
 * Created on 30 de Outubro de 2019, 08:36
 */

#include "TWIMaster.h"

TWIMaster::TWIMaster(BusSpeed bs) {  // speed, modo (leitura/ escrita), quantidade de escravos, e array de endereços de escravos
    uint16_t speed;
    if(bs == 0){
        speed = 100000UL;
    }
    if(bs == 1){
        speed = 400000UL;
    }
    TWBR = ((F_CPU/speed)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))));
}

TWIMaster::TWIMaster(const TWIMaster& orig) {
}

TWIMaster::~TWIMaster() {
}

