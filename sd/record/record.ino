#include <SPI.h>
#include <SD.h>

const int chipSelect = D8;

void setup() {
    Serial.begin(115200);

   if( !SD.begin( chipSelect )){
       Serial.println("initialization failed!");
       return;
    }
    // открываем файл для чтения
    Serial.println("Card OK");                                  // выводим текст в последовательный порт.
  File myFile = SD.open("file.txt", FILE_WRITE);              // создаём файл для записи
  char c = '@';                                               // создаём переменную
  int i = 42;                                                 // создаём переменную
  float f = 3.14;                                             // создаём переменную
  String s = "я пеодик";
   String s1 = " ";
  myFile.println(s1);  // создаём переменную
  myFile.print(c);                                          // записываем переменную в файл
  myFile.print(i);                                          // записываем переменную в файл
  myFile.print(f);                                          // записываем переменную в файл
  myFile.print(s);                                          // записываем переменную в файл
  myFile.close();                                             // закрываем файл
  Serial.println("done");  
}
void loop() {
}
