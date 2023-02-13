
int ledPin = D2;                // Выбираем пин для светодиода
int inputPin = D1;               // Выбираем пин для входа датчика
int pirState = LOW;             // Переменная состояния датчика
int val = 0;                    // Переменная для чтения статуса состояния датчика

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <FastBot.h>

const char* ssid = "Cats_Ass";
const char* password = "12345678s";

const char* host = "192.168.1.94";

#define BOT_TOKEN "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI"
FastBot bot(BOT_TOKEN);
 
void setup() {
  pinMode(ledPin, OUTPUT);      // Объявляем контакт светодиода как выходной
  pinMode(inputPin, INPUT);     // Объявляем контакт датчика как входной
   
 
  Serial.begin(9600);

  Serial.printf("Здорова отец ");

   Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  bot.setChatID("-847090362, 1488559189");
  

  
}
 
void loop(){
  WiFiClient client;
  val = digitalRead(inputPin);
  
  if (val == HIGH)
  {            
    digitalWrite(ledPin, HIGH);
  
    if (pirState == LOW) 
  {
      Serial.println("Motion detected!");
      pirState = HIGH;
       Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
  
    Serial.println("connected к открыть]");
    client.print( "GET /controlop1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
    delay(100); 
    
    bot.sendMessage("На бунгало нападение");
    }

    
  } 
  else 
  {
    digitalWrite(ledPin, LOW);
  
    if (pirState == HIGH)
  {
      Serial.println("Motion ended!");
      pirState = LOW;
       Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);
  
         Serial.println("connected к закрыть]");
    client.print( "GET /controlcl1.php?");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(host);
    client.println( "Connection: close" );
    client.println();
    client.println();
    client.stop();
    client.flush();
      delay(100); 
      bot.sendMessage("Нападение окончено");
    }
  }
}
