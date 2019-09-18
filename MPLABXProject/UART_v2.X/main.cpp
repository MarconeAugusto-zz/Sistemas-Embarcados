/* 
 * File:   main.cpp
 * Author: marcone
 *
 * Created on 18 de Setembro de 2019, 08:32
 */

#include <stdio.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

//# define F_CPU 1600000UL

//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    uart serial(9600, uart::DATABITS_8, uart::NONE, uart::STOPBIT_1);
	uint8_t info;
	sei();

	while(true){
		if(serial.has_data()){
			info = serial.get();
			serial.put(info);
			//_delay_ms(500);
		}
	}
    return 0;
}

