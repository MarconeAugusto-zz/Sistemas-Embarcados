/* 
 * File:   main.cpp
 * Author: marcone
 *
 * Created on 24 de Outubro de 2019, 20:38
 */
#define F_CPU 16000000UL                            /* Define CPU clock Frequency e.g. here its 16MHz */
#include <avr/io.h>                                 
#include <util/delay.h>                             
#include <avr/interrupt.h>
#include "TWI.h"
#include "UART.h"
#include "GPIO.h"

/*          AT24C08A - 8k EEPROM 
Address    1 | 0 | 1 | 0 | A2 | P1 | P0 | R/W
 */

#define EEPROM_1_Write_Address      0xA0            /* 10100000 = 0xA0*/
#define EEPROM_1_Read_Address		0xA1            /* 10100001 = 0xA1*/
#define EEPROM_2_Write_Address      0xA8            /* 10101000 = 0xA8*/
#define EEPROM_2_Read_Address		0xA9            /* 10101001 = 0xA9*/

UART serial(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
GPIO EEPROM_1(54, GPIO::OUTPUT);                    /* Utilizado para controle do endereçamento da EEPROM_1 - PF0 */
GPIO EEPROM_2(55, GPIO::OUTPUT);                    /* Utilizado para controle do endereçamento da EEPROM_2 - PF1 */
    
int main(int argc, char** argv){
    
    sei();
    char array[9] = "EEPROM 1";                     /* Declaração do array usado no teste */
    EEPROM_1.set(0);                                /* Controla o bit A2 da EEPROM 1 */
    char array2[9] = "EEPROM 2";                    /* Declaração do array usado no teste */
    EEPROM_2.set(1);                                /* Controla o bit A2 da EEPROM 2 */
    while(1){
        serial.puts("\n");                          /* Tirando o lixo da serial */
        serial.puts("\n");
        serial.puts("\n");
        _delay_ms(100);
        serial.puts("Iniciando...");
        _delay_ms(100);
        TWI twi;                                    /* Inicializando I2C */
        serial.puts("\n");
        twi.Start_Wait(EEPROM_1_Write_Address);     /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x00);                            /* Endereço de memória inicial para gravação de dados */
        serial.puts("Iniciando escrita... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Escrevendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array); i++){      /* Escrevendo array de dados */
            twi.Write(array[i]); 
            serial.put(array[i]);
            _delay_ms(500);
        }
        serial.puts("\n");
        twi.Stop();                                 /* Parando I2C */
        _delay_ms(100);
        serial.puts("Encerrando escrita...");
        serial.puts("\n");
        _delay_ms(100);
        twi.Start_Wait(EEPROM_1_Write_Address);     /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x00);                            /* Escreva o endereço da memória inicial */
        twi.Repeated_Start(EEPROM_1_Read_Address);  /* Repeat start I2C SLA+R */
        serial.puts("Iniciando leitura... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Lendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array); i++){      /* Lendo os dados com ack */
            serial.put(twi.Read_Ack());
            _delay_ms(500);
        }
        twi.Read_Nack();                            /* Lendo os dados com nack */
        serial.puts("\n");
        serial.puts("Encerrando...");
        _delay_ms(100);
        twi.Stop();                                 /* Parando I2C */
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        serial.puts("\n");                          /* Tirando o lixo da serial */
        serial.puts("\n");
        serial.puts("\n");
        _delay_ms(100);
        serial.puts("Iniciando...");
        _delay_ms(100);
        serial.puts("\n");
        twi.Start_Wait(EEPROM_2_Write_Address);     /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x20);                            /* Endereço de memória inicial para gravação de dados */
        serial.puts("Iniciando escrita... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Escrevendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array2); i++){      /* Escrevendo array de dados */
            twi.Write(array2[i]); 
            serial.put(array2[i]);
            _delay_ms(500);
        }
        serial.puts("\n");
        twi.Stop();                                 /* Parando I2C */
        _delay_ms(100);
        serial.puts("Encerrando escrita...");
        serial.puts("\n");
        _delay_ms(100);
        twi.Start_Wait(EEPROM_2_Write_Address);     /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x20);                            /* Escreva o endereço da memória inicial */
        twi.Repeated_Start(EEPROM_2_Read_Address);  /* Repeat start I2C SLA+R */
        serial.puts("Iniciando leitura... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Lendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array2); i++){      /* Lendo os dados com ack */
            serial.put(twi.Read_Ack());
            _delay_ms(500);
        }
        twi.Read_Nack();                            /* Lendo os dados com nack */
        serial.puts("\n");
        serial.puts("Encerrando...");
        _delay_ms(100);
        twi.Stop();                                 /* Parando I2C */
    }
    return 0;
}




//#define Slave_Write_Address		0x20
//#define Slave_Read_Address		0x21
//#define	count					10
//
//
//int main(int argc, char** argv) { 
//    UART serial(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
//	char info;
//	sei();
//    serial.puts("Iniciando Master \n");
//	TWI twi;								/* Initialize I2C */
//	
//	while(1){
//        serial.puts("Enviando: ");
//		twi.Start_Wait(Slave_Write_Address);/* Start I2C communication with SLA+W */
//		_delay_ms(5);
//		for (uint8_t i = 0; i < count ; i++){
//            serial.put(i);
//			twi.Write(i);					/* Send Incrementing count */
//			_delay_ms(500);
//		}
//		serial.puts("Recebendo: ");
//		twi.Repeated_Start(Slave_Read_Address);	/* Repeated Start I2C communication with SLA+R */
//		_delay_ms(5);
//		for (uint8_t i = 0; i < count; i++){
//			if(i < count - 1){
//				/* Read and send Acknowledge of data */
//                info = twi.Read_Ack();
//                serial.put(info);
//            }else{
//                /* Read and Not Acknowledge to data */
//                info = twi.Read_Nack();
//                serial.put(info);
//            }
//			_delay_ms(500);
//		}
//		twi.Stop();							/* Stop I2C */
//	}
//    return 0;
//}
        
        
//#define Slave_Address			0x20
//
//int main(int argc, char** argv) { 
//    UART serial(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
//    sei();
//	uint8_t count = 0;
//	TWI twi;
//	twi.Slave_Init(Slave_Address);
//	serial.puts("Iniciando Slave");
//	
//	while (1){
//		switch(twi.Slave_Listen()){				/* Check for any SLA+W or SLA+R */
//			case 0:
//			{
//                serial.puts("Recebendo: ");
//				do{
//					count = twi.Slave_Receive();/* Receive data byte*/
//                    serial.put(count);
//				} while (count != -1);			/* Receive until STOP/REPEATED START received */
//                    count = 0;
//                    break;
//			}
//			case 1:
//			{
//				uint8_t Ack_status;
//				serial.puts("Enviando: ");
//				do{
//					Ack_status = twi.Slave_Transmit(count);	/* Send data byte */
//					serial.put(count);
//					count++;
//				} while (Ack_status == 0);		/* Send until Acknowledgment is received */
//				break;
//			}
//			default:
//				break;
//		}
//	}
//    return 0;
//}

