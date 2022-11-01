#define WIFI_SSID "Cats_Ass"
#define WIFI_PASS "12345678s"
#define BOT_TOKEN "1617873195:AAGpNItFduM1HgtZeajYfM0s9ZsMAP-jLaI"
//#define 2 "LED_BUILTIN"

#include <FastBot.h>

FastBot bot(BOT_TOKEN);
void setup() {
  connectWiFi();
  bot.setChatID("-847090362, 1488559189");
  bot.sendMessage("Здарова пидарас, чо опять решил в свой копуктер играть из своей турции, лучше бы ты сосал хуи как профессиональная шлюха чем лез сюда, Щенок!");
  bot.attach(newMsg);
  pinMode(D0, OUTPUT);
}
// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  Serial.print(msg.chatID);     // ID чата 
  Serial.print(", ");
  Serial.print(msg.username);   // логин
  Serial.print(", ");
  Serial.println(msg.text);     // текст
 // bot.sendMessage(msg.text, msg.chatID);  
 if (msg.text == "Я уже грязная шлюха") bot.sendMessage("Да сучка это так!", msg.chatID);
 delay(1000);
 if (msg.text == "Я уже грязная шлюха") bot.sendMessage("Продолжай говорить что ты дрянь", msg.chatID);
 delay(2000);
if (msg.text == "Я уже грязная шлюха") bot.sendMessage("Меня это пиздец как заводит", msg.chatID); 
delay(3000);
if (msg.text == "Я уже грязная шлюха") bot.sendMessage("Хочешь чтобы я включил твой ПК, падаль?", msg.chatID); 

if (msg.text == "Да") bot.sendMessage("Скажи мне что ты пидорок!", msg.chatID);
if (msg.text == "Я пидорок") bot.sendMessage("Ну ладно я включаю твою разьебайку!", msg.chatID);
if (msg.text == "Я пидорок") digitalWrite(D0, HIGH );
delay(200);
digitalWrite(D0, LOW);

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
