#define F_CPU 16000000UL
//#define F_CPU 1000000UL

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART.h"
#include "dht.h"

int main(void)
{
	//init uart
    UART uart(1200, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
	char printbuff[100];

	//init interrupt
	sei();

	uint8_t temperature = 0;
	uint8_t humidity = 0;

	for (;;) {
		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {
            _delay_ms(1000);
			itoa(temperature, printbuff, 10);
			uart.puts("temperature: "); uart.puts(printbuff); uart.puts("C");uart.puts("\r\n");
			_delay_ms(100);
            itoa(humidity, printbuff, 10);
			uart.puts("humidity: "); uart.puts(printbuff); uart.puts("%RH");uart.puts("\r\n");
            _delay_ms(100);
        }
        if(dht_gethumidity(&humidity) != -1){
            itoa(humidity, printbuff, 10);
			uart.puts("humidity: "); uart.puts(printbuff); uart.puts("%RH");uart.puts("\r\n");
            _delay_ms(100);
            
        }else {
			uart.puts("error"); uart.puts("\r\n");
		}
		uart.puts("\r\n");
		_delay_ms(1500);
	}
	
	return 0;
}