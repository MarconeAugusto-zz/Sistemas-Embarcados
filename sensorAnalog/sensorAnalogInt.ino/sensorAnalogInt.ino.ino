// Código para medir a temperatura com um termonstato NTC
#include <math.h>

int sensorPin = A0 ;    // selecione o pino de entrada para o potenciômetro
int ledPin = 22 ;      // selecione o pino para o LED
int sensorValue = 0 ;  // variável para armazenar o valor vindo do sensor
int temperatura = 0, A = 0, B = 0, C = 0, Vs = 0, Vo = 0, Rs = 0;

void setup ( ) {
  // declara o ledPin como um OUTPUT:
  pinMode(ledPin , OUTPUT);
  Serial.begin(9600); 
  A = 1.1122e-03;
  B = 2.3758e-04;
  C = 0.6852e-07;
}

void loop(){
   // liga o ledPin em
  digitalWrite(ledPin , LOW);
  // lê o valor do sensor:
  sensorValue = analogRead(sensorPin);
  // converte para a tensão real
  Vs = sensorValue*5/1023;
  // calcula o valor da resistencia
  Rs = ((50000/Vs)-10000);
  // calcula o valor da temperatura
  temperatura = 1/(A + (B*log(Rs))+ C*pow(log(Rs),3))-273.15; 
  // desliga o ledPin:
  digitalWrite(ledPin , HIGH);
  // imprime via serial o valor da temperatura
  Serial.print("Temperatura ");
  Serial.println(temperatura);
  // parar o programa por um segundo
  delay(1000);
}
