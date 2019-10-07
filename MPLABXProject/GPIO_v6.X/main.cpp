#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Timer.h"
#include <avr/interrupt.h>
#include "GPIO.h"
#include "GPIO_Port.h"
#include "uart.h"

 
GPIO_PORT::GPIO_Port * _Px = GPIO_PORT::AllPorts[9];
GPIO botao(54, GPIO::INPUT);		//PF0 
Timer t = Timer(1000);
uart serial(9600, uart::DATABITS_8, uart::NONE, uart::STOPBIT_1);

uint8_t px_value = 0;

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
        char msg[] = "O valor atual da porta PK é: ";
        serial.puts(msg);
    }
}
 
int main(void){
    _Px->dir_byte(1);
	t.addTimeout(2000, &timeout_handler);     
    sei();

    for(;;){
        t.timeoutManager();
    }
}
