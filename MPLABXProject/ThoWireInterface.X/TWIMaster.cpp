/* 
 * File:   TWIMaster.cpp
 * Author: marcone
 * 
 * Created on 30 de Outubro de 2019, 08:36
 */

#include "TWIMaster.h"

TWIMaster::TWIMaster(BusSpeed bs, Modo md) {  // speed, modo (leitura/ escrita), quantidade de escravos, e array de endereços de escravos
    TWBR = ((F_CPU/bs)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))));
}

TWIMaster::TWIMaster(const TWIMaster& orig) {
}

TWIMaster::~TWIMaster() {
}

