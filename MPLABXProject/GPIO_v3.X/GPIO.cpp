
#include "GPIO.h"
#include <avr/io.h>

GPIO::GPIO(uint8_t id, PortDirection_t dir):
_id(id)
{
	switch (_id) {
	case 0:
	case 1:
		_Px = GPIO_PORT::PE;
		_bit = id;
		if (dir)
			DDRE |= (1 << _bit);
		else
			DDRE &= ~(1 << _bit);
		break;

	case 2:
	case 3:
		_Px = GPIO_PORT::PE;
		_bit = id;
		_bit = id + 2;
		if (dir)
			DDRE |= (1 << _bit);
		else
			DDRE &= ~(1 << _bit);
		break;

	case 4:
		_Px = GPIO_PORT::PG;
		_bit = id;
		//_bit = DDG5;
		if (dir)
			DDRG |= (1 << _bit);
		else
			DDRG &= ~(1 << _bit);
		break;

	case 5:
		_Px = GPIO_PORT::PE;
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
		_Px = GPIO_PORT::PH;
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
		_Px = GPIO_PORT::PB;
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
	return _Px->get(_bit);
}

void GPIO::set(bool val) {
	_Px->set(_bit, val);
}

void GPIO::clear() {
	this->set(0);
}

void GPIO::toggle() {
	_Px->toggle(_bit);
}