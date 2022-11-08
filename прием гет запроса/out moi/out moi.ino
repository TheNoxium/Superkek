
 
//#include <SPI.h>
//#include <ArduinoJson.h> 
#include <ESP8266WiFi.h>
 

                    //подключаем библиотеку I2C LCD

 
const char* WIFI_SSID = "Cats_Ass";                 //имя точки доступа
const char* WIFI_PASS = "12345678s";               //пароль wifi
 
const char* host = "192.168.1.56";
const int port = 80;
String line; 
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  Serial.println(" Пошел Нахуй, я в твоей сети ");
 
                                 

 

  
 
  WiFiClient client;

 if (client.connect(host, port))
  {
    Serial.println(" конекчусь как ебанучка ");
    client.print("GET /data.php");
     Serial.print(" Отправляю: GET /data.php ");
    client.println(" HTTP/1.1");
     Serial.println(" HTTP/1.1 ");
  client.print( "Host: " );
   Serial.print("Host: ");
  client.println(host);
   Serial.println(host);
  client.println( "Connection: close");
   Serial.println(" Connection: close ");
  client.println();
   Serial.println();
  client.println();
   Serial.println(" Все заебига ");

    
     Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String c = client.readStringUntil('\n');
        //Serial.println(line);
        //char c = client.read();
        Serial.println(c);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);

  
}
 
void loop() {
   
  //  client.println("GET /ard/1.php HTTP/1.1");
  
}