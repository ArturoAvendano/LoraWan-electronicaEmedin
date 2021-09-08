/*
Arturo Avendaño - 2021
Biblioteca de configuración de la comunicación LoRa integrada en el dispositivo.
Maneja el envio y recepción de paquetes LoRa sobre la red.
*/

#include <SPI.h>              
#include <LoRa.h>

/*Declaración de pines LoRa*/
const int csPin = 26;          // LoRa radio chip select
const int resetPin = 0;       // LoRa radio reset
const int irqPin = 19;         // change for your board; must be a hardware interrupt pin


#define BAND    868E6  

/*Implementación de Headers LoRa para la descripción de la red*/
uint8_t ids[] = {0x01};
uint8_t idnodo[] = {0x22};
uint8_t bufer[100] = {};
uint8_t idrepeat[]={0x22};
uint8_t bufHumedad[12];
uint8_t bufACK[12];
uint8_t bufTemperature[12];
uint8_t bufVoltaje[12];
int packetSize;

#define CASE1 0x21 //Identificador Humedad
#define CASE2 0x22 //Identificador Temperatura
#define CASE3 0x23 //Identificador Voltaje


/*Decleración de estructuras*/

union paqueteHumedad{
struct humedad
   {  
    uint8_t id; //1 id de la red 
    uint8_t idnodo;//1 id nodo
    uint8_t idrepeat;//id repetidor
    uint8_t type;//1 tipo de dato
    uint8_t length_;//1 tipo de dato
    uint8_t nc2;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc3;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc4;//1 byte constructor, aun no es utilizado futura implementación
    float val1; //Valor del dispositivo.
   }hum;//12
uint8_t paquete_humedad[sizeof(hum)];
};paqueteHumedad paquete_humedad;

union paqueteVoltaje{  
struct voltaje
   {  
   
    uint8_t id;//1 id de la red 
    uint8_t idnodo;//1
    uint8_t idrepeat;//1 id repetidor
    uint8_t type;//1 
    uint8_t length_;//1 tipo de dato
    uint8_t nc2;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc3;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc4;//1 byte constructor, aun no es utilizado futura implementación
    float val1;//Valor del dispositivo
   }volt;//12
 
uint8_t paquete_voltaje[sizeof(volt)];
};paqueteVoltaje paquete_voltaje;

union paqueteTemperature{  
struct temperature
   {  
    uint8_t id;//1
    uint8_t idnodo;//1
    uint8_t idrepeat;//id repetidor
    uint8_t type;//1
    uint8_t length_;//1 tipo de dato
    uint8_t nc2;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc3;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc4;//1 byte constructor, aun no es utilizado futura implementación
    float val1;//Valor del dispositivo
   }temp;//12
   
uint8_t paquete_temperature[sizeof(temp)];
};paqueteTemperature paquete_temperature;

union paqueteACK{
struct ack
   {  
    uint8_t id; //1 id de la red 
    uint8_t idnodo;//1 id nodo
    uint8_t idrepeat;//id repetidor
    uint8_t type;//1 tipo de dato
    uint8_t length_;//1 tipo de dato
    uint8_t messageType_;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc3;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc4;//1 byte constructor, aun no es utilizado futura implementación
    float val1;//Valor del ACK (0 PARA RECEPCIÓN CORRECTA, 1 PARA ERROR DE LECTURA)
   }ack;//12
uint8_t paquete_ack[sizeof(ack)];
};paqueteACK paquete_ack;

/*FUNCIÓN DE INICILIZACIÓN LORA*/
void LoRaInit(){ 
    LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin
    if (!LoRa.begin(BAND)) {
      Serial.println("LoRa failed!");
      while (1);
    }
    Serial.println("LoRa Succeed!");
  }

/*FUNCIÓN DE RECEPCIÓN PAQUETE HUMEDAD*/
void leerPaqueteHumedad(){
  for (int i = 0; i <12; i++) {paquete_humedad.paquete_humedad[i] = bufer[i];}   
  Serial.println("RECIBIDO HUMEDAD");
  Serial.println(paquete_humedad.hum.val1);
  }

/*FUNCIÓN DE RECEPCIÓN PAQUETE TEMPERATURA*/
void leerPaqueteTemperatura(){
  for (int i = 0; i <12; i++) {paquete_temperature.paquete_temperature[i] = bufer[i];}
                      Serial.println("RECIBIDO TEMPERATURA");
                      Serial.println(paquete_temperature.temp.val1);  
  }

/*FUNCIÓN DE RECEPCIÓN PAQUETE VOLTAJE*/
void leerPaqueteVoltaje(){
    for (int i = 0; i <12; i++) {paquete_voltaje.paquete_voltaje[i] = bufer[i];}
                      Serial.println("RECIBIDO VOLTAJE");   
                      Serial.println(paquete_voltaje.volt.val1);
  }
  
/*FUNCIÓN DE ENVIO DE PAQUETE ACK PARA ASEGURAR LA RECEPCION DEL DISPOSITIVO*/   
 void sendACK(uint8_t receptor,uint8_t tipo,float valor){
  Serial.println("Envio de ack");
  paquete_ack.ack.id=0x01;
  paquete_ack.ack.idnodo=receptor;
  paquete_ack.ack.type=0x24;
  paquete_ack.ack.idrepeat=0x00;
  paquete_ack.ack.length_=0x0C;
  paquete_ack.ack.messageType_=tipo;
  paquete_ack.ack.nc3=0x00;
  paquete_ack.ack.nc4=0x00;
  paquete_ack.ack.val1=valor;
  for(int i=0; i<12; i++){bufACK[i]=paquete_ack.paquete_ack[i];}
  LoRa.beginPacket();
  LoRa.write(bufACK,sizeof(bufACK));
  Serial.println(paquete_ack.ack.val1);
  LoRa.endPacket();
  Serial.println("Fin de envio de ack");
  }
   
