/*Nayadeth Aguirre - 2021
 * Programa Repetidor de red LoRa
 * Implementación de red LoRa en varios dispositivos con la finalidad de conectarse a un servidor Thingsboard
 * Esquema de configuración:
 * definition.h: Contiene las definiciones asociadas a la configuración de la red y los dispositivos
 * libreria_.h: Contiene las funciones asociadas a la estructura principal de la programación del sistema.
*/

/*Inclusión de bibliotecas*/
#include "library_.h"

#define SERIAL_BAUD_RATE 9600 //Definición de la velocidad Serial

void setup() {
  Serial.begin(SERIAL_BAUD_RATE); //Inicio de la comunicación Serial
 
 if (!LoRa.begin(BAND)) {
    Serial.println("LoRa failed!"); //Comprobacion de radio LoRa
    while (1);
    }
    Serial.println("Enviando a gateway");
}

void loop() {
  packetSize = LoRa.parsePacket();
  if (packetSize) {
      for (i = 0; i < packetSize; i++) {bufer[i] = LoRa.read();} //Lectura del buffer del dispositivo LoRa 

      if (bufer[0] == ids[0] && bufer[1] == idnodo[0]){
          switch (bufer[3]){
                 case CASE1:
                  Paquete_Humedad(); //Función de envio de datos
                 case CASE2:
                  Paquete_Temperatura(); //Función de envio de datos
                 break;                                                            
                 case CASE3:
                  Paquete_Voltaje(); //Función de envio de datos
                 break;
          }
          }
          }
          }

 
  
 
