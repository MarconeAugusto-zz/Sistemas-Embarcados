/* 
 * File:   Main.cpp
 * Author: marcone
 *
 * Created on 25 de Setembro de 2019, 08:11
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "GPIO.h"

GPIO p2(2, GPIO::OUTPUT);
GPIO p3(3, GPIO::OUTPUT);
GPIO p4(4, GPIO::OUTPUT);
GPIO p5(5, GPIO::OUTPUT);
 
void timeout2_handler(void){
	p2.toggle();
}
 
void timeout3_handler(void){
	p3.toggle();
}
 
void timeout4_handler(void){
	p4.toggle();
}
 
void timeout5_handler(void){
	p5.toggle();
}
 
 
Timer t = Timer(1000);

int main(int argc, char** argv) {
   
    sei();
	t.addTimeout(1000, &timeout2_handler);
	t.addTimeout(2000, &timeout3_handler);
	t.addTimeout(3000, &timeout4_handler);
	t.addTimeout(4000, &timeout5_handler);
	while(true){
		t.timeoutManager();
	}
    
    return 0;
}
