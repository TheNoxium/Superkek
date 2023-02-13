#include <Wire.h>  
#include <SSD1306Wire.h>
#include "images.h"

SSD1306Wire display(0x3c, 5, 4); // SDA - IO5 (D1), SCL - IO4 (D2) 

void setup() {
  Serial.begin(115200);
  display.init(); //  Инициализируем дисплей
  display.flipScreenVertically(); // Устанавливаем зеркальное отображение экрана, к примеру, удобно, если вы хотите желтую область сделать вверху
  
}

void loop() {
  display.clear(); // Очищаем экран
  
display.drawXbm(20, 20, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);

  display.display(); // Выводим на экран
}
