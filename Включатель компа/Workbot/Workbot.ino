#include <ESP8266WiFi.h>


#define WIFI_SSID "Cats_Ass"
#define WIFI_PASS "12345678s"

const char* host = "192.168.1.56";       // Локальный адрес
const uint16_t port = 80;                 // Порт

int temp = 12;
int hum = 55;
  

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  Serial.println("Пошел Нахуй, я в твоей сети");
  

 
}
void loop() {
  
 delay(2000);
  
  WiFiClient client;
  
  if (client.connect(host, port))
  {
    Serial.println("конекчусь как ебанучка");
    client.print("GET /insert.php?");
     Serial.println("Отправляю GET /insert.php?");
    client.print("temp=");
     Serial.println("Отправляю temp=");
    client.print(temp);
     Serial.println(temp);
    client.print("&hum=");
     Serial.println("Отправляю &hum=");
    client.print(hum);
     Serial.println(hum);
    client.println(" HTTP/1.1");
     Serial.println("Отправляю HTTP/1.1");
  client.print( "Host: " );
   Serial.println("Отправляю Host: ");
  client.println(host);
   Serial.println(host);
  client.println( "Connection: close" );
   Serial.println("Отправляю Connection: close");
  client.println();
   Serial.println("Отправляю пустоту");
  client.println();
   Serial.println("Отправляю пустоту");

    
    while (client.connected())                          //Ответ
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println("получил парашу");
      }
    }
    client.stop();
     Serial.println("остонавливаюсь");// Остановить клиента
    
  }else{
    
    client.stop(); 
    Serial.println("Я обосрался ошибка подключения");                          // Ошибка подключения
  }
  delay(10000);                         // Ждём 10 мекунд
}
