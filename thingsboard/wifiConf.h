/*
Arturo Avendaño - 2021
Biblioteca de configuración de la comunicación WiFi integrada en el dispositivo.
Maneja el envio y recepción de datos sobre la red WiFi asignada en la configuración.
*/

/*Inclusión de bibliotecas*/
#include <WiFi.h>
#include <ThingsBoard.h>

/*Definición de estados para la conexión WiFi*/
#define WIFI_AP_NAME        "REEMPLAZAR CON NOMBRE WIFI"
#define WIFI_PASSWORD       "REEMPLAZAR CON CLAVE WIFI"
WiFiClient espClient;
int status = WL_IDLE_STATUS;

/*Definición para la conexión con el servidor Thingsboard*/
#define TOKEN               "REEMPLAZAR CON TOKEN THINGSBOARD"
#define THINGSBOARD_SERVER  "REEMPLAZAR CON IP SERVIDOR THINGSBOARD"
#define THINGSBOARD_PORT 8080
ThingsBoardHttp tb(espClient, TOKEN, THINGSBOARD_SERVER, THINGSBOARD_PORT);

/*FUNCIÓN DE INICIALIZACIÓN WIFI*/
void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

/*FUNCIÓN DE RECONEXIÓN WIFI*/
void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
