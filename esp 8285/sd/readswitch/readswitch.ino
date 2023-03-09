#include <SPI.h>
#include <SD.h>
File dataFile;
String buffer;

const int chipSelect = D8;

void setup() {
    
   
}
void loop() {

    Serial.begin(9600);
    
      //Serial.println("включаюсь");
      
        if( SD.begin( chipSelect ))
        {
      Serial.println(" ");    
      Serial.print(SD.begin( chipSelect ));
      SD.open("test.txt");
      Serial.println(SD.open("test.txt"));
      File dataFile = SD.open("test.txt");
      buffer = dataFile.readStringUntil('\n');
      SD.end( chipSelect );
      Serial.println(buffer);
    
        
    
     
      delay(5000);
      
        } else {
      SD.end( chipSelect );
      Serial.println(" ");
      Serial.print(SD.begin( chipSelect ));
      delay(5000);
     
        }
}
 
