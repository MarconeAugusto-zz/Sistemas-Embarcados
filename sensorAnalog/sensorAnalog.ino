// Código para medir a temperatura com um termonstato NTC
#include <math.h>
#include <stdio.h>
#include <string.h>

float sensorPin = A0 ;    // selecione o pino de entrada para o potenciômetro
float ledPin = 22 ;      // selecione o pino para o LED
float sensorValue = 0 ;  // variável para armazenar o valor vindo do sensor
float temperatura = 0, Vs = 0, Vo = 0, Rs = 0, tempo_1;
float A = 1.1122e-03, B = 2.3758e-04, C = 0.6852e-07;
String inString = "";

float calculaTemp(float resistencia){ // Equação de Steinhart-Hart
  temperatura = 1/(A + (B*log(Rs))+ C*pow(log(Rs),3))-273.15; 
  return temperatura;  
}

float calculaTempSimplificada(float resistencia){ // Equação de Steinhart-Hart
  temperatura = 1.0/(1.0/298.15 + (1.0/3950.0)*log(resistencia/10000.0))-273.15; 
  return temperatura;  
}

long calculaTempLong(float resistencia){ // Equação de Steinhart-Hart
  long temperaturaLong = 0;
  temperaturaLong = (long)29800*(long)3950/((long)3950 + (long)(298.15*log(resistencia/10000.0)));
  return temperaturaLong;  
}

void setup(){
  // declara o ledPin como um OUTPUT:
  pinMode(ledPin , OUTPUT);
  Serial.begin(9600); 
}

void loop(){
   // liga o ledPin em
  tempo_1 = 0;
  digitalWrite(ledPin , LOW);
  
  sensorValue = analogRead(sensorPin);
  
  // converte para a tensão real
  Vs = sensorValue*5/1023;
  // calcula o valor da resistencia
  Rs = ((50000/Vs)-10000);

  // Temperatura Steinhart-Hart Simplificada
  tempo_1 = micros();
  // calcula o valor da temperatura
  temperatura = calculaTemp(Rs);
  float tempo_2 = micros();
  // imprime via serial o valor da temperatura
  Serial.print("Temperatura B = ");
  Serial.println(temperatura);
  Serial.print("Tempo B = ");
  Serial.print((tempo_2 - tempo_1)/1000);
  Serial.println(" ms");

  // Temperatura Steinhart-Hart
  tempo_1 = 0;
  tempo_1 = micros();
  temperatura = calculaTempSimplificada(Rs);
  float tempo_3 = micros();
  // imprime via serial o valor da temperatura
  Serial.print("Temperatura Steinhart-Hart = ");
  Serial.println(temperatura);
  Serial.print("Tempo Steinhart-Hart = ");
  Serial.print((tempo_3 - tempo_1)/1000);
  Serial.println(" ms");

  // Temperatura Steinhart-Hart Simplificada long int
  tempo_1 = 0;
  tempo_1 = micros();
  long temperaturaLong = 0;
  temperaturaLong = calculaTempLong(Rs); 
  float tempo_4 = micros();
  // imprime via serial o valor da temperatura
  char temperaturaLong_str [10];
  int inteiro = ((temperaturaLong/100) -273);
  int decimal = (temperaturaLong%100);
  sprintf(temperaturaLong_str,"%d.%d",inteiro,decimal);      
  Serial.print("Temperatura com Long = ");
  Serial.println(temperaturaLong_str);
  Serial.print("Tempo Long = ");
  Serial.print((tempo_4 - tempo_1)/1000);
  Serial.println(" ms");
  
  // desliga o ledPin:
  digitalWrite(ledPin , HIGH);
  // parar o programa por um segundo
  delay(1000);

}
