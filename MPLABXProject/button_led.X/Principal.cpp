/* 
 * File:   Principal.cpp
 * Author: Marcone
 *
 * Created on 26 de Agosto de 2019, 07:40
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main() {
    //Setup, registrador que configura o bit 7 da porta B como Output (1)
    DDRB |= (1 << 7); 
    //Setup, registrador que configura o bit 6 da porta B como Input (0)
    DDRB &= ~(1 << 6);
    
    while(true){
        
        if(PINB & (1 << 6)){//Fazer uma AND com o PINB, para ler o valor da entrada
            PORTB |= (1 << 7); //Set o nível lógico 1 no PORTB_7 e ascende o LED
            //_delay_ms(1000);
        }else{
            PORTB &= ~(1 << 7); ///Set o nível lógico 0 no PORTB_7 e apaga o LED
        }
    }
    
    return 0;
}
