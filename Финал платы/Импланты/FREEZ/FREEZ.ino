#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <SSD1306Wire.h>
#include "fontsRus.h"
SSD1306Wire display(0x3c, 5, 4);  // SDA - IO5 (D1), SCL - IO4 (D2)

/* Установите здесь свои SSID и пароль */
const char* ssid = "IH*Cu9wzz7PE78F";  // SSID
const char* password = "";     // пароль

/* Настройки IP адреса */
IPAddress local_ip(192, 168, 1, 23);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

uint8_t LED1pin = D7;
bool LED1status = LOW;

uint8_t LED2pin = D6;
bool LED2status = LOW;

void setup() {


  Serial.begin(115200);
  display.init();                  //  Инициализируем дисплей
  display.flipScreenVertically();  // Устанавливаем зеркальное отображение экрана, к примеру, удобно, если вы хотите желтую область сделать вверху
  display.setFontTableLookupFunction(FontUtf8Rus);


  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  LED1status = LOW;
}

void loop() {
  server.handleClient();
  if (LED1status) {
    digitalWrite(LED1pin, HIGH);

    display.clear();  // Очищаем экран



    display.drawHorizontalLine(0, 14, 128);  // Горизонтальная линия

    display.clear();
    display.setFont(ArialRus_Plain_16);  // Шрифт кегль 24
    display.drawString(0, 40, "перезарядка");
    display.display();  // Выводим на экран
    delay(72000);
    LED1status = LOW;

  } else {
    digitalWrite(LED1pin, LOW);
    display.clear();
     display.setFont(ArialRus_Plain_16); // Шрифт кегль 16
  display.drawString(0, 25, "ФРИИЗ");
    display.setFont(ArialRus_Plain_24);  // Шрифт кегль 24
    display.drawString(0, 40, "Готов");
    display.display();  // Выводим на экран
  }
}
void handle_OnConnect() {
  Serial.print("GPIO7 Status: ");
  if (LED1status)
    Serial.print("ON");
  else
    Serial.print("OFF");




  Serial.println("");
  server.send(200, "text/html", SendHTML(LED1status, LED2status));
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true, LED2status));
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false, LED2status));
}



void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat, uint8_t led2stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Implant server</h1>\n";
  ptr += "<h3>FREEZ</h3>\n";

  if (led1stat)
    ptr += "<p>LED1 Status: Ready</p><a class=\"button button-off\" href=\"/led1off\">Reload</a>\n";
  else
    ptr += "<p>LED1 Status: Reload</p><a class=\"button button-on\" href=\"/led1on\">Ready</a>\n";



  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

char FontUtf8Rus(const byte ch) {
  static uint8_t LASTCHAR;

  if ((LASTCHAR == 0) && (ch < 0xC0)) {
    return ch;
  }

  if (LASTCHAR == 0) {
    LASTCHAR = ch;
    return 0;
  }

  uint8_t last = LASTCHAR;
  LASTCHAR = 0;

  switch (last) {
    case 0xD0:
      if (ch == 0x81) return 0xA8;
      if (ch >= 0x90 && ch <= 0xBF) return ch + 0x30;
      break;
    case 0xD1:
      if (ch == 0x91) return 0xB8;
      if (ch >= 0x80 && ch <= 0x8F) return ch + 0x70;
      break;
  }

  return (uint8_t)0;
}