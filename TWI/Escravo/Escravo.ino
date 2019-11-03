#include <Wire.h>

char strc[10];

void setup ( ) {
  Wire.begin ( 8 ) ;                // ingressa no barramento i2c com o endereço nº 8
  Wire.onRequest (requestEvent) ; // registre o evento
  Serial.begin ( 9600 ) ;  // inicia serial para saída
}

void loop ( ) {
    // apenas responde quando dados são recebidos:
  if (Serial.available() > 0) {
    // Lê toda string recebida
    String recebido = getString();
    recebido.toCharArray(strc,10);
    Wire.write (strc) ; // responde com a mensagem
  }
}
// função que é executada sempre que os dados são solicitados pelo mestre
// essa função é registrada como um evento, consulte setup ()
void requestEvent ( ) {
  Wire.write (strc) ; // responde com mensagem esperado pelo mestre
  //Wire.endTransmission();    // stop transmitting
}

String getString(){
  String conteudo = "";
  char caractere;
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  Serial.print("Escrito: ");
  Serial.println(conteudo);
  return conteudo;
}
