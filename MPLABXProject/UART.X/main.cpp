#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
 
UART uart(115200, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
 
int main(){
	uint8_t echo;
	char msg[] = "Byte Received: ";
 
	while(1){
		echo = uart.get();
		uart.puts(msg);
		uart.put(echo);
		uart.put('\n');
	}
 
	return 1;
}