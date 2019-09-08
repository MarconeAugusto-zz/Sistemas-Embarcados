/* 
 * File:   Temp_ADC.cpp
 * Author: marcone
 *
 * Created on 6 de Setembro de 2019, 19:15
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BAUD 9600 // Define baudrate
#define MYUBRR (F_CPU/16/BAUD-1) // Define a frequência de oscilação

//Inicia a interface serial
void uart_init(){
    // Define a frequência de oscilação
	UBRR0 = MYUBRR;				
	// Habilita RX e TX
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); 
	// Set frame format - pag 221 datasheet: 8 bits com 1 stop bit (00000110)
    UCSR0C = (3 << UCSZ00);
}

//Inicia a conversão analógioco para digital
void adc_init(void){
    // Determina o fator de divisão como 128
	ADCSRA |= ((1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0));
    // Define a tensão de referencia do AVCC (5V)
	ADMUX |= (1 << REFS0);    
    // ADC Enable, ativa o ADC
	ADCSRA |= (1 << ADEN); 
    // Não é necessário alterar nenhum valor MUX para usar a entrada A0
}

void uart_transmit(char *data){
     for (int i=0;data[i]!=0;i++) {
        // Aguarda o buffer de transmissão ficar vazio
        while ( !(UCSR0A & (1 << UDRE0)) );
        // Armazena os dados no buffer, transmite os dados
        UDR0 = data[i];
    }
}

double analog_read(){
	double val;
    // Iniciar conversões A2D
	ADCSRA |= (1 << ADSC);
	while ( !(ADCSRA & (1 << ADIF)) );
	val = ADC;
    // Termina a leitura
	ADCSRA &= ~(1 << ADSC);
	return val;
}

double rms_read(int repeat) {
	double accumulated = 0;
	for(int n=0;n<repeat;n++) {
		accumulated += analog_read();
	}
	return accumulated/repeat;
}

double calculaTemp(double Rs){ // Equação de Steinhart-Hart
    double A = 1.1122e-03, B = 2.3758e-04, C = 0.6852e-07;
    double temperatura = 1/(A + (B*log(Rs))+ C*pow(log(Rs),3))-273.15; 
    return temperatura;  
}


int main(){
	uart_init();	// Inicia interface de comunicação
	adc_init();		// Inicia interface de leitura ADC
    
	double val = 0,Vs = 0;
    char  buffer_temp[5];
    //char buffer_dig[5], buffer_analog[5], buffer_resistencia[5];
	
    while (true){
        // Converte valor lido para RMS
        val = rms_read(100);	
        /*
        // Converte o valor double para um vetor char
        dtostrf(val,4,2,buffer_dig);	
        char str2[18] = "\n Analog_read(): ";
        uart_transmit(str2);
        uart_transmit(buffer_dig);
        */
        // Converte valor RMS para digital
        Vs = val*(5.0/1023.0);
        /*
        // Converte o valor double para um vetor char
        dtostrf(Vs,10,3,buffer_analog);
        char str3[18] = "\n Digital: ";
        uart_transmit(str3);
        uart_transmit(buffer_analog);
        */
        
        // calcula o valor da resistencia
        double Rs = ((50000/Vs)-10000);
        /*
        // Converte o valor double para um vetor char
        dtostrf(Rs,5,3,buffer_resistencia);
        char str[18] = "\n Resistencia: ";
        uart_transmit(str);
        uart_transmit(buffer_resistencia);
        */
        
        // calcula a temperatura
        double temperatura = calculaTemp(Rs);
        
        // Converte o valor double para um vetor char
        dtostrf(temperatura,4,2,buffer_temp);
        char str1[16] = "\nTemperatura = ";
        uart_transmit(str1);
        uart_transmit(buffer_temp);
            
        _delay_ms(3000);
		}
}
