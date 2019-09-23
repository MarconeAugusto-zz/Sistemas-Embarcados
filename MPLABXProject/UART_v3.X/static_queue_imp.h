/*
 * queue-imp.h
 *
 *  Created on: 23 de set de 2019
 *      Author: guilherme
 */

#ifndef STATIC_QUEUE_IMP_H_
#define STATIC_QUEUE_IMP_H_

#include "static_queue.h"
template <typename T> static_queue<T>::static_queue(unsigned int size){
    cap = size;
    N=0;
    inicio=0;
    fim=0;
    buffer = new T[cap];
}

template <typename T> static_queue<T>::~static_queue(){
    delete[] buffer;
}

template <typename T> void static_queue<T>::push(const T & algo){
    if(N == cap){
        throw -1;
    }

    else if(N < cap){
        buffer[fim] = algo;
        N++;
        fim++;
    }

    if(N == cap){
        fim=0;
    }
}

template <typename T> T static_queue<T>::pop(){
    int pos = inicio;
    inicio = (inicio+1)%cap;
    N--;
    return buffer[pos];
}


template <typename T> bool static_queue<T>::empty() const{
    return N==0;
}

template <typename T> bool static_queue<T>::full() const{
    return N==cap;
}

template <typename T> unsigned int static_queue<T>::length() const{
    return N;
}

template <typename T> unsigned int static_queue<T>::size() const{
    return cap;
}
#endif /* STATIC_QUEUE_IMP_H_ */
