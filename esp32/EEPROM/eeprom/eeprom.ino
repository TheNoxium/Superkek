#include <EEPROM.h>

String str_pass = "123451234512345";
String str_pass2 = "";

void setup() {
   Serial.begin(9600);
  EEPROM.begin(100);

   //EEPROM.put(0, str_pass);
   //EEPROM.commit();
   

   delay(5000);

}

void loop() {

  
   str_pass2 = EEPROM.get(0, str_pass);
   Serial.println(" пароль");
   Serial.println(str_pass2);

   delay(5000);
 

}
