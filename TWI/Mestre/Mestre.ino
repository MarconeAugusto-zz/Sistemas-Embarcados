#include <Wire.h>

void setup ( ) { 
  Wire.begin ( ) ;        // ingressa no barramento i2c (endereço opcional para o mestre)
  Serial.begin ( 9600 ) ;  // inicia serial para saída
}

void loop ( ) {
  Wire.requestFrom ( 8 , 10 ) ;    // solicita 10 bytes do dispositivo escravo # 8
  char c;
  String msg;
  while (Wire.available ( )) { // slave pode enviar menos do que o requisitado
    c = Wire.read ( ) ; // recebe um byte como caractere
  
    if(isAscii(c)){
      msg.concat(c);
    }
  }
  Serial.print(msg) ;         // imprime o caractere
  Serial.println();
  delay ( 2000 ) ;
}
