/*Nayadeth Aguirre - 2021
 * Programa Emisor de red LoRa
 * Implementación de red LoRa en varios dispositivos con la finalidad de conectarse a un servidor Thingsboard
 * Esquema de configuración:
 * definition.h: Contiene las definiciones asociadas a la configuración de la red y los dispositivos
 * libreria_.h: Contiene las funciones asociadas a la estructura principal de la programación del sistema.
*/

/*Inclusión de bibliotecas*/
#include "libreria_.h"

#define SERIAL_BAUD_RATE 9600 //Definición de la velocidad Serial

void setup() {
Serial.begin(SERIAL_BAUD_RATE); //Inicio de la comunicación Serial
  if (!LoRa.begin(BAND)) { //Comprobacion de radio LoRa
    while (1);
  }
  initBasis(); //Inicilización de las estructuras para transmisión de datos
 Serial.println("Enviando a repetidor");
}

void loop() {
    sendHumedad(); //Función de envio de datos
    sendTemperature(); //Función de envio de datos
    sendVoltaje(); //Función de envio de datos
  }
