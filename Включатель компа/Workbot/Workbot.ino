#include <FastBot.h>
#include <ESP8266WiFi.h>
#define WIFI_SSID "Cats_Ass"
#define WIFI_PASS "12345678s"
#define BOT_TOKEN "xxxx"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  Serial.println("Пошел Нахуй");
  

 
}
void loop() {
}
