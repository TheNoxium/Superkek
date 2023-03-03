// GPIO0 должен быть подключен к GND для загрузки кода
// Подключение необходимых библиотек
// библиотеки для NTP
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// библиотеки для ESP32Cam и SD Card
#include "esp_camera.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           
#include "soc/rtc_cntl_reg.h"  
#include "driver/rtc_io.h"

// контакты для модуля камеры AI-THINKER
// Измените пины если у вас другая камера
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

String path2 = "/test.txt";
String buffer;

unsigned long last_time;

camera_config_t config;                 // Конфигурациия камеры

const char *ssid     = "Cats_Ass";     //Название WIFI сети
const char *password = "12345678s";      //Пароль

// Переменные для хранения даты и времени
int currentHour, currentMinute, currentSecond, monthDay, currentMonth, currentYear; 
const int Pausa = 10000;                          // Пауза между фотографиями 10 секунд
// NTP сервер
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800, 60000); // ТАЙМЗОНА(в сек.)  соединение 1раз/ минуту
String Date;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  Serial.begin(115200);

  Serial.print("Соединение с сетью ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Проверка модуля камеры.");
  configInitCamera();
  Serial.println("Ok!");
 


  timeClient.begin();               // Инициализация NTPClient
}

void loop() {

  if (millis() - last_time > 10000)
  {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();  
  currentHour = timeClient.getHours();            // Часы  
  currentMinute = timeClient.getMinutes();        // Минуты   
  currentSecond = timeClient.getSeconds();        // Секунды  
  struct tm *ptm = gmtime ((time_t *)&epochTime); //Структура даты 
  monthDay = ptm->tm_mday;                        // День  
  currentMonth = ptm->tm_mon+1;                   // Месяц  
  currentYear = ptm->tm_year+1900;                // Год
 Date = String(monthDay)+"."+String(currentMonth)+"."+String(currentYear)+"."+String(currentHour)+"."+String(currentMinute)+"."+String(currentSecond);
  
  //Название и путь для сохранения фото на SD Card
  String path = "/" + String(Date) +".jpg";  

  //Получить и сохранить фото

  Serial.print("Проверка MicroSD card модуля. ");

  initMicroSDCard();
  takeSavePhoto(path);

  initMicroSDCard();
  Demon(path2);
  
 // delay(Pausa);
 last_time = millis();
 }                                    // Пауза между фотками 
}

 // Конфигурациия камеры   
void configInitCamera(){
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 

   if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; 
    config.jpeg_quality = 10; 
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  // Инициализация камеры
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Ошибка инициализации камеры 0x%x", err);
    return;
  }


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

void takeSavePhoto(String path){
  // Сделать снимок с помощью камеры
  camera_fb_t  * fb = esp_camera_fb_get();  
  
  if(!fb) {
    Serial.println("Сбой захвата камеры");
    return;
  }

  // Запись фото на SD card
  fs::FS &fs = SD_MMC; 
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file){
    Serial.println("Не удалось открыть файл для записи");
    SD_MMC.end();
  } 
  else {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.printf("Файл сохранён по адресу: %s\n", path.c_str());
   
  }
  file.close(); 
  esp_camera_fb_return(fb);
  SD_MMC.end(); 
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
