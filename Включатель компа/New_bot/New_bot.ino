#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "Cats_Ass"
#define WIFI_PAS "12345678s"

WiFiClientSecure secured_client;
#define BOT_TOKEN "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI"
#define CHAT_ID "1488559189" // api.telegram.org/bot1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI/getUpdates

const unsigned long  BOT_MTBS = 3000;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
//UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;

void setup() {
 // Serial.begin(9600);
 // configTime(0,0, "pool.ntp.org");
 // secured_client.setTrustAnchors(&cert); 
  //Serial.print("Connected to WiFi SSID ");
 // Serial.print(WIFI_SSID);
  //WiFi.begin(WIFI_SSID, WIFI_PAS);
 // while (WiFi.status() !=WL_CONNECTED)
//  {
    Serial.print(".");
   // delay(300);
 // }
    //Serial.print("\nWiFi connected. IP addres: ");
    //Serial.println(WiFi.localIP());

    //bot.sendMessage(CHAT_ID, "HI PIDOR", "");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
