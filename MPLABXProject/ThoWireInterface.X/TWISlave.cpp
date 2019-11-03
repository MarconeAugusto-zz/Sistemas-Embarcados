/* 
 * File:   TWISlave.cpp
 * Author: marcone
 * 
 * Created on 2 de Novembro de 2019, 16:04
 */

#include "TWISlave.h"

TWISlave::TWISlave(uint8_t slave_address) {
    TWAR = slave_address;                                   /* Atribuir endereço no registro de endereço TWI */
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);              /* Ativar TWI, Ativar geração de ack, limpar a interrupção TWI */
    rx_count = 0;
    tx_count = 0;    
}

TWISlave::~TWISlave() {}

/*Ouvir o Barramento
    - O dispositivo escravo sempre precisa ouvir o barramento TWI para verificar se ele é endereçado por qualquer mestre.
    - Quando endereçado, o bit TWINT é configurado. Então, precisa monitorar bit TWINT.
    Função Slave_Listen
    Argumento de entrada: - não possui nenhum argumento de entrada.
    Retorno: - retorna o status do evento.
 */

uint8_t TWISlave::Slave_Listen(){
	while(1)
	{
		uint8_t status;                                     /* Declarar variável */
        TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);    /* Obter reconhecimento, Ativar TWI, Limpar sinalizador de interrupção TWI*/
		while (!(TWCR & (1<<TWINT)));                       /* Aguarde para ser enderessado */
		status = TWSR & 0xF8;                               /* Leia o registro de status TWI com mascaramento de três bits inferiores */
		if (status == 0x60 || status == 0x68){              /* Verifique se o SLA + W foi recebido e retornado o ack (TWEA = 1) */
            return 0;                                       /* Se sim, retorne 0 para indicar que a confirmação retornou */
		}
        if (status == 0xA8 || status == 0xB0){              /* Verificar se o SLA + R foi recebido e retornado o ack (TWEA = 1) */
            return 1;                                       /* Se sim, retorne 1 para indicar que a confirmação retornou */
        }
        if (status == 0x70 || status == 0x78){              /* Verifique se uma chamada geral foi recebida e retornado o ack (TWEA = 1) */
            return 2;                                       /* Se sim, retorne 2 para indicar que a confirmação retornou */
		}else
            continue;                                       /* Senão continue */
	}
}

/*Transmitir dados
    - Depois de ser endereçado pelo mestre com endereço SLA + R, o escravo deve enviar os dados solicitados.
    - Os dados a serem enviados precisam ser gravados no registro TWDR.
    - Após a gravação dos dados, ative o TWI com confirmação e limpe o sinalizador de interrupção.
    - Se o reconhecimento não for recebido do mestre, o dispositivo escravo apaga a bandeira TWINT e novamente escuta o barramento.
    - Além disso, se RECIPITED START/STOP recebido, o dispositivo escravo apaga a bandeira TWINT e novamente escuta o barramento.
    Função Slave_Transmit
    Argumento de entrada: - possui argumento de entrada de dados de caracteres a serem enviados.
    Retorno: - retorna o status do evento.
 */
uint8_t TWISlave::Slave_Transmit(char data){
	uint8_t status;
	TWDR = data;                                            /* Grave dados no TWDR para serem transmitidos */
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);                  /* Ative o TWI e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));                           /* Aguarde até o TWI concluir seu trabalho atual (operação de gravação) */
	status = TWSR & 0xF8;                                   /* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status == 0xA0){                                    /* Verifique se STOP/REPEATED START foi recebido */
		TWCR |= (1<<TWINT);                                 /* Se sim, limpe o sinalizador de interrupção e retorne -1 */
		return -1;
	}
	if (status == 0xB8){                                    /* Verifique se os dados foram transmitidos e a confirmação ack recebida */
		return 0;                                           /* Se sim, retorne 0 */
	}
    if (status == 0xC0){                                    /* Verifique se os dados foram transmitidos e a confirmação nack recebida */
		TWCR |= (1<<TWINT);                                 /*  Se sim, limpe o sinalizador de interrupção e retorne -2 */
		return -2;
	}
	if (status == 0xC8){                                    /* Se o último byte de dados transmitido com confirmação recebeu TWEA = 0 */
        return -3;                                          /* Se sim, retorne -3 */
	}else                                                   /* else retorna -4 */
        return -4;
}

/*Receber dados
    - Depois de ser endereçado pelo mestre com o endereço SLA + W, o escravo precisa receber dados enviados pelo mestre.
    - Após cada byte recebido, o escravo precisa retornar o reconhecimento sobre o domínio.
    - Se START / STOP REPETIDO for recebido, o dispositivo escravo apagará a bandeira TWINT e ouvirá novamente o barramento.
    - Função Slave_Recieve
    Argumento de entrada: - não possui argumento de entrada.
    Retorno: - retorna dados recebidos ou status do evento.
 */
char TWISlave::Slave_Receive(){
	uint8_t status;                                         /* Declarar variável */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);                    /* Ativar TWI, gerador de ack e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));                           /* Aguarde até o TWI concluir seu trabalho atual (operação de leitura) */
	status = TWSR & 0xF8;                                   /* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status == 0x80 || status == 0x90)                   /* Verifique se os dados foram recebidos e ack retornado (TWEA = 1) */
	return TWDR;                                            /* Se sim, retorne os dados recebidos */
	if (status == 0x88 || status == 0x98)                   /* Verifique se os dados foram recebidos, nack retornou e passou para o modo escravo não endereçado */
	return TWDR;                                            /* Se sim, retorne os dados recebidos */
	if (status == 0xA0){                                    /* Verifique se foi recebido STOP/REPEATED START */
		TWCR |= (1<<TWINT);                                 /* Se sim, limpe o sinalizador de interrupção e retorne 0 */
		return 0;
	}else
        return -1;                                          /* Outro retorno -1 */
}

void TWISlave::init() {
    char byte;
	while (1){
		switch(Slave_Listen()){                 /* Check for any SLA+W or SLA+R */
			case 0:
			{
                while(1){
                    byte = Slave_Receive();     /* Receive data byte*/
                    if(byte == -1)
                        continue;
                    if(byte != 0)
                        break;
                    rx_buffer[rx_count] = byte;
                    rx_count++;
                    if(rx_count == 255)
                        rx_count = 0;
                }
                break;
			}
			case 1:
			{
                tx_count = Slave_Receive();     /* Receive reg to read*/
                if (tx_count == 255)
                    tx_count = 0;
                while(1){
                    uint8_t Ack_status = Slave_Transmit(data[tx_count]);
                    if(Ack_status == -2)
                        break;
                    tx_count++;
                    if (tx_count == 255)
                        tx_count = 0;
                }
				break;
			}
			default:
				break;
		}
	}
}
