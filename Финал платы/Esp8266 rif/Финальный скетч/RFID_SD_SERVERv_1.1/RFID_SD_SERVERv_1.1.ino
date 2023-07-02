#include <SPI.h>
#include <SD.h>

#include <ESP8266WiFi.h>
#include <MFRC522.h>



File dataFile;
String buffer;

String demon = "PENIS";

String namedemon = "test.txt";

int chipSelect = D8;

const char* ssid = "Cats_Ass";
const char* password = "12345678s";

const char* host = "192.168.1.94";

int buff;


int LEDGREAN_PIN = D0;  //зеленый
int LEDRED_PIN = D1;    //красны
int LEDBLUE_PIN = D2;   //синий




constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;

MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String tag;

unsigned long pass_timerwifi;

unsigned long pass_timerrfid;

char c;

void setup() {
  // delay(1000);

  Serial.begin(115200);




  pinMode(LEDGREAN_PIN, OUTPUT);
  pinMode(LEDRED_PIN, OUTPUT);


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


  Serial.printf("Подключение к Wi-Fi сети %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Модуль успешно подключен к Wi-Fi сети. ");
}


void loop() {

  if (buffer == demon) {
    Demon();
    buff1();
    controlop1();
    delay(10000);
    controlcl1();


  } else {


    if (millis() - pass_timerwifi > 10000) {
      pass_timerwifi = millis();
      wificonnectdata();
      Demon();
      //Serial.println(buff);
      // Serial.print("значение");
    }

    if (buff == 0) {
      //Serial.println("Замок закрыт");
      buff2();

      rfidlock();

    } else {
      //Serial.println("Замок открыт");
      buff1();

      //delay(10000);
    }
  }
}



void wificonnectdata() {
  Serial.println("Передача состояние веб контроллера ");
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80)) {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET /data.php?") + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n" + "\r\n");

    Serial.println("[Response:]");

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        char c = client.read();
        //Serial.println(c);
        if (c == '1') {
          buff = 1;
          Serial.println("Открыто");
        }
        if (c == '0') {
          buff = 0;
          Serial.println("Закрыто");
          rfidlock();
        }
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  } else {
    Serial.println("connection failed!]");
    client.stop();
    buff = 0;
  }
  Serial.println("Остановка подключения");
}


void Demon() {

  Serial.println("Проверяю слот SD");

  if (SD.begin(chipSelect)) {

    if (SD.open(namedemon)) {
      Serial.println("Апаратный код успешно распознан рааспознан");
      File dataFile = SD.open(namedemon);
      buffer = dataFile.readStringUntil('\n');
      Serial.println(buffer);
      if (buffer == demon) {
        Serial.println("Активация апаратного кода");
        Serial.print("Апаратный код:");
        Serial.println(demon);
        buff = 1;

      } else {
        Serial.println("Апаратный код не рааспознан");
        buffer = "LOX";
      }
    } else {
      Serial.println("Апаратный код не распознан");
      buffer = "LOX";
    }

    SD.end(chipSelect);
  } else {
    SD.end(chipSelect);
    Serial.println("SD карты не найдено");
    buffer = "LOX";
  }
}


void buff1() {

  digitalWrite(LEDRED_PIN, LOW);
  digitalWrite(LEDBLUE_PIN, LOW);
  digitalWrite(LEDGREAN_PIN, HIGH);
}

void buff2() {

  digitalWrite(LEDGREAN_PIN, LOW);
  digitalWrite(LEDRED_PIN, HIGH);
  digitalWrite(LEDBLUE_PIN, LOW);
}

void controlcl1() {

  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);

  Serial.println("connected к закрыть]");
  client.print("GET /controlcl1.php?");
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  client.flush();
}

void controlop1() {
  WiFiClient client;
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);

  Serial.println("connected к открыть]");
  client.print("GET /controlop1.php?");
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  client.flush();
}

void rfidlock() {

  SPI.begin();
  rfid.PCD_Init();

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "5113184173") {
      Serial.println("Ключ верный, доступ открыт.");

      buff1();
      controlop1();
      delay(5000);
      buff2();
      controlcl1();
    }

  } else if (tag == "1606717532") {
    Serial.println("Ключ верный, доступ открыт.");

    buff1();
    controlop1();
    if (millis() - pass_timerrfid > 10000) {
      pass_timerrfid = millis();
      buff2();
      controlcl1();
    }



  } else {
    Serial.println("Ключ не верен. В доступе октазано.");
  }
  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}