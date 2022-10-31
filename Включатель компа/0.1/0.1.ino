
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define OPT 2 // D1

const char* ssid = "Cats_Ass"
const char* pas = "12345678s"
const char* Bitt = "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI"

WiFiClientSecure net_ssl; 
TelegramBot bot (Bitt, net_ssl);

void setup() {

   Serial.begin (9600);
   Serial.println(Jopa);
   
   WiFi.begin(ssid, pas);
     Serial.print("Connecting");
     
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Bot.begin();

  pinMode(OTP, OUTPUT);
}

void loop() {
  message m = bot.getUodates();

  if (m.text.equals("Я пидор")){
    digitalWrite(OTP, HIGH);
    bot.sendMessage(Что правда то правда);

  }else if (m.text.equals("off")){
    digitalWrite(OTP, LOW);
     bot.sendMessage(и кстати пошел нахуй);
  }
}

}
