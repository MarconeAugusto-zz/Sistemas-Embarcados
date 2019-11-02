/* 
 * File:   TWISlave.h
 * Author: marcone
 *
 * Created on 2 de Novembro de 2019, 16:04
 */

#ifndef TWISLAVE_H
#define	TWISLAVE_H

class TWISlave {
public:
    TWISlave(uint8_t adress);
    ~TWISlave();
    uint8_t slaveSend(const char *data);
    char slaveReceive();
private:

};

#endif	/* TWISLAVE_H */

