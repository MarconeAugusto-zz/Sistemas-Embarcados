/* 
 * File:   UART.cpp
 * Author: guilherme
 * 
 * Created on 16 de Setembro de 2019, 09:16
 */

#include "UART.h"

UART::UART(uint32_t baud,DATABITS_t db,PARITY_t parity,STOPBITS_t sb){
		UBRR0 = (16000000/16/baud-1);
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		UCSR0C = db|parity|sb;
}

UART::~UART() {
}

void UART::put(uint8_t data){
	while ( !( UCSR0A & (1<<UDRE0)) ); 	// Aguarda o buffer de transmissão ficar vazio
	UDR0 = data; // Armazena os dados no buffer, transmite os dados
}

uint8_t UART::get(){
	while (!(UCSR0A & (1<<RXC0))); 	// Aguarda que dados sejam recebidos
	return UDR0;
}

void UART::puts(const char * data) {
	for(int i = 0; data[i]!=0;i++)
		put((uint8_t) data[i]);
}