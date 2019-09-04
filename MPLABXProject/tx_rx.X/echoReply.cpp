/* 
 * File:   Principal.cpp
 * Author: Marcone
 *
 * Created on 28 de Agosto de 2019, 07:50
 */

#define F_CPU 16000000UL

#include <avr/io.h>

#define BAUD 9600
// set UBRR - pag 203 datasheet - Asynchronous Normal mode
#define MYUBRR (F_CPU/16/BAUD-1)

void USART_init() {
	// Set baud rate
    UBRR0 = MYUBRR;
    // Set frame format - pag 221 datasheet: 8 bits com 1 stop bit (00000110)
    UCSR0C = (3 << UCSZ00);
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void USART_tx(unsigned char data) {
	// Wait for empty transmit buffer. This method is bloking.
	// Verify 5th bit of UCSR0A Register (USART Data register empty)
	while ( !(UCSR0A & (1 << UDRE0)) );
    // Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_rx(void) {
    // Wait for data to be received
    // Verify 7th bit of UCSR0A Register
	while ( !(UCSR0A & (1 << RXC0)) );
    // Get and return received data from buffer
	return UDR0;
}

int main(void) {
	unsigned char input;
	USART_init();
	for(;;){
		input = USART_rx();
		USART_tx(input+1);
	}
    return 0;
}
