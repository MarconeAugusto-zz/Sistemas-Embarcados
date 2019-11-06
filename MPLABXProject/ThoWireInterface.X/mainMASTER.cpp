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

/*7bit address (R/W will be manage by master functions)*/
#define EEPROM_1_Address      0xA0            /* 10100000 = 0xA0*/
#define EEPROM_2_Address      0xA8            /* 10101000 = 0xA8*/
#define SLAVE_Address         0xB0            /* 10110000 = 0xB0*/

UART uart(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
GPIO EEPROM_1(54, GPIO::OUTPUT);                    /* Utilizado para controle do endere�amento da EEPROM_1 - PF0 */
GPIO EEPROM_2(55, GPIO::OUTPUT);                    /* Utilizado para controle do endere�amento da EEPROM_2 - PF1 */
    
int main(int argc, char** argv){
    EEPROM_1.set(0);                                /* Controla o bit A2 da EEPROM 1 */
    EEPROM_2.set(1);                                /* Controla o bit A2 da EEPROM 2 */

    TWIMaster master(SLOW_TWI);
    char  input[] = " ...";
    char  output[5];

    sei();
    while (1) {
        if (uart.has_data()) {
            input[0] = uart.get();
            master.write(input,5,SLAVE_Address,0x00);
            master.receive(output,5,SLAVE_Address,0x00);
            uart.puts(output);
        }
    }          

    return 0;
}