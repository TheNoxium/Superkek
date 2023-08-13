#include "Keypad.h"  //библиотека клавиатуры
#include <EEPROM.h>

#include <WiFi.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"


#define LEDBLUE_PIN 17  // 4 blue
#define LEDGREAN_PIN 4  //16 grea
#define LEDRED_PIN 16   //17 red


const char* ssid = "NIGHT CITY FREE WIFI";
const char* password = "88888888";


const char* host = "192.168.1.203";

int buff = 0;


unsigned long pass_timer;
unsigned long pass_timerwifi;


File dataFile;

String path2 = "/demon.txt";
String buffer;

String demon = "boba";


char key;

String str_pass = "";
byte pass_lenght, j;
unsigned long int_pass;  // 10 знаков моксимум!!

char keys[3][4] = {
  { '0', '8', '5', '2' },
  { '#', '9', '6', '3' },
  { '*', '7', '4', '1' },

};
byte rowPins[] = { 14, 12, 27 };                                   // Подключены строки (4 пина)
byte colPins[] = { 26, 25, 33, 32 };                               // подключены столбцы (4 пина)
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 3, 4);  //иниициализировать клавиатуру

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.println("Включение");

  delay(1000);

  Serial.println("Militech International Armaments");
  delay(1000);
  Serial.println("Включение модуля CODELOCK");
  delay(1000);
  Serial.println("Включение модуля энергонезависимой памяти");
  delay(1000);
  Serial.println("Включение модуля Micro SD");
  delay(1000);
  Serial.println("Загрузка прошивки CODELOCK_SD_SERVERv_1");
  Serial.println();

  delay(1000);


  Serial.println("Запуск Wi-Fi модуля");


  Serial.printf("Подключение к Wi-Fi сети %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Модуль успешно подключен к Wi-Fi сети. ");


  EEPROM.begin(4);

  pinMode(LEDBLUE_PIN, OUTPUT);
  pinMode(LEDGREAN_PIN, OUTPUT);
  pinMode(LEDRED_PIN, OUTPUT);

  Serial.println("Активация пароля из энергонезависимой памяти");
  int_pass = EEPROM.get(0, int_pass);  // вспоминаем пароль из памяти
  Serial.print("Пароля из энергонезависимой памяти:");
  Serial.println(int_pass);


  str_pass = String(int_pass, DEC);  // переводим в строчный тип
  pass_lenght = str_pass.length();   // получиаем длину пароля

  digitalWrite(LEDBLUE_PIN, HIGH);
  digitalWrite(LEDGREAN_PIN, HIGH);
  digitalWrite(LEDRED_PIN, HIGH);

  Serial.println("Активация вода нового пароля.");

  Serial.println("Для активации нового пароля введите желаемый пароль.");

  Serial.println("Для сохранения его в энергонезависимую памнять нажмите символ *.");

  Serial.println("Если вы желаете оставить старый пароль 10 секунд.");

  //Serial.println(str_pass.length());

  str_pass = "";  // сброс пароля (пустая строка)





  pass_timer = millis();    // сброс таймера ввода пароля
  while (1) {               // бесконечный цикл
    key = keypad.getKey();  // обработка нажатия

    digitalWrite(LEDGREAN_PIN, LOW);




    if (key != NO_KEY) {  // если была нажата

      digitalWrite(LEDBLUE_PIN, LOW);
      digitalWrite(LEDRED_PIN, LOW);
      digitalWrite(LEDGREAN_PIN, HIGH);
      delay(100);

      pass_timer = millis();  // сбросить таймер
      if (key == '*') {       // если нажата *

        digitalWrite(LEDBLUE_PIN, HIGH);
        digitalWrite(LEDGREAN_PIN, HIGH);
        digitalWrite(LEDRED_PIN, HIGH);


        int_pass = str_pass.toInt();  // перевести в число
        EEPROM.put(0, int_pass);      // записать в память
        EEPROM.commit();
        Serial.println("Пароль записан в энергонезависимую память.");
        Serial.println(int_pass);



        pass_lenght = str_pass.length();  // получиаем длину пароля

        digitalWrite(LEDBLUE_PIN, LOW);
        digitalWrite(LEDGREAN_PIN, LOW);
        digitalWrite(LEDRED_PIN, LOW);


        break;                  // выйти из цикла
      } else if (key == '#') {  // если нажата #
        str_pass = "";          // начать ввод сначала
      } else {                  // если * не нажата
        str_pass += key;        // прибавить нажатую цифру к паролю
      }
    }
    if (millis() - pass_timer > 10000) {  // если сработал таймер
      str_pass = String(int_pass, DEC);   // сбросить ввод и выйти из цикла
                                          //Serial.println(str_pass.length());
      Serial.println("Пароль из энергонезависимой памяти");
      Serial.println(int_pass);
      Serial.println("Выход из цикла ввода пароля.");

      digitalWrite(LEDBLUE_PIN, LOW);
      digitalWrite(LEDGREAN_PIN, LOW);
      digitalWrite(LEDRED_PIN, LOW);

      break;
    }
  }
  delay(1000);
  Serial.println("Активация цикла ввода пароля.");
}

void pass_check() {


  // Serial.println(str_pass);


  key = keypad.getKey();  // обработка нажатия
  if (key == '*') {       // если была нажата *
    Serial.println("звезда");

    pass_timer = millis();  // сбросить таймер
    j = 0;
    while (1) {  // бесконечный цикл ввода пароля

      digitalWrite(LEDBLUE_PIN, HIGH);
      digitalWrite(LEDRED_PIN, LOW);


      key = keypad.getKey();  // обработка нажатия
      if (key != NO_KEY) {    // если была нажата

        digitalWrite(LEDGREAN_PIN, HIGH);
        delay(100);
        digitalWrite(LEDGREAN_PIN, LOW);

        pass_timer = millis();     // сбросить таймер
        if (key == str_pass[j]) {  // если новая введённая цифра совпала с цифрой пароля
          j++;                     // прибавить счётчик
        } else {                   // если нет
          j = 0;                   // начать с начала
        }
        if (j == pass_lenght) {  // если были введены все правильные цифры пароля


          Serial.println("Замок открыт");
          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, HIGH);
          controlop1();
          delay(10000);
          controlcl1();  // время открытого замка
          Serial.println("Замок закрыт");
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, HIGH);


          break;  // выйти из цикла
        }
        if (key == '#') {
          // Serial.println("решето");  // если нажата #

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);

          break;  // выйти из цикла
        }
      }
      if (millis() - pass_timer > 10000) {  // если сработал таймер

        digitalWrite(LEDBLUE_PIN, LOW);
        digitalWrite(LEDGREAN_PIN, LOW);
        digitalWrite(LEDRED_PIN, LOW);

        break;  // выйти из цикла
      }
    }
  }
}


void wificonnectdata() {
  Serial.println("Передача состояние с WEB сервера ");

  WiFiClient client;
  // digitalWrite(LEDRED_PIN, LOW);
  //digitalWrite(LEDBLUE_PIN, HIGH);
  //digitalWrite(LEDGREAN_PIN, HIGH);

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80)) {
    Serial.println("connected]");
    client.print("GET /data.php?");
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    client.println();
    client.println();


    delay(200);

    while (client.available()) {
      String line = client.readStringUntil('\n');

      Serial.println(line);


      char c = client.read();
      if (c == '1') {
        buff = 1;
        Serial.println("Открыто");
      }
      if (c == '0') {
        buff = 0;
        Serial.println("Закрыто");
      }
    }

    client.stop();
    client.flush();
    delay(50);

  } else {
    client.stop();
    client.flush();
    Serial.println("Ошибка подключения");
    delay(1000);
  }
  //digitalWrite(LEDBLUE_PIN, LOW);
  //digitalWrite(LEDGREAN_PIN, LOW);
  Serial.println("Остановка подключения");
}


void buff1() {


  //Serial.println("открыто");
  digitalWrite(LEDRED_PIN, LOW);
  digitalWrite(LEDBLUE_PIN, LOW);
  digitalWrite(LEDGREAN_PIN, HIGH);
}

void controlop1() {
  WiFiClient client;
  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);

  Serial.println("connected к открыть]");
  client.print("GET /controlop.php?");
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  client.flush();
}

void buff2() {



  //Serial.println("закрыто");
  digitalWrite(LEDGREAN_PIN, LOW);
  digitalWrite(LEDRED_PIN, HIGH);
  digitalWrite(LEDBLUE_PIN, LOW);
}

void controlcl1() {

  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  client.connect(host, 80);

  Serial.println("connected к закрыть]");
  client.print("GET /controlcl.php?");
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  client.flush();
}

void initMicroSDCard() {
  Serial.println("Проверяю слот SD");
  if (!SD.begin()) {
    //Serial.println("SD Card не работает");
    SD.end();
    // return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("SD Card не найдена");
    SD.end();
    // return;
  }
}

void Demon(String path2) {


  // Запись  на SD card
  fs::FS& fs = SD;

  File file = fs.open(path2);


  if (file) {
    Serial.println("SD Card найдена");
    Serial.println("Имя файла апаратного кода успешно рааспознано");  // считываем все байты из файла и выводим их в COM-порт
    while (file.available())                                          //Читаем содержимое файла
    {
      buffer = file.readStringUntil('\n');  //Считываем с карты весь дотекст в строку до символа окончания.

      if (buffer == demon) {
        Serial.println("Апаратный код успешно распознан рааспознан");
        Serial.println("Активация апаратного кода");
        Serial.print("Апаратный код:");
        Serial.println(demon);  // для отладки отправляем по UART все что прочитали с карты.
      } else {
        Serial.println("Апаратный код не рааспознан");
      }
    }
  }

  else {

    // выводим ошибку если не удалось открыть файл
    Serial.println("Имя файла апаратного кода не рааспознано");
    buffer = "LOX";
    //Serial.println(buffer);
    SD.end();
  }

  file.close();
  SD.end();
}




void loop() {

  if (buffer == demon) {
    //Serial.println(buffer);
    initMicroSDCard();
    Demon(path2);
    buff1();
    controlop1();
    delay(10000);
    controlcl1();

  } else {


    if (millis() - pass_timerwifi > 10000) {
      pass_timerwifi = millis();
      wificonnectdata();
      initMicroSDCard();
      Demon(path2);
      //Serial.println(buff);
      //Serial.print(" значение ");
    }

    if (buff == 0) {
      buff2();
      pass_check();

    } else {
      buff1();
      //delay(10000);
    }
  }
}
