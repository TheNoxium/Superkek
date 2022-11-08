#include <ESP8266WiFi.h>

const char* ssid = "Cats_Ass";
const char* password = "12345678s";

const char* host = "192.168.1.56";

int buff=0;

//char c;
int led = 16;

void setup()
{
  pinMode(led, OUTPUT);
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
        }
        else
        {
          digitalWrite(led, LOW);
        }
  delay(500);
  Serial.println(buff);
  delay(500);

}