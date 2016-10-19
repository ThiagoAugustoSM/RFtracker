#include <VirtualWire.h>

//Enviar
String mensagem_enviar;
char data[40] = {'7', 'E', '0', '0', '0', '0', '0', '1'};
int numero;

//Receber
byte message[VW_MAX_MESSAGE_LEN];    // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN; // Armazena o tamanho das mensagens

void enviar();
boolean receber();

boolean range;

#define LED 13
#define TEMPO 1000

int cont = 1;
int good = 0;
int bad = 0;

int contador = 0;

int tempo = millis();
int tempo_passado = 0;

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
  tempo = millis();
  enviar();
  tempo_passado = millis();
  Serial.println(tempo_passado - tempo);
  /*
  tempo = millis();
  while(tempo_passado <  tempo + TEMPO){
    range = receber();
    tempo_passado = millis();
    if(range == true){
      digitalWrite(13,HIGH);
      break;
    }
   }
   if(range == false){
    digitalWrite(13,LOW);
  }
      */
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Aguarda o envio de dados
}

void enviar(){
  
  //data[40];
  //numero;
    Serial.print("Enviado : ");
    Serial.print(data);
    Serial.print(" - Caracteres : ");
    Serial.println(strlen(data));
    //Envia a mensagem para a rotina que
    //transmite os dados via RF
    send(data);
  
}

boolean receber(){
  
   uint8_t message[VW_MAX_MESSAGE_LEN];    
   uint8_t msgLength = VW_MAX_MESSAGE_LEN;
   bad =  vw_get_rx_bad();
   good = vw_get_rx_good();
   //Serial.println(bad);  
   //Serial.println(good);
    if (vw_get_message(message, &msgLength)) // Non-blocking
    {   
      digitalWrite(LED,1); 
      Serial.print("Recebido: ");
      for (int i = 0; i < msgLength; i++){
        if(message[i] == data[i]){
        }else{
          Serial.println("Não recebeu");
          return false;
        }
        Serial.write(message[i]);
      }
      Serial.println();
      return true;
    }else{
      Serial.println("NAO RECEBIDO");
      return false;
    }
}



