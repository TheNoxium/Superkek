#include "Keypad.h"  //библиотека клавиатуры
#include <EEPROMex.h>
#define BUTTON_PIN  12
#define LED1_PIN    7   // 7  green
#define LED2_PIN    10  // 10 blue
#define LED3_PIN    8   // 8  red 
#define MOTO_PIN    5
#define TONE_PIN    3


int tone_frequency[] = {700, 700, 700, 700, 555, 620, 700, 620, 700};
int tone_duration[]  = {175,  60,  60, 320, 350, 350, 175,  75, 700};
int delay_duration[] = {225,  95,  95, 350, 385, 385, 275, 110, 770};
byte count = 0;
byte count_max = 9;

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
byte rowPins[] = {12, 11, 9, 6};     // Подключены строки (4 пина)
byte colPins[] = {5, 4, 2};   
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 ); //иниициализировать клавиатуру

void setup() {
  pinMode(LED3_PIN  , OUTPUT);
  pinMode(LED2_PIN  , OUTPUT);
  pinMode(LED1_PIN  , OUTPUT);
  pinMode(TONE_PIN  , OUTPUT);
  
  Serial.begin(9600);
  int_pass = EEPROM.readLong(0);     // вспоминаем пароль из памяти
  str_pass = String(int_pass, DEC);  // переводим в строчный тип
  pass_lenght = str_pass.length();   // получиаем длину пароля

  str_pass = "";                       // сброс пароля (пустая строка)
  pass_timer = millis();               // сброс таймера ввода пароля
  while (1) {                          // бесконечный цикл
    digitalWrite(LED2_PIN ,HIGH);      // веключается синий светодиод
    key = keypad.getKey();             // обработка нажатия
    if (key != NO_KEY) {               // если была нажата
       digitalWrite(LED1_PIN ,HIGH);
       tone (TONE_PIN,500);
       delay(100);
       noTone(TONE_PIN);             // веключается зеленый светодиод
      pass_timer = millis();            // сбросить таймер
      if (key == '*') {                // если нажата *
        int_pass = str_pass.toInt();   // перевести в число
        EEPROM.writeLong(0, int_pass); // записать в память
        pass_lenght = str_pass.length();
        Serial.println("записал пароль");
        digitalWrite(LED3_PIN ,HIGH);   // веключается красный светодиод
               for ( ;count < count_max; ++count) {
      tone(TONE_PIN, tone_frequency[count], tone_duration[count]);
      delay(delay_duration[count]);  
    }
    count = 0;  
   

    delay(1000);
       digitalWrite(LED2_PIN ,LOW);
       digitalWrite(LED3_PIN ,LOW); 
       digitalWrite(LED1_PIN ,LOW);
        
        
        
                                         
                                         // получиаем длину пароля
        break;                         // выйти из цикла
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
      digitalWrite(LED2_PIN ,LOW);
      digitalWrite(LED3_PIN ,LOW); 
      digitalWrite(LED1_PIN ,LOW);
      break;
    }
  }
}

void pass_check() {
   digitalWrite(LED3_PIN ,HIGH);
   
  key = keypad.getKey();             // обработка нажатия
  if (key == '*') {                  // если была нажата *
    pass_timer = millis();           // сбросить таймер
    j = 0;
    digitalWrite(LED2_PIN ,HIGH);
      tone (TONE_PIN,700);
      delay(100);
      noTone(TONE_PIN);
    while (1) {                      // бесконечный цикл ввода пароля
      key = keypad.getKey();             // обработка нажатия
      if (key != NO_KEY) {
         tone (TONE_PIN,500);
         delay(100);
         noTone(TONE_PIN);                  // если была нажата
        pass_timer = millis();           // сбросить таймер
        if (key == str_pass[j]) {        // если новая введённая цифра совпала с цифрой пароля
          j++; 
           //tone (TONE_PIN,500);
           //delay(100);
           //noTone(TONE_PIN);                   // прибавить счётчик
        } else {                         // если нет
          j = 0;                         // начать с начала
        }
        if (j == pass_lenght) {          // если были введены все правильные цифры пароля
          Serial.println("Success");
           digitalWrite(LED3_PIN ,LOW);
           digitalWrite(LED2_PIN ,LOW);
           digitalWrite(LED1_PIN ,HIGH);
     
            for ( ;count < count_max; ++count) 
            {
            tone(TONE_PIN, tone_frequency[count], tone_duration[count]);
            delay(delay_duration[count]);  
            }
            count = 0;
            delay(60000);
           tone (TONE_PIN,200); 
           delay(200);
           tone (TONE_PIN,100); 
           delay(200);
           noTone(TONE_PIN); 
                digitalWrite(LED2_PIN ,LOW);
                digitalWrite(LED3_PIN ,LOW); 
                digitalWrite(LED1_PIN ,LOW);
                
          
          break;                         // выйти из цикла
        }
        if (key == '#') { 
          digitalWrite(LED2_PIN ,LOW);
          digitalWrite(LED3_PIN ,LOW); 
          digitalWrite(LED1_PIN ,LOW); 
                // если нажата #
          break;                         // выйти из цикла
        }
      }
      if (millis() - pass_timer > 10000) {
        digitalWrite(LED2_PIN ,LOW);
        digitalWrite(LED3_PIN ,LOW); 
        digitalWrite(LED1_PIN ,LOW);
        tone (TONE_PIN,200); 
        delay(200);
        tone (TONE_PIN,100); 
        delay(200);
        noTone(TONE_PIN);// если сработал таймер
        break;                                // выйти из цикла
      }
    }
  }
}

void loop() {
  pass_check();

}
