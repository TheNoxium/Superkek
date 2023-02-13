/* Read RFID Tag with RC522 RFID Reader
    Made by miliohm.com
*/
#include <SPI.h>
#include <MFRC522.h>
constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;



void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);
  pinMode(D0, OUTPUT); //red
  pinMode(D1, OUTPUT); //blue
  pinMode(D2  , OUTPUT); //grean
 
}
void loop() {
  
  digitalWrite(D0, HIGH);
   if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "24323223227") {
      Serial.println("Access Granted!");
      digitalWrite(D0, LOW);
      digitalWrite(D2, HIGH);
      
           tone (D8,700); 
           delay(200);
           noTone(D8); 
            
           delay(5000);
           tone (D8,500); 
           delay(200);
           noTone(D8); 
           digitalWrite(D2, LOW);
    } else if (tag == "1606717532") {
          Serial.println("Access Granted!");
      digitalWrite(D0, LOW);
      digitalWrite(D2, HIGH);
      
           tone (D8,700); 
           delay(200);
           noTone(D8); 

           delay(5000);
           tone (D8,500); 
           delay(200);
           noTone(D8);
           digitalWrite(D2, LOW);
    
    } else {
      Serial.println("Access Denied!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
