/*
  echo 
  reenvia para o computador o dado recebido pela serial
*/
 
byte byteRead;
 
void setup() {                
//configura a comunicação seria com baud rate de 9600
//Serial.begin(9600,config); config é usado para configurar paridade e stop bit
  Serial.begin(9600);
}
 
void loop() {
   
  if (Serial.available())  //verifica se tem dados diponível para leitura
  {
    byteRead = Serial.read(); //lê byte mais recente no buffer da serial
    byteRead++;
    Serial.write(byteRead);   //reenvia para o computador o dado recebido
  }
}
