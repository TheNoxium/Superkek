#include <SSD1306Wire.h>
#include "fontsRus.h"
SSD1306Wire display(0x3c, 5, 4); // SDA - IO5 (D1), SCL - IO4 (D2) 

void setup() {
  Serial.begin(115200);
   display.init(); //  Инициализируем дисплей
  display.flipScreenVertically(); // Устанавливаем зеркальное отображение экрана, к примеру, удобно, если вы хотите желтую область сделать вверху
  display.setFontTableLookupFunction(FontUtf8Rus);;
}

void loop() {
  display.clear(); // Очищаем экран
  
  display.drawRect(102, 2, 20, 8); // Пустой прямоугольник
  display.fillRect(104, 4, 4, 4); // Заполненный прямоугольник
  display.fillRect(110, 4, 4, 4); // Заполненный прямоугольник
  display.fillRect(116, 4, 4, 4); // Заполненный прямоугольник
  
  display.drawHorizontalLine(0, 14, 128); // Горизонтальная линия
  
  display.setFont(ArialRus_Plain_10); // Шрифт кегль 10
  display.drawString(0, 14, "Привет мир!");
  display.setFont(ArialRus_Plain_16); // Шрифт кегль 16
  display.drawString(0, 25, "Привет мир!");
  display.setFont(ArialRus_Plain_24); // Шрифт кегль 24
  display.drawString(0, 40, "Привет мир!");
  display.display(); // Выводим на экран
  delay(1000); 
  display.clear();
  display.setFont(ArialRus_Plain_24); // Шрифт кегль 24
  display.drawString(0, 40, "Привет мир!");
  display.display(); // Выводим на экран
  delay(1000); 
}

char FontUtf8Rus(const byte ch) { 
    static uint8_t LASTCHAR;

    if ((LASTCHAR == 0) && (ch < 0xC0)) {
      return ch;
    }

    if (LASTCHAR == 0) {
        LASTCHAR = ch;
        return 0;
    }

    uint8_t last = LASTCHAR;
    LASTCHAR = 0;
    
    switch (last) {
        case 0xD0:
            if (ch == 0x81) return 0xA8;
            if (ch >= 0x90 && ch <= 0xBF) return ch + 0x30;
            break;
        case 0xD1:
            if (ch == 0x91) return 0xB8;
            if (ch >= 0x80 && ch <= 0x8F) return ch + 0x70;
            break;
    }

    return (uint8_t) 0;
}