#include <ESP8266WiFi.h>

const char* ssid = "Elisium";
const char* password = "888888881";

const char* host = "192.168.1.94";

int buff=0;

//char c;
int led = 16;
int led2 = 5;
int led3 = 12;
int tonepin = 04;
int rad = 15;

//int temp = 123;
//int hum = 123;
  

void setup()
{
  Serial.printf("Здорова отец ");
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(tonepin, OUTPUT);
  pinMode(rad  , OUTPUT); 
  
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

}


void loop()
{

 WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    client.print( "GET /data.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    
   
    delay(200);
         
      while (client.available())
 {
      String line = client.readStringUntil('\n');
      //Serial.print(line);
    
    
      char c = client.read();
        if ( c=='1')
        {
        buff=1;
        tone (tonepin,200);
         delay(100);
         tone (tonepin,200);
         delay(100);
         tone (tonepin,200);
         delay(100);
         noTone(tonepin);
        }
        if ( c=='0')
        {
         buff=0;
        }
      } 
    
      client.stop();
      client.flush();
      delay(100); 
  }
  else 
  {
   client.stop();
   delay(1000);
   client.connect(host, 80);
  }
  if ( buff==1)
        {
        digitalWrite (led, HIGH);
        digitalWrite (led2, LOW);
        digitalWrite (rad, HIGH); 
        }
        else
        {
           digitalWrite(led, LOW);
           digitalWrite(led2, HIGH);
           digitalWrite (rad, LOW);
        }
  delay(500);
  Serial.println(buff);


  
  if (client.connect(host, 80))
  {
    Serial.println("конекчусь как ебанучка");
    client.print("GET /insert.php?");
     Serial.print("Отправляю: GET /insert.php?");
   //client.print("temp=");
    // Serial.print("temp=");
   // client.print(temp);
   //  Serial.print(temp);
   // client.print("&hum=");
    // Serial.print("&hum=");
    //client.print(hum);
    // Serial.print(hum);
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
    



  delay(500);

}
