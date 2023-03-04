#include <SPI.h>
#include <SD.h>
File dataFile;
String buffer;

const int chipSelect = 18;

void setup() {
    Serial.begin(9600);

   if( !SD.begin( chipSelect )){
       Serial.println("initialization failed!");
       return;
    }
    // открываем файл для чтения
    File dataFile = SD.open("test.txt");
    if (dataFile) {
        // считываем все байты из файла и выводим их в COM-порт
       while (dataFile.available()) //Читаем содержимое файла
  {
    buffer = dataFile.readStringUntil('\n');//Считываем с карты весь дотекст в строку до символа окончания.
    Serial.println(buffer); // для отладки отправляем по UART все что прочитали с карты.
  }
  dataFile.close(); //закроем файл
    } else {
        // выводим ошибку если не удалось открыть файл
        Serial.println("error opening test.txt");
    }
}
void loop() {
}
