#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Timer.h"
#include <avr/interrupt.h>
#include "GPIO.h"
#include "GPIO_Port.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>

 
GPIO_PORT::GPIO_Port * _Px = GPIO_PORT::AllPorts[9];
GPIO botao(54, GPIO::INPUT);		//PF0 
Timer t = Timer(1000);
uart serial(9600, uart::DATABITS_8, uart::NONE, uart::STOPBIT_1);
const char msg[] = "O valor atual da porta PK e: ";

uint8_t px_value = 1;

void timeout_handler(void){
    _Px->write_byte(px_value);
    if(px_value == 128){
        px_value = 1;
    }
    else{
        px_value <<= 1;        
    }
}

void check_botao(){
    if(botao.get()){
        serial.puts(msg);
        /*
        char valor[5];
        sprintf(valor,"%d\n",px_value);         
         */
        char valor[5];
        itoa(px_value,valor,10);
        valor[3]='\n';
        valor[4]='\0';        
        serial.puts(valor);
    }
}
 
int main(void){
    _Px->dir_byte(1);
	t.addTimeout(2000, &timeout_handler); 
	t.addTimeout(200, &check_botao);     
    sei();

    for(;;){
        t.timeoutManager();
    }
}
