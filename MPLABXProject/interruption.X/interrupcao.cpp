#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 9600
// set UBRR - pag 203 datasheet - Asynchronous Normal mode
#define MYUBRR (F_CPU/16/BAUD-1)

void Init(){
    //Setup, registrador que configura o bit 7 da porta B como Output (1)
    DDRB |= (1 << 7);
    //Setup, registrador que configura o bit 2 da porta E como Input (0)
    DDRE &= ~(1 << 4);
    // Set baud rate
    UBRR0 = MYUBRR;
    // Set frame format - pag 221 datasheet: 8 bits com 1 stop bit (00000110)
    UCSR0C = (3 << UCSZ00);
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // onfigurando as interrupções
    DDRB |= (1 << 7);
    DDRE &= ~(1 << 4);
    EICRB |= (3 << ISC40);
    EIMSK |= (1 << INT4);
            
} 

void USART_tx(unsigned char data) {
	// Wait for empty transmit buffer. This method is bloking.
	// Verify 5th bit of UCSR0A Register (USART Data register empty)
	while ( !(UCSR0A & (1 << UDRE0)) );
    // Put data into buffer, sends the data
	UDR0 = data;
}

int main() {
    Init();
    sei();
    while(true){
        PORTB |= (1 << 7); //Set o nível lógico 1 no PORTB_7 e ascende o LED
        _delay_ms(1000);
        PORTB &= ~(1 << 7); ///Set o nível lógico 0 no PORTB_7 e apaga o LED
        _delay_ms(1000);
    }
    return 0;
}

ISR(INT4_vect){
    USART_tx('p');
}
