#define F_CPU 16000000UL

#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>
#include "LCD.h"
#include "UART.h"
#include <avr/interrupt.h>

int main() {

	LCD display = LCD();
    UART uart(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
    
	sei();

	display.LCD_Init();
	while(1) {
        display.LCD_Clear();
        display.LCD_String("   ESCREVENDO");	/* write string on 1st line of LCD*/
        display.LCD_Command(0xC0);		/* Go to 2nd line*/
        display.LCD_String("    LINHA 2");	/* Write string on 2nd line*/
        uart.puts("Teste");
        _delay_ms(1000);
        
    }
}
