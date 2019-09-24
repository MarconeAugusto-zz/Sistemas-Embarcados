#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


#include "GPIO.h"
 
 
////LEDS PLACA (acende com '0')
GPIO led0(0, GPIO::OUTPUT);		//PE0
GPIO led1(1, GPIO::OUTPUT);		//PE1
 
//LEDS PLACA (acende com '1')
GPIO led13(13, GPIO::OUTPUT);	//PB7
 
//Adicionar LED
GPIO led4(4, GPIO::OUTPUT);		//PG5
GPIO led6(6, GPIO::OUTPUT);		//PH0

GPIO led19(19, GPIO::OUTPUT);
GPIO led25(25, GPIO::OUTPUT);
GPIO led33(33, GPIO::OUTPUT);
GPIO led38(38, GPIO::OUTPUT);
GPIO led41(41, GPIO::OUTPUT);
GPIO led49(49, GPIO::OUTPUT);
GPIO led55(55, GPIO::OUTPUT);
GPIO led62(62, GPIO::OUTPUT);
GPIO led69(69, GPIO::OUTPUT);
 
int main(void){
 
	UCSR0B = 0;
 
	led0.set(1);
	led1.set(1);
	led6.clear();
	led4.clear();
	led13.clear();
	_delay_ms(1000);
	led0.clear();
	led1.clear();
	led6.set(1);
	led4.set(1);
	led13.set(1);
	_delay_ms(1000);
	led19.set(1);
	led25.set(1);
	led33.set(1);
	led38.set(1);
	led41.set(1);
	led49.set(1);
	led55.set(1);
	led62.set(1);
	led69.set(1);
    
	while (1){
		led0.toggle();
		led1.toggle();
		led6.toggle();
		led4.toggle();
		led13.toggle();
		led19.toggle();
		led25.toggle();
		led33.toggle();
		led38.toggle();
		led41.toggle();
		led49.toggle();
		led55.toggle();
		led62.toggle();
		led69.toggle();
		_delay_ms(1000);
	}
 
}
