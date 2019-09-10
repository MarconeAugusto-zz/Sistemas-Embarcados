
#include "GPIO.h"
#include <avr/io.h>

GPIO::GPIO(uint8_t id, PortDirection_t dir):
_id(id)
{
	switch (_id) {
	case 0:
	case 1:
        _port = &PORTE;
        _pin = &PINE;
        _ddr = &DDRE;
		_bit = id;
		if (dir)
			DDRE |= (1 << _bit);
		else
			DDRE &= ~(1 << _bit);
		break;

	case 2:
	case 3:
        _port = &PORTE;
        _pin = &PINE;
        _ddr = &DDRE;
		_bit = id;
		_bit = id + 2;
		if (dir)
			DDRE |= (1 << _bit);
		else
			DDRE &= ~(1 << _bit);
		break;

	case 4:
        _port = &PORTG;
        _pin = &PING;
        _ddr = &DDRG;
		_bit = id;
		//_bit = DDG5;
		if (dir)
			DDRG |= (1 << _bit);
		else
			DDRG &= ~(1 << _bit);
		break;

	case 5:
        _port = &PORTE;
        _pin = &PINE;
        _ddr = &DDRE;
        _bit = id;
		//_bit = DDE3;
		if (dir)
			DDRE |= (1 << _bit);
		else
			DDRE &= ~(1 << _bit);
		break;

	case 6:
	case 7:
	case 8:
	case 9:
        _port = &PORTH;
        _pin = &PINH;
        _ddr = &DDRH;
		_bit = id - 3;
		if (dir)
			DDRH |= (1 << _bit);
		else
			DDRH &= ~(1 << _bit);
		break;

	case 10:
	case 11:
	case 12:
	case 13:
        _port = &PORTB;
        _pin = &PINB;
        _ddr = &DDRB;
		_bit = id - 6;
		if (dir)
			DDRB |= (1 << _bit);
		else
			DDRB &= ~(1 << _bit);
		break;

	}

}

GPIO::~GPIO() {}

bool GPIO::get() {
	return (bool) _pin & (1 << _bit);
}

void GPIO::set(bool val) {
	if (val)
		*_port |= _bit;
	else
		*_port &= ~_bit;
}

void GPIO::clear() {
	this->set(0);
}

void GPIO::toggle() {
	*_pin = _bit;
}