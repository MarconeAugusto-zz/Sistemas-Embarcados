/* 
 * File:   main.cpp
 * Author: Marcone
 *
 * Created on 21 de Agosto de 2019, 08:31
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

/*
 * 
 */
int main() {
    
    DDRB = 0xFF; //Setup, registrador que configura a porta B como Output
    DDRD = 0x00;
    
    for(;;){
        
        if(PIND){
            PORTB = 0xFF;
            _delay_ms(1000);
        }else{
            PORTB = 0x00;

        }
    }
//00000001;
    return 0;
}

