/* 
 * File:   UART.h
 * Author: guilherme
 *
 * Created on 16 de Setembro de 2019, 09:16
 */

#ifndef UART_H
#define	UART_H

#include <avr/io.h>

class UART {
public:
    
enum DATABITS_t {
    DATABITS_5,
    DATABITS_6,
    DATABITS_7,
    DATABITS_8
};

enum PARITY_t {
    NONE,
    EVEN,
    ODD
};

enum STOPBITS_t {
    STOPBIT_1,
    STOPBIT_2
};

    UART(uint32_t baud,DATABITS_t db,PARITY_t parity,STOPBITS_t sb);
    ~UART();

    void put(uint8_t data);
    void puts(const char * data);
    uint8_t get();

private:    
    DATABITS_t db;
    uint32_t baud;
    PARITY_t parity;
    STOPBITS_t sb;
};

#endif	/* UART_H */

