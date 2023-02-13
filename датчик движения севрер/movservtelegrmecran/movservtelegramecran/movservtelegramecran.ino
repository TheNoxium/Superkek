int ledPin = D8;   
int inputPin = D3;               // Выбираем пин для входа датчика
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
#include <SSD1306Wire.h>
#include "fontsRus.h"
#include "images.h"
SSD1306Wire display(0x3c, 5, 4); // SDA - IO5 (D1), SCL - IO4 (D2) 

#include <SPI.h>
#include <SD.h>
File dataFile;
String buffer;

const int chipSelect = D8;

 
void setup() {
  pinMode(ledPin, OUTPUT);      // Объявляем контакт светодиода как выходной
  pinMode(inputPin, INPUT);     // Объявляем контакт датчика как входной
  display.init(); //  Инициализируем дисплей
  display.flipScreenVertically(); // Устанавливаем зеркальное отображение экрана, к примеру, удобно, если вы хотите желтую область сделать вверху
  display.setFontTableLookupFunction(FontUtf8Rus);
   
 
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
Serial.println("здоровапеддики");
  WiFiClient client;
  delay(100);
SD.begin( chipSelect );
       Serial.println("initialization failed!");
     //  return;
    
    delay(100);
    // открываем файл для чтения
    File dataFile = SD.open("test.txt");
    if (dataFile) {
        // считываем все байты из файла и выводим их в COM-порт
       while (dataFile.available()) //Читаем содержимое файла
  {
    buffer = dataFile.readStringUntil('\n');//Считываем с карты весь дотекст в строку до символа окончания.
    Serial.println(buffer); 
    SD.end("test.txt"); // для отладки отправляем по UART все что прочитали с карты.
     if (buffer == "PISKA")
  {Serial.println("пошел нахуй");
    display.clear();
    display.setFont(ArialRus_Plain_16); 
      display.drawString(0, 30, "пошел нахуй");
       display.display(); 
       delay(10000);
       display.clear();
          display.drawString(0, 26, " ");
  
  display.display(); 
    
  } 
    Serial.println("пиздую дальше");
   SD.end("test.txt");
  }
  dataFile.close(); //закроем файл
    } else {
        // выводим ошибку если не удалось открыть файл
        Serial.println("error opening test.txt");
    

  
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
    display.clear();
    display.setFont(ArialRus_Plain_16); 
      display.drawString(0, 30, "Чё пришел?");
       display.display(); 
       display.drawXbm(90, 20, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
       display.display();
      
    }

    
  } 
  else 
  { 
    digitalWrite(ledPin, LOW);
  
    if (pirState == HIGH)
  {
      display.clear();
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
        display.clear();
          display.drawString(0, 26, " ");
  
  display.display(); 
  Serial.println(" очищаю экран ");
    delay(100); 
     
    }
  }
    }
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

    return (uint8_t) 0;
}
