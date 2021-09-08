/*Nayadeth Aguirre - 2021
 *Contiene las definiciones asociadas a la configuración de la red y los dispositivos.
*/

/*Inclusión de bibliotecas
SPI -> comunicación con la red 
LoRa-> protocolo
*/

#include <SPI.h>              
#include <LoRa.h>
#include <Wire.h>


/*Definición de buffers y variables asociadas a las estructuras*/
#define BAND    868E6
#define CASE1 0x21
#define CASE2 0x22
#define CASE3 0x23
uint8_t ids[] = {0x01};
uint8_t idnodo[] = {0x22};
uint8_t buferACK[100]={};
uint8_t bufer[100] = {};
uint8_t bufHumedad[12];
uint8_t bufTemperature[12];
uint8_t bufVoltaje[12];
uint8_t bufACK[12];
int packetSize;
boolean recibido=false;


/*Definicion de estructuras*/
union paqueteHumedad{
struct humedad
   {  
    uint8_t id;//1 id de la red 
    uint8_t idnodo;//1 id de nodo
    uint8_t idrepeat;//1 id repetidor
    uint8_t type;//1 tipo de dato
    uint8_t length_;//1 tamaño del paquete
    uint8_t nc2;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc3;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc4;//1 byte no utilizado actualmente, futura implementación
    float val1;//4 valor del sensor asociado a la estructura
   }hum;//12
uint8_t paquete_humedad[sizeof(hum)];
};paqueteHumedad paquete_humedad;

union paqueteVoltaje{  
struct voltaje
 {  
    uint8_t id;//1 id de la red 
    uint8_t idnodo;//1 id de nodo
    uint8_t idrepeat;//1 id repetidor
    uint8_t type;//1 tipo de dato
    uint8_t length_;//1 tamaño del paquete
    uint8_t nc2;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc3;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc4;//1 byte no utilizado actualmente, futura implementación
    float val1;//4 valor del sensor asociado a la estructura
   }volt;//12
 
uint8_t paquete_voltaje[sizeof(volt)];
};paqueteVoltaje paquete_voltaje;

union paqueteTemperature{  
struct temperature
   {  
    uint8_t id;//1 id de la red 
    uint8_t idnodo;//1 id de nodo
    uint8_t idrepeat;//1 id repetidor
    uint8_t type;//1 tipo de dato
    uint8_t length_;//1 tamaño del paquete
    uint8_t nc2;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc3;//1 byte no utilizado actualmente, futura implementación
    uint8_t nc4;//1 byte no utilizado actualmente, futura implementación
    float val1;//4 valor del sensor asociado a la estructura
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
