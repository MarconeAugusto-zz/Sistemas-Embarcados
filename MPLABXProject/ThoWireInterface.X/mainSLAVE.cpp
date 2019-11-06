/* 
 * File:   main.cpp
 * Author: marcone
 *
 * Created on 24 de Outubro de 2019, 20:38
 */
#define F_CPU 16000000UL                            /* Define CPU clock Frequency e.g. here its 16MHz */
#include <avr/io.h>                                 
#include <util/delay.h>                             
#include <avr/interrupt.h>
#include "TWIMaster.h"
#include "TWISlave.h"
#include "GPIO.h"

/*          AT24C08A - 8k EEPROM 
Address    1 | 0 | 1 | 0 | A2 | P1 | P0 | R/W
 */

/*7bit address (R/W will be manage by master functions)*/
#define SLAVE_Address      0xB0            /* 10110000 = 0xB0*/
int main(int argc, char** argv){

    TWISlave slave(SLAVE_Address);

    sei();
    slave.init();

    return 0;
}

//ISR(TWI_vect){}
