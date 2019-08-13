/*
  Entrada

  analógica Demonstra entrada analógica lendo um sensor analógico no pino analógico 0 e
  ligando e desligando um diodo emissor de luz (LED) conectado ao pino digital 13.
  O tempo que o LED ficará ligado e desligado dependerá do valor obtido
  por analogRead ().

  O circuito:
  -
    pino central potenciômetro do potenciômetro para a entrada analógica 0
    um pino lateral (qualquer um) para aterrar
    o outro pino lateral para + 5V
  -
    ânodo LED (perna longa) ligado à saída digital 13
    cátodo (perna curta) ligado a ground

  - Nota: como a maioria dos Arduinos tem um LED embutido no pino 13 da
    placa, o LED é opcional.

  criado por David Cuartielles
  modificado em 30 de agosto de 2011
  Por Tom Igoe

  Este código de exemplo é de domínio público.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/
#include <math.h>

float sensorPin = A0 ;    // selecione o pino de entrada para o potenciômetro
float ledPin = 13 ;      // selecione o pino para o LED
float sensorValue = 0 ;  // variável para armazenar o valor vindo do sensor
float temperatura, A, B, C, Vsensor, Vout, Rsensor;

void setup ( ) {
  // declara o ledPin como um OUTPUT:
  pinMode ( ledPin , OUTPUT );
  Serial.begin(9600); 
  A = 1.112272e-03;
  B = 2.375809e-04;
  C = 0.685285e-07;
  
}

void loop ( ) {
  // lê o valor do sensor:
  sensorValue = analogRead (sensorPin);
  Vsensor = sensorValue*5/1023;
  Vout = 5 - Vs;
  Rsensor = ((50000/Vout)-10000);
  Serial.print("Resistência ");
  Serial.println(Rs);
  
  temperatura = 1/(A + B*log(Rs)+ C*pow((log(Rs)),3)); 
  // liga o ledPin em
  Serial.print("Sensor ");
  Serial.println(sensorValue);
  Serial.print("Temperatura ");
  Serial.println(temperatura);
  delay(1000);
  //digitalWrite ( ledPin , HIGH ) ;
  // pare o programa por <sensorValue> milissegundos:
  //delay ( sensorValue ) ;
  // desliga o ledPin:
  //digitalWrite ( ledPin , LOW ) ;
  // pare o programa por <sensorValue> milissegundos:
  //delay( sensorValue ) ;
}

