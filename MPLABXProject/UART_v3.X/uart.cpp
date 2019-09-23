/* 
 * File:   uart.cpp
 * Author: marcone
 * 
 * Created on 18 de Setembro de 2019, 08:11
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

# define F_CPU 1600000UL

uart::uart(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb) {
	_has_data = false;
	UBRR0 = (F_CPU/16/baud-1);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // RXCIE0 bit interrupção
	UCSR0C = db|parity|sb;
}

uart::~uart(){}

uint8_t uart::get() {
	_has_data = false;
	return _rx_buffer.pop();
}

void uart::put(uint8_t data) {
	_tx_buffer.push(data);
	UCSR0B |= (1<<UDRIE0);
}

bool uart::has_data(){
	return _has_data;
}

void uart::rxc_isr_handler(){
	_rx_buffer.push((uint8_t)UDR0);
	_has_data = true;
}

void uart::udre_isr_handler(){
	UDR0 = _tx_buffer.pop();
	UCSR0B &= ~(1<<UDRIE0);
}

ISR(USART0_RX_vect){
	uart::rxc_isr_handler();
}

ISR(USART0_UDRE_vect){
	uart::udre_isr_handler();
}