#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define OPT 0 // D1

const char* WIFI_SSID = "Cats_Ass";
const char* WIFI_PAS = "12345678s";
const char BotToken[] = "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI";

WiFiClientSecure net_ssl; 
TelegramBot bot (BotToken, net_ssl);

void setup() {
 Serial.begin(9600);
  configTime(0,0, "pool.ntp.org");
  //secured_client.setTrustAnchors(&cert);
  Serial.print("Connected to WiFi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PAS);
  while (WiFi.status() !=WL_CONNECTED)
  {
    Serial.print(".");
    delay(3000);
  }
    Serial.print("\nWiFi connected. IP addres: ");
    Serial.println(WiFi.localIP());
   

  bot.begin();

  pinMode(OPT, OUTPUT);
}

void loop() {
 message m = bot.getUpdates();

 if (m.text.equals("Я пидор")){
    digitalWrite(OPT, HIGH);
    bot.sendMessage(m.chat_id, "Что правда то правда");

 }
 else if (m.text.equals("off")){
    digitalWrite(OPT, LOW);
     bot.sendMessage(m.chat_id, "и кстати пошел нахуй");
  }
}
