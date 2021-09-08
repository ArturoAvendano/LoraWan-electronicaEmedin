/*Nayadeth Aguirre - 2021
 *Contiene las definiciones asociadas a la configuración de la red y los dispositivos.
*/

/*Inclusión de bibliotecas
SPI -> comunicación con la red 
LoRa-> protocolo
*/
#include <SPI.h>
#include <LoRa.h>

/*Definición de buffers y variables asociadas a las estructuras*/
#define BAND    868E6 
uint8_t ids[] = {0x01};
uint8_t idnodo[] = {0x22};
uint8_t buferACK[100]={};
uint8_t bufer[100] = {};
uint8_t bufHumedad[12];
uint8_t bufTemperature[12];
uint8_t bufVoltaje[12];
uint8_t bufACK[12];
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
    uint8_t nc2;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc3;//1 byte constructor, aun no es utilizado futura implementación
    uint8_t nc4;//1 byte constructor, aun no es utilizado futura implementación
    float val1;//Valor del ACK (0 PARA RECEPCIÓN CORRECTA, 1 PARA ERROR DE LECTURA)
   }ack;//12
uint8_t paquete_ack[sizeof(ack)];
};paqueteACK paquete_ack;


/* Declaración de espacios de memoria */

void initBasis(){
  
  paquete_humedad.hum.id=0x01;
  paquete_humedad.hum.idnodo=0x22;
  paquete_humedad.hum.type=0x21;
  paquete_humedad.hum.idrepeat=0x00;
  paquete_humedad.hum.length_=0x0C; 
  paquete_humedad.hum.nc2=0x00;
  paquete_humedad.hum.nc3=0x00;
  paquete_humedad.hum.nc4=0x00;
  
  paquete_temperature.temp.id=0x01;
  paquete_temperature.temp.idnodo=0x22;
  paquete_temperature.temp.type=0x22;
  paquete_temperature.temp.idrepeat=0x00;
  paquete_temperature.temp.length_=0x0C; 
  paquete_temperature.temp.nc2=0x00;
  paquete_temperature.temp.nc3=0x00;
  paquete_temperature.temp.nc4=0x00;

  paquete_voltaje.volt.id=0x01;
  paquete_voltaje.volt.idnodo=0x22;
  paquete_voltaje.volt.type=0x23;
  paquete_voltaje.volt.idrepeat=0x00;
  paquete_voltaje.volt.length_=0x0C; 
  paquete_voltaje.volt.nc2=0x00;
  paquete_voltaje.volt.nc3=0x00;
  paquete_voltaje.volt.nc4=0x00;
  }
  
