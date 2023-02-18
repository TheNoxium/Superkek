// This post referred to this git. I just trimmed cam and wifi part.
// https://github.com/v12345vtm/CameraWebserver2SD/blob/master/CameraWebserver2SD/CameraWebserver2SD.ino

#include "FS.h" 
#include "SD_MMC.h" 
File dataFile;
String buffer;


//Read a file in SD card
void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    
    if (file) {
        // считываем все байты из файла и выводим их в COM-порт
       while (file.available()) //Читаем содержимое файла
  {
    buffer = file.readStringUntil('\n');//Считываем с карты весь дотекст в строку до символа окончания.
    Serial.println(buffer); // для отладки отправляем по UART все что прочитали с карты.
  }
    file.close();
    SD_MMC.end();
   } else {
        // выводим ошибку если не удалось открыть файл
        Serial.println("error opening test.txt");
         SD_MMC.end();
    }
        
        delay(5000);
    
}



void setup() {  
  Serial.begin(115200);


  
}

void loop() {
       Serial.println("SDcard Testing....");

   if(!SD_MMC.begin()){
        Serial.println("Card Mount Failed");
        SD_MMC.end();
        //return;
    }
   // uint8_t cardType = SD_MMC.cardType();

    ''


    readFile(SD_MMC, "/test.txt");
 
  // put your main code here, to run repeatedly:


   
  delay(1000);
}
