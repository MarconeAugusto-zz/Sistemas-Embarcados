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
float ledPin = 22 ;      // selecione o pino para o LED
float sensorValue = 0 ;  // variável para armazenar o valor vindo do sensor
float temperatura, A, B, C, Vs, Vo, Rs, ln, ln3;

void setup ( ) {
  // declara o ledPin como um OUTPUT:
  pinMode ( ledPin , OUTPUT );
  Serial.begin(9600); 
  A = 1.1122e-03;
  B = 2.3758e-04;
  C = 0.6852e-07;
}

void loop ( ) {
   // liga o ledPin em
  digitalWrite ( ledPin , LOW ) ;
  // lê o valor do sensor:
  sensorValue = analogRead (sensorPin);
  // converte para a tensão real
  Vs = sensorValue*5/1023;
  // calcula o valor da resistencia
  Rs = ((50000/Vs)-10000);
  // calcula o valor do ln
  ln = log(Rs);
  // calcula o valor da temperatura
  temperatura = 1/(A + (B*ln)+ C*pow(ln,3))-273.15; 
  // desliga o ledPin:
  digitalWrite ( ledPin , HIGH ) ;
  // imprime via serial o valor da temperatura
  Serial.print("Temperatura ");
  Serial.println(temperatura);
  // parar o programa por um segundo
  delay(5000);
}
