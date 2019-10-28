/* 
 * File:   TWI.cpp
 * Author: marcone
 * 
 * Created on 27 de Outubro de 2019, 15:57
 */

#include "TWI.h"

TWI::TWI() {                                                /* TWI initialize function */
    TWBR = BITRATE(TWSR = 0x00);							/* Get bit rate register value by formula */
}

TWI::~TWI() {}

/*INÍCIO(S)
    - Condição START emitida pelo mestre.
    - É gerado pela transição Alto para Baixo no SDA enquanto o SCL é Alto.
    - Enquanto o barramento estiver livre, o dispositivo mestre emite uma condição START com o endereço do dispositivo escravo (SLA) para iniciar a transmissão.
    Função Start - inicia a condição START
    Argumento de entrada: - possui argumento de entrada do endereço de gravação do dispositivo escravo (SLA + W).
    Retorno: - retorna o status do evento.
 */
uint8_t TWI::Start(char write_address){						/* TWI start function */
	uint8_t status;											/* Declarar variável */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Ative o TWI, gere condição de início e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até que o TWI termine seu trabalho atual (condição inicial) */
	status = TWSR & 0xF8;									/* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status != 0x08){									/* Verificar a condição de início foi transmitida com sucesso ou não? */
        return 0;											/* Caso contrário, retorne 0 para indicar falha na condição de início */
	}
    TWDR = write_address;									/* Se sim, escreva SLA + W no registro de dados TWI */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Ative o TWI e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até o TWI concluir seu trabalho atual (operação de gravação) */
	status = TWSR & 0xF8;									/* Leia o registro de status TWI com mascaramento de três bits inferiores */	
	if (status == 0x18){									/* Verifique se o SLA + W foi transmitido e ack recebido ou não?  */
        return 1;											/* Se sim, retorne 1 para indicar a confirmação recebida, ou seja, pronto para aceitar o byte de dados */
	}
    if (status == 0x20){									/* Verifique o SLA + W foi transmitido e o nack recebido ou não? */
        return 2;											/* Se sim, retorne 2 para indicar o nack recebido, ou seja, o dispositivo está ocupado */
	}else
        return 3;											/* Caso contrário, retorne 3 para indicar falha no SLA + W */
}

/*INÍCIO REPETIDO(Sr)
    - Condição START REPETIDA emitida pelo mestre.
    - É gerado emitindo outra condição START para iniciar uma nova transmissão.
    - A condição START REPEATED com endereço de dispositivo escravo (SLA) é emitida entre a condição START e STOP
    Função Repeated_Start - gera a condição REPEATED START para operação de leitura.
    Argumento de entrada: - possui argumento de entrada do endereço de leitura do dispositivo escravo (SLA + R).
    Retorno: - retorna o status do evento.
 */
uint8_t TWI::Repeated_Start(char read_address){				/* TWI repeated start function */
	uint8_t status;											/* Declarar variável */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Ative o TWI, gere condição de início e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até que o TWI termine seu trabalho atual (condição inicial) */
	status = TWSR & 0xF8;									/* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status != 0x10){									/* Verifique a condição de início repetido foi transmitida com sucesso ou não? */
        return 0;											/* Se não, retorne 0 para indicar falha de condição de início repetida */
	}
    TWDR = read_address;									/* Se sim, escreva SLA + R no registro de dados TWI */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Ative o TWI e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até o TWI concluir seu trabalho atual (operação de gravação) */
	status = TWSR & 0xF8;									/* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status == 0x40){									/* Verifique se o SLA + R foi transmitido e ack aceito ou não? */
        return 1;											/* Se sim, retorne 1 para indicar a confirmação recebida */ 
	}
    if (status == 0x20){									/* Verificar SLA + R foi transmitido e nack recebido ou não? */
        return 2;											/* Se sim, retorne 2 para indicar o nack recebido, ou seja, o dispositivo está ocupado */
	}else
        return 3;											/* Outro retorno 3 para indicar falha no SLA + R */
}

/*PARAR(P)
    - Evento STOP emitido pelo mestre para indicar que ele deve parar.
    - É gerado pela transição Baixa para Alta no SDA enquanto o SCL é Alto.
    Função Stop - inicia a condição STOP
    Argumento de entrada: - não possui argumento de entrada.
    Retorno: - não retorna nenhum tipo de dado.
 */
void TWI::Stop(){											/* TWI stop function */
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Ative o TWI, gere a condição de parada e limpe o sinalizador de interrupção */
	while(TWCR & (1<<TWSTO));								/* Aguarde até a execução da condição de parada */
}

void TWI::Start_Wait(char write_address){					/* I2C start wait function */
	uint8_t status;											/* Declarar variável */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Ative o TWI, gere condição de início e limpe o sinalizador de interrupção */
		while (!(TWCR & (1<<TWINT)));						/* Aguarde até que o TWI termine seu trabalho atual (condição inicial) */
		status = TWSR & 0xF8;								/* Leia o registro de status TWI com mascaramento de três bits inferiores */
		if (status != 0x08){								/* Verifique se a condição de início foi transmitida com sucesso ou não? */
            continue;										/* Se não, continue com o loop inicial novamente */
		}
        TWDR = write_address;								/* Se sim, escreva SLA + W no registro de dados TWI */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Ative o TWI e limpe o sinalizador de interrupção */
		while (!(TWCR & (1<<TWINT)));						/* Aguarde até o TWI concluir seu trabalho atual (operação de gravação) */
		status = TWSR & 0xF8;								/* Leia o registro de status TWI com mascaramento de três bits inferiores */
		if (status != 0x18 ){								/* Verifique se o SLA + W foi transmitido e o ack recebido ou não? */
			TWI::Stop();									/* Caso contrário, gere a condição de parada */
			continue;										/* Continue com o loop inicial novamente */
		}
		break;												/* Se sim, interrompa o loop */
	}
}

/*ESCREVA(W)
    - O evento WRITE data / address é emitido pelo mestre após o reconhecimento bem-sucedido do START recebido do dispositivo escravo.
    Função Write - grava dados/endereço no barramento
    Argumento de entrada: - possui argumento de entrada de dados / endereço.
    Retorno: - retorna o status do evento.
 */
uint8_t TWI::Write(char data){								/* TWI write function */
	uint8_t status;											/* Declarar variável */
	TWDR = data;											/* Copiar dados no registro de dados TWI */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Ative o TWI e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até o TWI concluir seu trabalho atual (operação de gravação) */
	status = TWSR & 0xF8;									/* Leia o registro de status TWI com mascaramento de três bits inferiores */
	if (status == 0x28){									/* Verifique se os dados foram transmitidos e ack recebido ou não? */
        return 0;											/* Se sim, retorne 0 para indicar que a confirmação foi recebida */
	}
    if (status == 0x30){									/* Verificar se os dados foram transmitidos e nack recebido ou não? */
        return 1;											/* Se sim, retorne 1 para indicar nack recebido */
	}else
        return 2;											/* Outro retorno 2 para indicar falha na transmissão de dados */
}

/*LER(R)
    - O evento de leitura de dados é emitido pelo mestre após a condição REPEATED START bem-sucedida.
    Função Read_Ack - lê dados disponíveis na linha SDA e retorna ao dispositivo escravo a confirmação sobre a leitura bem-sucedida dos dados,
    e também informa ao escravo para transmitir outros dados.
    Argumento de entrada: - não possui argumento de entrada.
    Retorno: - retorna dados recebidos.
 */
char TWI::Read_Ack(){										/* TWI read ack function */
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Ativar TWI, gerar o ack e limpar o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até o TWI concluir seu trabalho atual (operação de leitura) */
	return TWDR;											/* Retornar dados recebidos */
}	

/*Função Read_Nack - lê o último byte de dados necessário disponível na linha SDA,mas não retorna o reconhecimento. 
    - Indica ao escravo que o mestre não deseja os próximos dados e deseja interromper a comunicação.
    Argumento de entrada: - não possui argumento de entrada.
    Retorno: - retorna os dados recebidos.
 */
char TWI::Read_Nack(){										/* TWI read nack function */
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Ative o TWI e limpe o sinalizador de interrupção */
	while (!(TWCR & (1<<TWINT)));							/* Aguarde até o TWI concluir seu trabalho atual (operação de leitura) */
	return TWDR;											/* Retornar dados recebidos */
}	

/*Função de inicialização I2C Slave
    - Atribuir um endereço de dispositivo de 7 bits no registro TWAR. 
    - Após atribuir o endereço, precisamos ativar o TWI e o bit de reconhecimento no TWCR.
    - E limpe o sinalizador de interrupção do TWI escrevendo a lógica 1 nele.
    Argumento de entrada: - possui argumento de entrada do endereço escravo.
    Retorno: - não retorna nenhum tipo de dado.
 */
void TWI::Slave_Init(uint8_t slave_address){
	TWAR = slave_address;                                   /* Atribuir endereço no registro de endereço TWI */
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);              /* Ativar TWI, Ativar geração de ack, limpar a interrupção TWI */
}

/*Ouvir o Barramento
    - O dispositivo escravo sempre precisa ouvir o barramento TWI para verificar se ele é endereçado por qualquer mestre.
    - Quando endereçado, o bit TWINT é configurado. Então, precisa monitorar bit TWINT.
    Função Slave_Listen
    Argumento de entrada: - não possui nenhum argumento de entrada.
    Retorno: - retorna o status do evento.
 */
uint8_t TWI::Slave_Listen(){
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
uint8_t TWI::Slave_Transmit(char data){
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
char TWI::Slave_Receive(){
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
		return -1;
	}else
        return -2;                                          /* Outro retorno 1 */
}
