#include <VirtualWire.h>

//Enviar
String mensagem_enviar;
char data[40] = {'7', 'E', '0', '0', '0', '0', '0', '0'};
int numero;

//Receber
byte message[VW_MAX_MESSAGE_LEN];    // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN; // Armazena o tamanho das mensagens

void enviar();
struct retorno receber();

boolean range = false;

#define LED 13
#define TEMPO 3000

int cont = 1;
int good = 0;
int bad = 0;

int contador = 0;

int tempo = millis();
int tempo_passado = 0;

struct retorno{
  boolean range;
  int pacote_conhecido;
};

void setup(){

  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  //Define o pino 8 do Arduino como 
  //o pino de dados do transmissor
  vw_set_tx_pin(8);
  vw_setup(2000);   // Bits per sec

  /////Enviar
  vw_set_rx_pin(5); // Define o pino 5 do Arduino como entrada 
  //de dados do receptor
  vw_setup(2000);             // Bits por segundo
  vw_rx_start();              // Inicializa o receptor  
  
}

void loop(){

  struct retorno valores;
  valores.range = false;
  tempo = millis();
  while(valores.range == false){
    valores = receber();
    tempo_passado = millis();
    if(tempo_passado >  tempo + TEMPO){
      digitalWrite(13,0);
    }
  }
  digitalWrite(13,1);
  Serial.println(tempo_passado - tempo);      
}

struct retorno receber(){
   struct retorno teste;
   
   uint8_t message[VW_MAX_MESSAGE_LEN];    
   uint8_t msgLength = VW_MAX_MESSAGE_LEN;
   bad =  vw_get_rx_bad();
   good = vw_get_rx_good();
   //Serial.println(bad);  
   //Serial.println(good);
    if (vw_get_message(message, &msgLength)) // Non-blocking
    {   
      //digitalWrite(LED,1); 
      Serial.print("Recebido: ");
      for (int i = 0; i < msgLength; i++){
        if(message[i] == data[i]){
        }else{
          Serial.println("NAO RECEBIDO");
          teste.range = false;
          return teste;
        }
        Serial.write(message[i]);
      }
      Serial.println();
      teste.range = true;
      return teste;
    }else{
      //Serial.println("NAO RECEBIDO");
      //digitalWrite(LED,0);
      teste.range = true;
      return teste;
    }
}
