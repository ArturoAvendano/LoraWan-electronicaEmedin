/*Nayadeth Aguirre - 2021
 *Contiene las funciones asociadas a la estructura principal de la programación del sistema.
*/

/*Inclusión de bibliotecas*/
#include "definition.h"


/*Funcion de recepción y envio de datos de humedad*/
 void Paquete_Humedad(){
    if(packetSize!=int (bufer[4])){
      Serial.println("ERROR DE LECTURA");}
    for (i = 0; i <12; i++) {paquete_humedad.paquete_humedad[i] = bufer[i];} 
    paquete_humedad.hum.idrepeat=0x22;
    for(int i=0; i<12; i++){bufHumedad[i]=paquete_humedad.paquete_humedad[i];}
    LoRa.beginPacket();
    LoRa.write(bufHumedad,sizeof(bufHumedad));
    LoRa.endPacket();
    Serial.println("fin del paquete humedad");
    }
    

/*Funcion de recepción y envio de datos de temperatura*/
  void Paquete_Temperatura(){
    if(packetSize!=int(bufer[4])){
      Serial.println("ERROR DE LECTURA");
      }
    for (int i = 0; i <12; i++) {paquete_temperature.paquete_temperature[i] = bufer[i];}
    paquete_temperature.temp.idrepeat=0x22;
    for(int i=0; i<12; i++){bufTemperature[i]=paquete_temperature.paquete_temperature[i];}
    LoRa.beginPacket();
    LoRa.write(bufTemperature,sizeof(bufTemperature));
    LoRa.endPacket();
    }
    
/*Funcion de recepción y envio de datos de voltaje*/
  void Paquete_Voltaje(){
    if(packetSize!=int (bufer[4])){
      Serial.println("ERROR DE LECTURA");
      }
      for (i = 0; i <12; i++) {paquete_voltaje.paquete_voltaje[i] = bufer[i];}   
      paquete_voltaje.volt.idrepeat=0x22;
      for(int i=0; i<12; i++){bufVoltaje[i]=paquete_voltaje.paquete_voltaje[i];}
      LoRa.beginPacket();
    LoRa.write(bufVoltaje,sizeof(bufVoltaje));
    LoRa.endPacket();
    Serial.println("fin del paquete voltaje");
    Serial.println(paquete_voltaje.volt.val1);                
  }


/*Funcion de recepción de ack del servidor*/
void recibirACK(){
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
      for (i = 0; i < packetSize; i++) {buferACK[i] = LoRa.read();}
      if (buferACK[0] == ids[0] && buferACK[1] == idnodo[0] && buferACK[3]==0x24){
            if(packetSize!=int(bufer[4])){
               Serial.println("ERROR DE LECTURA");
               recibirACK();
                 }
             switch(buferACK[5]){
                case 0x21:
                  Paquete_Humedad(); 
                  break;
         
                case 0x22:
                  Paquete_Temperatura();    
                  break;
                                                                                     
                case 0x23:
                  Paquete_Voltaje();
                  break; 
               }   
           }
       }
    }
  


 
