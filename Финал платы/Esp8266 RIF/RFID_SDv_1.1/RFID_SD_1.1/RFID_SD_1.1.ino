#include <SPI.h>
#include <SD.h>

#include <ESP8266WiFi.h>
#include <MFRC522.h>



File dataFile;
String buffer;

String demon = "potato";

String namedemon = "demon.txt";

int chipSelect = D8;

const char* ssid = "NIGHT CITY FREE WIFI";
const char* password = "88888888";



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
  delay(1000);

  Serial.begin(115200);




  pinMode(LEDGREAN_PIN, OUTPUT);
  pinMode(LEDRED_PIN, OUTPUT);


  delay(100);

  Serial.println("Включение");

  delay(100);

  Serial.println("Arasaka Corporation");
  delay(100);
  Serial.println("Включение модуля RFID RC522");
  delay(100);
  Serial.println("Включение модуля Micro SD");
  delay(100);
  Serial.println("Загрузка прошивки RFID_SD_SERVER_v.1");
  Serial.println();

  delay(100);
}


void loop() {

  if (buffer == demon) {
    Demon();
    buff1();
    //controlop1();
    delay(10000);
    //controlcl1();


  } else {


    if (millis() - pass_timerwifi > 10000) {
      pass_timerwifi = millis();
      //wificonnectdata();
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






void Demon() {

  Serial.println("Проверяю слот SD");

  if (SD.begin(chipSelect)) {
    Serial.println("SD карта найдена");
    if (SD.open(namedemon)) {
      Serial.println("Имя файла апаратного кода успешно рааспознано");
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
      Serial.println("Имя файла апаратного кода не рааспознано");
      buffer = "LOX";
    }

    SD.end(chipSelect);
  } else {
    SD.end(chipSelect);
    Serial.println("SD карта не найдена");
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
    if (tag == "5110850246") {
      Serial.println("Ключ верный, доступ открыт.");

      buff1();
      //controlop1();
      delay(10000);
      buff2();
      // controlcl1();
    }

    else if (tag == "115155246") {
      Serial.println("Ключ верный, доступ открыт.");

      buff1();
      //controlop1();
      delay(10000);
      buff2();
      //controlcl1();




    } else if (tag == "") {
      Serial.println("Ключ верный, доступ открыт.");

      buff1();
      //controlop1();
      delay(10000);
      buff2();
      //controlcl1();




    }else {
      Serial.println("Ключ не верен. В доступе октазано.");
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}