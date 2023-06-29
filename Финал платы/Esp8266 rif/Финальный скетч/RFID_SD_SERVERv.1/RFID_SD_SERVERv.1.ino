#include <SPI.h>
#include <SD.h>

#include <ESP8266WiFi.h>
#include <MFRC522.h>



File dataFile;
String buffer;

String demon = "PENIS";

int chipSelect = D8;

const char* ssid = "Cats_Ass";
const char* password = "12345678s";

const char* host = "192.168.1.94";

int buff;


int led = D0;   //зеленый
int led2 = D1;  //красны
int led3 = D2;  //синий




constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String tag;

unsigned long pass_timerwifi;

char c;

void setup() {
  // delay(1000);

  Serial.begin(115200);


  //SPI.begin();  // Init SPI bus
  //rfid.PCD_Init();

  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);


  // delay(1000);

  Serial.println("Включение");

  // delay(1000);

  Serial.println("Arasaka Corporation");
  Serial.println("Включение модуля RFID RC522");
  Serial.println("Включение модуля Micro SD");
  Serial.println("Загрузка прошивки RFID_SD_SERVER_v.1");
  Serial.println();

  // delay(1000);

  Serial.println("Запуск Wi-Fi модуля");


  Serial.printf("Подулючение к Wi-Fi сети %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf(" Модуль успешно подключен к Wi-Fi сети", ssid);
}


void loop() {

  if (millis() - pass_timerwifi > 1000) {
    pass_timerwifi = millis();
    //wificonnectdata();
    Demon();
    //Serial.println("buff");
    //Serial.print(buff);
  }
}

void wificonnectdata() {
  //buff = 2;
  Serial.println("Передача состояние веб контроллера ");

  WiFiClient client;

  Serial.printf("\n[Подключение к хосту %s ... ", host);
  if (client.connect(host, 80)) {
    Serial.println("Потключено]");
    client.print("GET /data.php?");
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    client.println();
    //client.println();


    delay(50);

    while (client.available()) {


      String line = client.readStringUntil('\n');
      //Serial.print("Информация полученная с сервера: ");
      //Serial.println(line);

      char c = client.read();

      if (c == '1') {
        buff = 1;
      }
      if (c == '0') {
        buff = 0;
      }
    }
    client.stop();
    client.flush();
    delay(500);
  } else {

    client.stop();
    Serial.println("Ошибка подключения");
    delay(1000);
    client.connect(host, 80);
  }
  Serial.println("Остановка подключения");
  Serial.println(buff);
}


void Demon() {

  Serial.println("Проверяю слот SD");

  if (SD.begin(chipSelect)) {
    Serial.print(SD.begin(chipSelect));
    if (SD.open("test.txt")) {
      Serial.println("Апаратный код успешно распознан рааспознан");
      Serial.println(SD.open("test.txt"));
      File dataFile = SD.open("test.txt");
      buffer = dataFile.readStringUntil('\n');
      Serial.println(buffer);
      if (buffer == demon) {
        Serial.println("Активация апаратного кода");
      } else {
        Serial.println("Апаратный код не рааспознан");
      }
    } else {
      Serial.println("Апаратный код не распознан рааспознан");
    }

    SD.end(chipSelect);
  } else {
    SD.end(chipSelect);

    Serial.print(SD.begin(chipSelect));
    Serial.println("SD карты не найдено");
  }
}
