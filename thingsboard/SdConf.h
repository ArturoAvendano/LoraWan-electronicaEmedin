/*
Arturo Avendaño - 2021
Biblioteca de configuración e integración de la tarjeta uSD en el dispositivo.
Maneja la comunicación de hardware con el dispositivo SPI y la utilización de archivos en la memoria.
*/

/*Integración de bibliotecas*/
#include "FS.h" 
#include "SD.h"
#include "SPI.h"

/*Definición SPI*/
SPIClass spiSD(HSPI);
#define SD_CS 5
#define SDSPEED 27000000
uint8_t cardType = SD.cardType();


/*INICILIZACIÓN DE LA TARJETA uSD*/
void InitSD(){
      spiSD.begin(14,15,13,5);//SCK,MISO,MOSI,ss 
    if(!SD.begin( SD_CS, spiSD, SDSPEED)){
      Serial.println("Card Mount Failed");
      }
  }

/*COMPROBACIÓN DE LA TARJETA uSD*/
void comprobarTarjeta(){
  
    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }
  }

/*FUNCIÓN DE ANEXACIÓN DE INFORMACIÓN A UN ARCHIVO*/
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

/*FUNCIÓN PARA ABRIR UN ARCHIVO EN FORMA DE ESCRITURA, PERMITE OPERAR DENTRO DEL ARCHIVO ASIGNADO*/
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

/*FUNCION DE SOLO LECTURA*/
void readFile(fs::FS &fs, const char * path,uint8_t ids[],uint8_t idnodo[],uint8_t idrepeat[]){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    
        ids[0]=uint8_t(file.read());
        idnodo[0]=uint8_t(file.read());
        idrepeat[0]=uint8_t(file.read());
    
    file.close();
}
