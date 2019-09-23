/*
 * queue.h
 *
 *  Created on: 23 de set de 2019
 *      Author: guilherme
 */

#ifndef STATIC_QUEUE_H_
#define STATIC_QUEUE_H_

template <typename T> class static_queue {
public:
	static_queue(unsigned int size);
	~static_queue();
    void push(const T & algo);
    T pop();
    bool empty() const;
    bool full() const;
    unsigned int size() const;
    unsigned int length() const;

private:
    unsigned int inicio, fim;
    unsigned int N,cap;
    T * buffer;

};
#include "static_queue_imp.h"
#endif /* STATIC_QUEUE_H_ */
