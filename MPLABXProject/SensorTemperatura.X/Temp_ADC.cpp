/* 
 * File:   Temp_ADC.cpp
 * Author: marcone
 *
 * Created on 6 de Setembro de 2019, 19:15
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD 9600		// Define baudrate
#define MYUBRR (F_CPU/16/BAUD-1) // Define a frequ�ncia de oscila��o

void Init(){
    // Define a frequ�ncia de oscila��o
	UBRR0 = MYUBRR;				
	// Habilita RX e TX
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); 
	// Set frame format - pag 221 datasheet: 8 bits com 1 stop bit (00000110)
    UCSR0C = (3 << UCSZ00);
}

void USART_Transmit(char *data ){
	//while ( !( UCSR0A & (1<<UDRE0)) ); 	// Aguarda o buffer de transmiss�o ficar vazio
	//UDR0 = data; // Armazena os dados no buffer, transmite os dados
     for (int i=0;data[i]!=0;i++) {
        while ( !(UCSR0A & (1 << UDRE0)) );
        UDR0 = data[i];
    }
}

uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xE0;           	// Limpa bits de MUX0-4
	ADMUX |= channel & 0x07;   	// Define um novo canal a ser lido by setting bits MUX0-2
	ADCSRB = channel & (1<<3); 	// Define MUX5 como zero
	ADCSRA |= (1<<ADSC);      	// Inicia uma nova convers�o
	while(ADCSRA & (1<<ADSC));  	// Aguarda at� que a convers�o seja finalizada
	return ADCW; 			// Retorna o valor ADC do canal escolhido
}

void adc_init(void){
    // Determina o fator de divis�o como 128
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
    // Define a tens�o de referencia do AVCC (5V)
	ADMUX |= (1 << REFS0);    
    // ADC Enable, ativa o ADC
	ADCSRA |= (1 << ADEN); 
    // Inicia uma convers�o incial
	//ADCSRA |= (1<<ADSC);	
}


double RMS (int repeat){
	double digital_value;
	//double average;
	double accumulated = 0;
    // Canal utilizado para leitura ADC (Porta A0)
	uint8_t channel = 0;	
	for (int i = 0; i <= repeat; i++){
		digital_value = read_adc(channel);
		accumulated = (digital_value*digital_value) + accumulated;
	}
	return sqrt(accumulated/repeat);
}

double to_analog(double valor){
	double analogico;
	analogico = valor*(5.0/1023.0);
	return analogico;
}


int main(){
	Init();	// Inicia interface de comunica��o
	adc_init();		// Inicia interface de leitura ADC
    
	double val = 0;
	double val_analogico = 0;

	while (true){
        // Converte valor lido para RMS
        val = RMS(100);			
        // Converte valor RMS para anal�gico
        val_analogico = to_analog(val); 
        char buffer_dig[5], buffer_analog[5];
        //char buffer_analog[5];
        // Converte o valor double para um vetor char
        dtostrf(val,5,3,buffer_dig);			
        dtostrf(val_analogico,5,3,buffer_analog);

        char palavra_dig[10] = "Digital: \n";
        USART_Transmit(palavra_dig);


        _delay_ms(1000);
		}
}
