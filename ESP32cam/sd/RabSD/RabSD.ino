// This post referred to this git. I just trimmed cam and wifi part.
// https://github.com/v12345vtm/CameraWebserver2SD/blob/master/CameraWebserver2SD/CameraWebserver2SD.ino

#include "FS.h"
#include "SD_MMC"
#include "SPI.h"
File dataFile;

String path2 = "/test.txt";
String buffer;


void setup() {  
  Serial.begin(115200);
  
}

void loop() {
  initMicroSDCard();
  Demon(path2); 
  delay(1000);
}

void initMicroSDCard(){
  if(!SD_MMC.begin()){
    Serial.println("SD Card не работает");
    SD_MMC.end();
   // return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("SD Card не найдена");
    SD_MMC.end();
   // return;
  }
}

void Demon(String path2){
  

  // Запись  на SD card
  fs::FS &fs = SD_MMC;

   File file = fs.open(path2);

  if (file) {
        // считываем все байты из файла и выводим их в COM-порт
       while (file.available()) //Читаем содержимое файла
  {
    buffer = file.readStringUntil('\n');//Считываем с карты весь дотекст в строку до символа окончания.
    Serial.println(buffer); // для отладки отправляем по UART все что прочитали с карты.
  }
  
   } else {
        // выводим ошибку если не удалось открыть файл
        Serial.println("error opening test.txt");
         SD_MMC.end();
    }

  file.close(); 
  SD_MMC.end(); 

}

