/*
Arturo Avendaño - 2021
Integracion de ThingsBoard en plataforma ESP32 con comunicación LoRa integrada en un módulo GataWay

Composición:

LoraConf-h encargada de la capa de comunicación LoRa
SdConf.h Se encarga de la conexión y comunicación a través del protocolo SPI para la utilización de la microSd.
wifiConf.h Comunicación WiFi integrada en el modulo ESP32, maneja la conexión y transmisión de datos a través de la capa TCP a través de HTTP.
*/

/*Importación de bibliotecas*/
#include "wifiConf.h" 
#include "SdConf.h"
#include "LoRaConf.h"


#define SERIAL_DEBUG_BAUD    115200 //Velocidad de conexión serial.
 

void setup() {
    Serial.begin(SERIAL_DEBUG_BAUD); //Iniciación de dispositivos integrados en el módulo.
    InitWiFi();
    LoRaInit();
    InitSD();
    comprobarTarjeta();
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) { // Reconexión WiFi de la biblioteca.
    reconnect(); 
    return;
  }
     packetSize = LoRa.parsePacket(); //Verificación del tamaño del paquete LoRa
  if (packetSize) {
      for (int i = 0; i < packetSize; i++) {
        bufer[i] = LoRa.read(); 
        Serial.print(bufer[i],HEX);
            Serial.print("-");}
            Serial.println("");
      

      if (bufer[0] == ids[0] && bufer[1] == idnodo[0] && bufer[2] == idrepeat[0]){ //Verificación de Header LoRa para saber si pertenece el paquete a la red

          switch (bufer[3]){ //Verifación del tipo de dato que se esta enviando.
                 case CASE1:{
                        if(packetSize!=int(bufer[4])){ //Checksum del tamaño del paquete, si no corresponde se descarta
                        Serial.println("ERROR DE LECTURA");
                        sendACK(paquete_humedad.hum.idnodo,paquete_humedad.hum.type,0);
                        break;}
                      leerPaqueteHumedad(); //Ingreso del paquete a la estructura interna del dispositivo.
                      tb.sendTelemetryFloat("humidity", paquete_humedad.hum.val1); //Envio de los datos al servidor. 
                      sendACK(paquete_humedad.hum.idnodo,paquete_humedad.hum.type,1);
                      break;}
          
                 case CASE2:{
                      if(packetSize!=int(bufer[4])){
                        Serial.println("ERROR DE LECTURA");
                        sendACK(paquete_temperature.temp.idnodo,paquete_temperature.temp.type,0);
                        break;}
                      leerPaqueteTemperatura(); //Ingreso del paquete a la estructura interna del dispositivo. 
                      tb.sendTelemetryFloat("temperature", paquete_temperature.temp.val1); //Envio de los datos al servidor. 
                      sendACK(paquete_temperature.temp.idnodo,paquete_temperature.temp.type,1);
                      break;}
                                                                                     
                 case CASE3:{ 
                     if(packetSize!=int(bufer[4])){
                      Serial.println("ERROR DE LECTURA");
                      sendACK(paquete_voltaje.volt.idnodo,paquete_voltaje.volt.type,0);
                      break;}
                      leerPaqueteVoltaje(); //Ingreso del paquete a la estructura interna del dispositivo.
                      tb.sendTelemetryFloat("voltage", paquete_voltaje.volt.val1); //Envio de los datos al servidor.
                      sendACK(paquete_voltaje.volt.idnodo,paquete_voltaje.volt.type,1);
                 break;}
          }
          }
          }
          }
