/*Nayadeth Aguirre - 2021
 *Contiene las funciones asociadas a la estructura principal de la programación del sistema.
*/

/*Inclusión de bibliotecas*/
#include "definition.h"

/*Funcion de envio de datos de humedad*/
 void sendHumedad(){
  paquete_humedad.hum.val1=77;
  for(int i=0; i<12; i++){bufHumedad[i]=paquete_humedad.paquete_humedad[i];}
  LoRa.beginPacket();
  LoRa.write(bufHumedad,sizeof(bufHumedad));
   Serial.println( paquete_humedad.hum.val1);
  LoRa.endPacket();
  } 

/*Funcion de envio de datos de voltaje*/
  void sendVoltaje(){  
  paquete_voltaje.volt.val1=88;
  for(byte i=0; i<12; i++){bufVoltaje[i]=paquete_voltaje.paquete_voltaje[i];}
  LoRa.beginPacket();
  LoRa.write(bufVoltaje,sizeof(bufVoltaje));
     Serial.println(paquete_voltaje.volt.val1);

  LoRa.endPacket();
  } 


/*Funcion de envio de datos de temperatura*/
  void sendTemperature(){
    paquete_temperature.temp.val1= 99;
    for(int i=0; i<12; i++){bufTemperature[i]=paquete_temperature.paquete_temperature[i];}
      LoRa.beginPacket();
      LoRa.write(bufTemperature,sizeof(bufTemperature));
       Serial.println( paquete_temperature.temp.val1);
      LoRa.endPacket();
  }


/*Funcion para recibir mensaje de aceptación del servidor*/
  void recibirACK(){
    int packetSize = LoRa.parsePacket();
  if (packetSize) {
      for (int i = 0; i < packetSize; i++) {buferACK[i] = LoRa.read();}
      if (buferACK[0] == ids[0] && buferACK[1] == idnodo[0]){
          switch (bufer[3]){
                 case 0x24:{
                  
                      if(packetSize!=int (bufer[4])){
                      Serial.println("ERROR DE LECTURA");
                      break;}
                      for (int i = 0; i <12; i++) {paquete_humedad.paquete_humedad[i] = bufer[i];}
                      Serial.println("RECIBIDO ACK"); 
                      Serial.println(paquete_humedad.hum.val1);
                      recibido=true;
                 break;}
                
          }
    }
  }
  }
