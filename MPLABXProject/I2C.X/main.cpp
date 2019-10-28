/* 
 * File:   main.cpp
 * Author: marcone
 *
 * Created on 24 de Outubro de 2019, 20:38
 */
#define F_CPU 16000000UL					/* Define CPU clock Frequency e.g. here its 16MHz */
#include <avr/io.h>							/* Include AVR std. library file */
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
#include <avr/interrupt.h>
#include "TWI.h"
#include "UART.h"


#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21

//#define F_CPU 8000000UL		/* Define CPU clock Frequency 8MHz */

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1

int main(int argc, char** argv){
    UART serial(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
    char array[8] = "EEPROM";                /* Declaração do array usado no teste */
    sei();
    while(1){
        serial.puts("\n");
        serial.puts("\n");
        serial.puts("\n");                      /* Tirando o lixo da serial */
        serial.puts("\n");
        _delay_ms(1000);
        serial.puts("Iniciando...");
        _delay_ms(100);
        TWI twi;                                /* Inicializando I2C */
        serial.puts("\n");
        twi.Start(EEPROM_Write_Addess);         /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x00);                        /* Endereço de memória inicial para gravação de dados */
        serial.puts("Iniciando escrita... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Escrevendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array); i++){  /* Escrevendo array de dados */
            twi.Write(array[i]); 
            serial.put(array[i]);
            _delay_ms(500);
        }
        serial.puts("\n");
        twi.Stop();                             /* Parando I2C */
        _delay_ms(100);
        serial.puts("Encerrando escrita...");
        serial.puts("\n");
        _delay_ms(100);
        twi.Start(EEPROM_Write_Addess);         /* Inicia o I2C com o endereço de gravação do dispositivo */
        twi.Write(0x00);                        /* Escreva o endereço da memória inicial */
        twi.Repeated_Start(EEPROM_Read_Addess); /* Repeat start I2C SLA+R */
        serial.puts("Iniciando leitura... ");
        _delay_ms(100);
        serial.puts("\n");
        serial.puts("Lendo: ");
        _delay_ms(100);
        for (int i = 0; i<strlen(array); i++){  /* Lendo os dados com ack */
            serial.put(twi.Read_Ack());
            _delay_ms(500);
        }
        twi.Read_Nack();                        /* Lendo os dados com nack */
        serial.puts("\n");
        serial.puts("Encerrando...");
        _delay_ms(100);
        twi.Stop();                             /* Parando I2C */
    }
    return 0;
}



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

