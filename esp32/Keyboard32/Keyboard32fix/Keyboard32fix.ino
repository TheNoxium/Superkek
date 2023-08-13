#include "Keypad.h"  //библиотека клавиатуры




char key;

char keys[3][4] = {
  {'0', '8', '5', '2'},
  {'#', '9', '6', '3'},
  {'*', '7', '4', '1'},

};
byte rowPins[] = { 14, 12, 27 };                                   // Подключены строки (4 пина)
byte colPins[] = { 26, 25, 33, 32 };      
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 3, 4 ); //иниициализировать клавиатуру



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
 
