#include <SPI.h>
#include <SD.h>
File dataFile;
String buffer;

#include <SPI.h>
#include <MFRC522.h>
constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;


const int chipSelect = D8;

void setup() {
 Serial.begin(9600);
          Serial.println("здаррова");
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D4, OUTPUT);   
  pinMode(D8, OUTPUT);
   
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
     
     // Serial.println(" ");
     //Serial.print(SD.begin( chipSelect ));
     
  //digitalWrite(D8, HIGH);
 //digitalWrite(D4, LOW); 
       if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "24323223227") {
      Serial.println("Access Granted!");
      //  delay(5000);
    } else if (tag == "1606717532") {
          Serial.println("Access Granted!");
      
    
    } else {
      Serial.println("Access Denied!");
      
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
      
     
      
}
 
