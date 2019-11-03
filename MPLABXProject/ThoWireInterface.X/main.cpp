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
#include "UART.h"
#include "GPIO.h"

/*          AT24C08A - 8k EEPROM 
Address    1 | 0 | 1 | 0 | A2 | P1 | P0 | R/W
 */

#define EEPROM_1_Address      0xA0            /* 10100000 = 0xA0*/
#define EEPROM_2_Address      0xA9            /* 10101000 = 0xA8*/

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
GPIO EEPROM_1(54, GPIO::OUTPUT);                    /* Utilizado para controle do endereçamento da EEPROM_1 - PF0 */
GPIO EEPROM_2(55, GPIO::OUTPUT);                    /* Utilizado para controle do endereçamento da EEPROM_2 - PF1 */
    
int main(int argc, char** argv){
    EEPROM_1.set(0);                                /* Controla o bit A2 da EEPROM 1 */
    EEPROM_2.set(1);                                /* Controla o bit A2 da EEPROM 2 */

    TWIMaster master(FAST_TWI);
    char  input[1];
    char  output[1];

    sei();

    while (1) {
        if (uart.has_data()) {
            input[0] = uart.get();
            master.write(input,1,EEPROM_1_Address,0x00);
            master.receive(output,1,EEPROM_1_Address,0x00);
            uart.put(output[0]);
        }
    }
    return 0;
}