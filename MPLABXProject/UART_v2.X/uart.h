/* 
 * File:   uart.h
 * Author: marcone
 *
 * Created on 18 de Setembro de 2019, 08:11
 */

#ifndef UART_H
#define	UART_H

class uart {
   public:
   
    enum DATABITS_t{
		DATABITS_5 = 0,
		DATABITS_6 = 2,
		DATABITS_7 = 4,
		DATABITS_8 = 6
	};

	enum PARITY_t{
		NONE = 0,
		EVEN = 32,
		ODD = 48
	};

	enum STOPBITS_t{
		STOPBIT_1 = 0,
		STOPBIT_2 = 8
	};

	uart(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb);
	~uart();

	void put(uint8_t data);
	uint8_t get();
	bool has_data();
	static void rxc_isr_handler();
	static void udre_isr_handler();
    
private:
    static bool _has_data;
	static uint8_t _rx_buffer;
	static uint8_t _tx_buffer;

};

#endif	/* UART_H */

