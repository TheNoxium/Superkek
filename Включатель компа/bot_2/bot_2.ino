#define WIFI_SSID "Cats_Ass"
#define WIFI_PASS "12345678s"
#define BOT_TOKEN "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI"
#include <FastBot.h>
FastBot bot(BOT_TOKEN);
void setup() {
  connectWiFi();
  bot.attach(newMsg);
}
// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  Serial.print(msg.chatID);     // ID чата 
  Serial.print(", ");
  Serial.print(msg.username);   // логин
  Serial.print(", ");
  Serial.println(msg.text);     // текст
  bot.sendMessage(msg.text, msg.chatID);  
}
  

void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
  Serial.println("Пошел Нахуй");
}
