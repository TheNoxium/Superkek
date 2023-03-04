#include "Keypad.h"  //библиотека клавиатуры




char key;

char keys[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[] = {33, 25, 26, 27};     // Подключены строки (4 пина)
byte colPins[] = {14, 12, 13};          // подключены столбцы (4 пина)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 ); //иниициализировать клавиатуру



void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }

}
 
