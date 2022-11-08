#include <ESP8266WiFi.h>


#define WIFI_SSID "Cats_Ass"
#define WIFI_PASS "12345678s"

const char* host = "192.168.1.5644";       // Локальный адрес
const uint16_t port = 80;                 // Порт

int temp = 13;
int hum = 56;
  
byte val;


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
  if (Serial.available()) 
  {   
   val = Serial.parseInt();
     if (val == 1) 
     {
      Serial.println("включаюсь");
       
  WiFiClient client;
  
  if (client.connect(host, port))
  {
    Serial.println("конекчусь как ебанучка");
    client.print("GET /insert.php?");
     Serial.print("Отправляю: GET /insert.php?");
    client.print("temp=");
     Serial.print("temp=");
    client.print(temp);
     Serial.print(temp);
    client.print("&hum=");
     Serial.print("&hum=");
    client.print(hum);
     Serial.print(hum);
    client.println(" HTTP/1.1");
     Serial.println(" HTTP/1.1");
  client.print( "Host: " );
   Serial.print("Host: ");
  client.println(host);
   Serial.print(host);
  client.println( "Connection: close" );
   Serial.println("Connection: close");
  client.println();
   Serial.println();
  client.println();
   Serial.println();

    
  //  while (client.connected())                          //Ответ
   // {
    // if (client.available())
    //  {
      //  String line = client.readStringUntil('\n');
      //  Serial.println("получил парашу");
      //  Serial.println(line);
     // }
   // }
   // client.stop();
   //  Serial.println("остонавливаюсь");// Остановить клиента
    
  }else{
    
    client.stop(); 
    Serial.println("Я обосрался ошибка подключения");                          // Ошибка подключения
  }
  delay(20000);                         // Ждём 10 мекунд
}else{
    Serial.println("включаю елсе пошел нахуй");
     }
}
  
}
