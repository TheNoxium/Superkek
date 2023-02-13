#include "Keypad.h"  //библиотека клавиатуры




char key;

char keys[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[] = {D0, D1, D2, D3};     // Подключены строки (4 пина)
byte colPins[] = {D4, D5, D7};          // подключены столбцы (4 пина)
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
 
