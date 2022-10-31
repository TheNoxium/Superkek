#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define OPT 2 // D1

const char* ssid = "Cats_Ass";
const char* pas = "12345678s";
const char BotToken[] = "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI";

WiFiClientSecure net_ssl; 
TelegramBot bot (BotToken, net_ssl);

void setup() {

   Serial.begin (9600);
   Serial.println("Jopa");
   
   WiFi.begin(ssid, pas);
     Serial.print("Connecting");
     
  while (WiFi.status() != WL_CONNECTED){
   
  
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  bot.begin();

  pinMode(OPT, OUTPUT);
}

void loop() {
  message m = bot.getUpdates();

  if (m.text.equals("Я пидор")){
    digitalWrite(OPT, HIGH);
    bot.sendMessage(m.chat_id, "Что правда то правда");

  }else if (m.text.equals("off")){
    digitalWrite(OPT, LOW);
     bot.sendMessage(m.chat_id, "и кстати пошел нахуй");
  }
}
