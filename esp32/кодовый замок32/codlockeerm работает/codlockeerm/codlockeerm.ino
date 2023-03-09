#include "Keypad.h"  //библиотека клавиатуры
#include <EEPROM.h>

#define LEDBLUE_PIN    17 // 4 blue 16 
#define LEDGREAN_PIN    4 //16 grea
#define LEDRED_PIN     16 //17 red

unsigned long pass_timer;
char key;
String str_pass = "";
byte pass_lenght, j;
unsigned long int_pass; // 10 знаков моксимум!!
char keys[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[] = {32, 33, 25, 26};     // Подключены строки (4 пина)
byte colPins[] = {27, 14, 12};           // подключены столбцы (4 пина)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 ); //иниициализировать клавиатуру

void setup() {
  Serial.begin(9600);
  EEPROM.begin(100);

   pinMode(LEDBLUE_PIN  , OUTPUT);
   pinMode(LEDGREAN_PIN  , OUTPUT);
   pinMode(LEDRED_PIN  , OUTPUT); 

       Serial.println("вспоминаю пароль");
  int_pass = EEPROM.get(0, int_pass);     // вспоминаем пароль из памяти

Serial.println(int_pass);
delay(5000);

  str_pass = String(int_pass, DEC);  // переводим в строчный тип
  pass_lenght = str_pass.length();   // получиаем длину пароля

        digitalWrite(LEDBLUE_PIN, HIGH); 
        digitalWrite(LEDGREAN_PIN, HIGH); 
        digitalWrite(LEDRED_PIN, HIGH);

  Serial.println(str_pass.length()); 

  str_pass = "";                       // сброс пароля (пустая строка)

  

  

  pass_timer = millis();               // сброс таймера ввода пароля
  while (1) {                          // бесконечный цикл
    key = keypad.getKey();             // обработка нажатия

           digitalWrite(LEDGREAN_PIN, LOW);
         
          
          

    if (key != NO_KEY) {               // если была нажата

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, HIGH);
          delay(100);

      pass_timer = millis();           // сбросить таймер
      if (key == '*') {                // если нажата *

           digitalWrite(LEDBLUE_PIN, HIGH); 
           digitalWrite(LEDGREAN_PIN, HIGH); 
           digitalWrite(LEDRED_PIN, HIGH);
  

        int_pass = str_pass.toInt();   // перевести в число
        EEPROM.put(0, int_pass);       // записать в память
        EEPROM.commit();
        Serial.println("записал пароль");
        Serial.println(int_pass );
        

delay(5000);
        pass_lenght = str_pass.length();   // получиаем длину пароля

          delay(1000);

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);


        break;                             // выйти из цикла
      }
      else if (key == '#') {           // если нажата #
        str_pass = "";                 // начать ввод сначала
      }
      else {                           // если * не нажата
        str_pass += key;               // прибавить нажатую цифру к паролю
      }
    }
    if (millis() - pass_timer > 10000) {     // если сработал таймер
      str_pass = String(int_pass, DEC);      // сбросить ввод и выйти из цикла
      Serial.println(str_pass.length());
      Serial.println("выхожу из ввода пароля");

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);

      delay(5000);
      break;
    }
  }
}

void pass_check() {
  Serial.println("жду ввода пароля");

     digitalWrite(LEDRED_PIN, HIGH);

  Serial.println(str_pass);


  key = keypad.getKey();             // обработка нажатия
  if (key == '*') {                  // если была нажата *
  Serial.println("звезда");
 
    pass_timer = millis();           // сбросить таймер
    j = 0;
    while (1) {                      // бесконечный цикл ввода пароля

      digitalWrite(LEDBLUE_PIN, HIGH); 
      digitalWrite(LEDRED_PIN, LOW);


      key = keypad.getKey();             // обработка нажатия
      if (key != NO_KEY) {               // если была нажата

         digitalWrite(LEDGREAN_PIN, HIGH); 
         delay(100);
         digitalWrite(LEDGREAN_PIN, LOW);

        pass_timer = millis();           // сбросить таймер
        if (key == str_pass[j]) {        // если новая введённая цифра совпала с цифрой пароля
          j++;                           // прибавить счётчик
        } else {                         // если нет
          j = 0;                         // начать с начала
        }
        if (j == pass_lenght) {          // если были введены все правильные цифры пароля
          Serial.println("Success");
          
          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, HIGH); 
          delay(5000);
          digitalWrite(LEDGREAN_PIN, LOW);


          break;                         // выйти из цикла
        }
        if (key == '#') { 
          Serial.println("решето");               // если нажата #

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);

          break;                         // выйти из цикла
        }
      }
      if (millis() - pass_timer > 10000) {    // если сработал таймер

          digitalWrite(LEDBLUE_PIN, LOW);
          digitalWrite(LEDGREAN_PIN, LOW);
          digitalWrite(LEDRED_PIN, LOW);

        break;                                // выйти из цикла
      }
    }
  }
}

void loop() {
  pass_check();

}