#include <Keypad.h> // подключаем библиотеку для управление клавиатурой

const byte ROWS = 4; //число строк у нашей клавиатуры
const byte COLS = 3; //число столбцов у нашей клавиатуры
char hexaKeys[ROWS][COLS] = {// здесь мы располагаем названия наших клавиш, как на клавиатуре,для удобства пользования

  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[] = {6, 7, 8, 9};       // Подключены строки (4 пина)
byte colPins[] = {10, 11, 12};        // подключены столбцы (4 пина)

//передаем все эти данные библиотеке:
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(9600);//запускаем отладочный вывод в монитор порта
}

void loop(){
char customKey = customKeypad.getKey();//записывем нажатый символ

if (customKey){//если что-то нажато
  Serial.println(customKey);//выводим нажатый символ в монитор порта
}

}