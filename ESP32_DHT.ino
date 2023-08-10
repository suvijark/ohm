#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid     = "OPPO A31";      // SSID เปลี่ยนชื่อWIFI
const char* password = "tew123456";      // เปลี่ยนPasswordWIFI 
const char* host = "192.168.43.173";  // IP serveur - Server IP เปลี่ยนIP =IPCONFIG
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 


#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT22   // DHT 22

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
void setup(void)
{ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humedad y Temperatura\n\n");
  delay(700);

}
void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();    
    //int h = random(1,100);
   // int t = random(1,100);     
    Serial.print("Humedad = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.println("°C  ");

    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/TutorialESP32/lol.php?temp=";     //เปลี่ยนเป็นชื่อฟายที่ใช้
    url += t;
    url += "&hum=";
    url += h;
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
